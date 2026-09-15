#include <dz1_malloc.h>
#include <dz1_aatree.h>
#include "../kernel/dz1_thread_stdio.h"

///////////////////////////////////////////////////////////////////////////////
// AATreeNode Structure
///////////////////////////////////////////////////////////////////////////////
typedef struct Dz1AATreeNode
{
	struct Dz1AATreeNode	*left;
	struct Dz1AATreeNode	*right;
	int						 level;
	void					*user_data;
} Dz1AATreeNode;

///////////////////////////////////////////////////////////////////////////////
// AATreeNode API
///////////////////////////////////////////////////////////////////////////////
static Dz1AATreeNode *Dz1AATreeNode_new(void *user_data, Dz1AATreeNode *NullNode, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1AATreeNode *ret = (Dz1AATreeNode *)Dz1Malloc(sizeof(Dz1AATreeNode), errp);
	if (ret != NULL)
	{
		ret->left = ret->right = NullNode;
		ret->level = 1;
		ret->user_data = user_data;
		Dz1Error_set(err, 0);
	}
	return ret;
}

static void _Dz1AATreeNode_del(Dz1AATreeNode *p, Dz1AATreeNode *NullNode, Dz1DelFunc userDataDel)
{
	if (p == NULL || p == NullNode) return;
	if (p->user_data && userDataDel) userDataDel(p->user_data);
	Dz1Free(p);
}

static void Dz1AATreeNode_delCascade(Dz1AATreeNode *p, Dz1AATreeNode *NullNode, Dz1DelFunc userDataDel)
{
	if (p == NULL || p == NullNode) return;
	Dz1AATreeNode_delCascade(p->left, NullNode, userDataDel);
	Dz1AATreeNode_delCascade(p->right, NullNode, userDataDel);
	_Dz1AATreeNode_del(p, NullNode, userDataDel);
}

///////////////////////////////////////////////////////////////////////////////
// AATree Operation Functions
///////////////////////////////////////////////////////////////////////////////
static Dz1AATreeNode * _singleRotateWithLeft(Dz1AATreeNode * pos)
{
	Dz1AATreeNode * ppos = pos->left;
	pos->left = ppos->right;
	ppos->right = pos;

	return ppos;
}

static Dz1AATreeNode *_singleRotateWithRight(Dz1AATreeNode * pos)
{
	Dz1AATreeNode *ppos = pos->right;
	pos->right = ppos->left;
	ppos->left = pos;

	return ppos;
}

static Dz1AATreeNode *_skew(Dz1AATreeNode * tree)
{
	if (tree->left->level == tree->level)
		tree = _singleRotateWithLeft(tree);
	return tree;
}

static Dz1AATreeNode *_split(Dz1AATreeNode * tree)
{
	if (tree->right->right->level == tree->level)
	{
		tree = _singleRotateWithRight(tree);
		tree->level++;
	}

	return tree;
}

///////////////////////////////////////////////////////////////////////////////
// Dz1AATree Structure
///////////////////////////////////////////////////////////////////////////////
typedef struct _Dz1AATree
{
	Dz1AATreeNode *root;
	pthread_mutex_t lock;

	Dz1CmpFunc userDataCmp;
	Dz1DelFunc userDataDel;
	Dz1DumpFunc userDataDump;

	Dz1AATreeNode _nullNode;
	Dz1AATreeNode *nullNode;

	u32_t count;
} _Dz1AATree;

///////////////////////////////////////////////////////////////////////////////
// Dz1AATree_insert
///////////////////////////////////////////////////////////////////////////////
static Dz1AATreeNode *_Dz1AATree_insert(_Dz1AATree *tree, Dz1AATreeNode *node, void *user_data, Dz1AATreeNode *NullNode, Dz1CmpFunc userDataCmp, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	Dz1Error_set(errp, 0);

	if (node == NullNode)
	{
		node = Dz1AATreeNode_new(user_data, NullNode, err);
		tree->count++;
	}
	else
	{
		int status;
		if ((status = userDataCmp(user_data, node->user_data)) < 0)
			node->left = _Dz1AATree_insert(tree, node->left, user_data, NullNode, userDataCmp, err);
		else if (status > 0)
			node->right = _Dz1AATree_insert(tree, node->right, user_data, NullNode, userDataCmp, err);
		else
			Dz1Error_set(errp, EEXIST);
	}

	node = _skew(node);
	node = _split(node);

	return node;
}

Dz1Error Dz1AATree_insert(Dz1AATree *ptr, void *user_data)
{
	_Dz1AATree *tree = (_Dz1AATree *)ptr;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (tree == NULL) Dz1Error_set(&err, EINVAL);
	else
	{
		pthread_mutex_lock(&tree->lock);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&tree->lock);

		tree->root = _Dz1AATree_insert(tree, tree->root, user_data, tree->nullNode, tree->userDataCmp, &err);

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&tree->lock);
	}
	return err;
}

Dz1Error Dz1AATree_insertAndDo(Dz1AATree *ptr, void *user_data, Dz1AATreeDoFunc doFunc, void *func_arg)
{
	_Dz1AATree *tree = (_Dz1AATree *)ptr;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (tree == NULL) Dz1Error_set(&err, EINVAL);
	else
	{
		pthread_mutex_lock(&tree->lock);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&tree->lock);

		tree->root = _Dz1AATree_insert(tree, tree->root, user_data, tree->nullNode, tree->userDataCmp, &err);
		if (err.code == 0) doFunc(func_arg, user_data);

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&tree->lock);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Dz1AATree_remove
///////////////////////////////////////////////////////////////////////////////
typedef struct Dz1AATreeNodeRemoveArg
{
	_Dz1AATree *tree;
	Dz1AATreeNode *DeletePtr;
	Dz1AATreeNode *LastPtr;
	Dz1CmpFunc userDataCmp;
	Dz1DelFunc userDataDel;
	void **ret;
	bool_t existence;
	bool_t deleted;
} Dz1AATreeNodeRemoveArg;
/*
static Dz1AATreeNode *_Dz1AATree_remove(Dz1AATreeNode *node, void *user_key, Dz1AATreeNode *NullNode, Dz1AATreeNodeRemoveArg *arg)
{
	if (node != NullNode)
	{
		arg->LastPtr = node;

		if (arg->userDataCmp(node->user_data, user_key) > 0)
			node->left = _Dz1AATree_remove(node->left, user_key, NullNode, arg);
		else
		{
			arg->DeletePtr = node;
			node->right = _Dz1AATree_remove(node->right, user_key, NullNode, arg);
		}
	
		if (node == arg->LastPtr)
		{
			if (arg->DeletePtr != NullNode && arg->userDataCmp(arg->DeletePtr->user_data, user_key) == 0)
			{
				if (arg->ret) { *arg->ret = arg->DeletePtr->user_data; }
				else if (arg->userDataDel) arg->userDataDel(arg->DeletePtr->user_data);

				arg->DeletePtr->user_data = node->user_data;
				arg->DeletePtr = NullNode;

				node = node->right;

				_Dz1AATreeNode_del(arg->LastPtr, NullNode, NULL );
				arg->tree->count--;
			}
		}
		else if (node->left->level < node->level - 1 || node->right->level < node->level - 1)
		{
			if (node->right->level > --node->level) node->right->level = node->level;

			node = _skew(node);
			node->right = _skew(node->right);
			node->right->right = _skew(node->right->right);

			node = _split(node);
			node->right = _split(node->right);
		}
	}

	return node;
}
*/
static Dz1AATreeNode *_Dz1AATree_remove(Dz1AATreeNode *node, void *user_key, Dz1AATreeNode *NullNode,
										Dz1AATreeNodeRemoveArg *arg,
										Dz1AATreeCheckFunc func, void *func_arg)
{
	if (node != NullNode)
	{
		arg->LastPtr = node;

		if (arg->userDataCmp(node->user_data, user_key) > 0)
			node->left = _Dz1AATree_remove(node->left, user_key, NullNode, arg, func, func_arg);
		else
		{
			arg->DeletePtr = node;
			node->right = _Dz1AATree_remove(node->right, user_key, NullNode, arg, func, func_arg);
		}
	
		if (node == arg->LastPtr)
		{
			if (arg->DeletePtr != NullNode && arg->userDataCmp(arg->DeletePtr->user_data, user_key) == 0)
			{
				arg->existence = TRUE;
				if (func(func_arg, arg->DeletePtr->user_data) == TRUE)
				{
					if (arg->ret) { *arg->ret = arg->DeletePtr->user_data; }
					else if (arg->userDataDel) arg->userDataDel(arg->DeletePtr->user_data);

					arg->DeletePtr->user_data = node->user_data;
					arg->DeletePtr = NullNode;

					node = node->right;

					_Dz1AATreeNode_del(arg->LastPtr, NullNode, NULL );
					arg->tree->count--;
					arg->deleted = TRUE;
				}
			}
		}
		else if (node->left->level < node->level - 1 || node->right->level < node->level - 1)
		{
			if (node->right->level > --node->level) node->right->level = node->level;

			node = _skew(node);
			node->right = _skew(node->right);
			node->right->right = _skew(node->right->right);

			node = _split(node);
			node->right = _split(node->right);
		}
	}

	return node;
}

static bool_t remove_yes(void *arg, void *data) { return TRUE; }
bool_t Dz1AATree_remove(Dz1AATree *ptr, void *key)
{
	bool_t ret = FALSE;
	_Dz1AATree *tree = (_Dz1AATree *)ptr;
	if (tree && key)
	{
		Dz1AATreeNodeRemoveArg arg;

		arg.tree = tree;
		arg.DeletePtr = tree->nullNode;
		arg.LastPtr = tree->nullNode;
		arg.userDataCmp = tree->userDataCmp;
		arg.userDataDel = tree->userDataDel;
		arg.ret = NULL;
		arg.existence = FALSE;
		arg.deleted = FALSE;

		pthread_mutex_lock(&tree->lock);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&tree->lock);

		tree->root = _Dz1AATree_remove(tree->root, key, tree->nullNode, &arg, remove_yes, NULL);

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&tree->lock);
		ret = arg.deleted;
	}
	return ret;
}

bool_t Dz1AATree_removeConditional(Dz1AATree *ptr, void *key, Dz1AATreeCheckFunc func, void *func_arg, bool_t *existence)
{
	bool_t ret = FALSE;
	_Dz1AATree *tree = (_Dz1AATree *)ptr;
	if (tree && key)
	{
		Dz1AATreeNodeRemoveArg arg;

		arg.tree = tree;
		arg.DeletePtr = tree->nullNode;
		arg.LastPtr = tree->nullNode;
		arg.userDataCmp = tree->userDataCmp;
		arg.userDataDel = tree->userDataDel;
		arg.ret = NULL;
		arg.existence = FALSE;
		arg.deleted = FALSE;

		pthread_mutex_lock(&tree->lock);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&tree->lock);

		tree->root = _Dz1AATree_remove(tree->root, key, tree->nullNode, &arg, func, func_arg);
		ret = arg.deleted;
		if (existence) *existence = arg.existence;

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&tree->lock);
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Dz1AATree_extract
///////////////////////////////////////////////////////////////////////////////
void *Dz1AATree_extract(Dz1AATree *ptr, void *key)
{
	_Dz1AATree *tree = (_Dz1AATree *)ptr;
	void *ret = NULL;
	if (tree && key)
	{
		Dz1AATreeNodeRemoveArg arg;

		arg.tree = tree;
		arg.DeletePtr = tree->nullNode;
		arg.LastPtr = tree->nullNode;
		arg.userDataCmp = tree->userDataCmp;
		arg.userDataDel = tree->userDataDel;
		arg.ret = &ret;

		pthread_mutex_lock(&tree->lock);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&tree->lock);

		tree->root = _Dz1AATree_remove(tree->root, key, tree->nullNode, &arg, remove_yes, NULL);

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&tree->lock);
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Dz1AATree_extractConditional
///////////////////////////////////////////////////////////////////////////////
void *Dz1AATree_extractConditional(Dz1AATree *ptr, void *key, Dz1AATreeCheckFunc func, void *func_arg, bool_t *existence)
{
	void *ret = NULL;
	_Dz1AATree *tree = (_Dz1AATree *)ptr;
	if (tree && key)
	{
		Dz1AATreeNodeRemoveArg arg;

		arg.tree = tree;
		arg.DeletePtr = tree->nullNode;
		arg.LastPtr = tree->nullNode;
		arg.userDataCmp = tree->userDataCmp;
		arg.userDataDel = tree->userDataDel;
		arg.ret = &ret;
		arg.existence = FALSE;
		arg.deleted = FALSE;

		pthread_mutex_lock(&tree->lock);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&tree->lock);

		tree->root = _Dz1AATree_remove(tree->root, key, tree->nullNode, &arg, func, func_arg);
		if (existence) *existence = arg.existence;

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&tree->lock);
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Dz1AATree_find
///////////////////////////////////////////////////////////////////////////////
static Dz1AATreeNode *_Dz1AATreefind(Dz1AATreeNode *node, void *user_key, Dz1AATreeNode *NullNode, Dz1CmpFunc userDataCmp)
{
	int stat = 0;
	if (node == NULL || node == NullNode) return NULL;

	if ((stat = userDataCmp(node->user_data, user_key)) > 0) return _Dz1AATreefind(node->left, user_key, NullNode, userDataCmp);
	else if (stat < 0) return _Dz1AATreefind(node->right, user_key, NullNode, userDataCmp);
	else return node;
}

void *Dz1AATree_find(Dz1AATree *ptr, void *key)
{
	_Dz1AATree *tree = (_Dz1AATree *)ptr;
	void *ret = NULL;
	if (tree && key)
	{
		Dz1AATreeNode *node = NULL;

		pthread_mutex_lock(&tree->lock);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&tree->lock);

		if ((node = _Dz1AATreefind(tree->root, key, tree->nullNode, tree->userDataCmp)))
			ret = node->user_data;

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&tree->lock);
	}
	return ret;
}

void *Dz1AATree_search(Dz1AATree *ptr, void *key, Dz1CmpFunc userDataCmp)
{
	_Dz1AATree *tree = (_Dz1AATree *)ptr;
	void *ret = NULL;
	if (tree && key)
	{
		Dz1AATreeNode *node = NULL;

		pthread_mutex_lock(&tree->lock);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&tree->lock);

		if ((node = _Dz1AATreefind(tree->root, key, tree->nullNode, userDataCmp)))
			ret = node->user_data;

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&tree->lock);
	}
	return ret;
}

void *Dz1AATree_findAndDo(Dz1AATree *ptr, void *key, Dz1AATreeDoFunc func, void *func_arg)
{
	_Dz1AATree *tree = (_Dz1AATree *)ptr;
	void *ret = NULL;
	if (tree && key)
	{
		Dz1AATreeNode *node = NULL;

		pthread_mutex_lock(&tree->lock);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&tree->lock);

		if ((node = _Dz1AATreefind(tree->root, key, tree->nullNode, tree->userDataCmp)))
		{
			if ((ret = node->user_data) != NULL) func(func_arg, ret);
		}

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&tree->lock);
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Dz1AATree_func
///////////////////////////////////////////////////////////////////////////////
Dz1Error Dz1AATree_func(Dz1AATree *ptr, void *key, Dz1AATreeTravelFunc func, void *arg)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	_Dz1AATree *tree = (_Dz1AATree *)ptr;
	if (tree == NULL || key == NULL || func == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Dz1AATreeNode *node = NULL;

		pthread_mutex_lock(&tree->lock);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&tree->lock);

		if ((node = _Dz1AATreefind(tree->root, key, tree->nullNode, tree->userDataCmp)) == NULL) ERR_SET_OUT(&err, ENOENT);
		else if ((err = func(arg, node->user_data)).code) ERR_OUT(&err);
			
		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&tree->lock);
	}
	return err;
}


///////////////////////////////////////////////////////////////////////////////
// Dz1AATree_min
///////////////////////////////////////////////////////////////////////////////
void *Dz1AATree_min(Dz1AATree *ptr)
{
	_Dz1AATree *tree = (_Dz1AATree *)ptr;
	void *ret = NULL;
	if (tree && tree->root != tree->nullNode)
	{
		Dz1AATreeNode *node = NULL;

		pthread_mutex_lock(&tree->lock);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&tree->lock);

		node = tree->root;
		while (node->left != tree->nullNode) node = node->left;
		ret = node->user_data;

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&tree->lock);
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Dz1AATree_max
///////////////////////////////////////////////////////////////////////////////
void *Dz1AATree_max(Dz1AATree *ptr)
{
	_Dz1AATree *tree = (_Dz1AATree *)ptr;
	void *ret = NULL;
	if (tree && tree->root != tree->nullNode)
	{
		Dz1AATreeNode *node = NULL;

		pthread_mutex_lock(&tree->lock);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&tree->lock);

		node = tree->root;
		while(node->right != tree->nullNode) node = node->right;
		ret = node->user_data;

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&tree->lock);
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Travel
static Dz1Error _Dz1AATree_travelForward(Dz1AATreeNode *node, Dz1AATreeTravelFunc func, void *param, Dz1AATreeNode *NullNode)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (node == NULL || node == NullNode) return err;
	else if ((node->left != NullNode) && (err = _Dz1AATree_travelForward(node->left, func, param, NullNode)).code != 0) { }
	else if ((err = func(param, node->user_data)).code) { }
	else if (node->right != NullNode && (err = _Dz1AATree_travelForward(node->right, func, param, NullNode)).code != 0) { }
	return err;
}

static Dz1Error _Dz1AATree_travelBackward(Dz1AATreeNode *node, Dz1AATreeTravelFunc func, void *param, Dz1AATreeNode *NullNode)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (node == NULL || node == NullNode) return err;
	else if (node->right != NullNode && (err = _Dz1AATree_travelBackward(node->right, func, param, NullNode)).code != 0) { }
	else if ((err = func(param, node->user_data)).code) { }
	else if ((node->left != NullNode) && (err = _Dz1AATree_travelBackward(node->left, func, param, NullNode)).code != 0) { }
	return err;
}

Dz1Error Dz1AATree_travelForward(Dz1AATree *ptr, Dz1AATreeTravelFunc func, void *param)
{
	_Dz1AATree *tree = (_Dz1AATree *)ptr;
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (tree == NULL) Dz1Error_set(errp, EINVAL);
	else if (pthread_mutex_trylock(&tree->lock) != 0) ERR_SET_OUT(errp, EBUSY);
	else
	{
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&tree->lock);

		*errp = _Dz1AATree_travelForward(tree->root, func, param, tree->nullNode);

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&tree->lock);
	}
	return err;
}

Dz1Error Dz1AATree_travelBackward(Dz1AATree *ptr, Dz1AATreeTravelFunc func, void *param)
{
	_Dz1AATree *tree = (_Dz1AATree *)ptr;
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (tree == NULL) Dz1Error_set(errp, EINVAL);
	else if (pthread_mutex_trylock(&tree->lock) != 0) ERR_SET_OUT(errp, EBUSY);
	else
	{
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&tree->lock);

		*errp = _Dz1AATree_travelBackward(tree->root, func, param, tree->nullNode);

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&tree->lock);
	}
	return err;
}
// Travel
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Travel 2
static int _Dz1AATree_travelForward2(Dz1AATreeNode *node, Dz1AATreeTravelFunc2 func, void *param, Dz1AATreeNode *NullNode, Dz1Error *errp)
{
	int ret = -1;
	if (node == NULL || node == NullNode) ret = 0;
	else if ((node->left != NullNode) && (ret = _Dz1AATree_travelForward2(node->left, func, param, NullNode, errp)) != 0) { }
	else if ((ret = func(param, node->user_data, errp)) != 0) { }
	else if (node->right != NullNode && (ret = _Dz1AATree_travelForward2(node->right, func, param, NullNode, errp)) != 0) { }
	return ret;
}

int Dz1AATree_travelForward2(Dz1AATree *ptr, Dz1AATreeTravelFunc2 func, void *param, Dz1Error *err)
{
	int ret = -1;
	_Dz1AATree *tree = (_Dz1AATree *)ptr;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (tree == NULL) Dz1Error_set(errp, EINVAL);
	else if (pthread_mutex_trylock(&tree->lock) != 0) ERR_SET_OUT(errp, EBUSY);
	else
	{
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&tree->lock);

		if ((ret = _Dz1AATree_travelForward2(tree->root, func, param, tree->nullNode, errp)) < 0) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&tree->lock);
	}
	return ret;
}

static int _Dz1AATree_travelBackward2(Dz1AATreeNode *node, Dz1AATreeTravelFunc2 func, void *param, Dz1AATreeNode *NullNode, Dz1Error *errp)
{
	int ret = -1;
	if (node == NULL || node == NullNode) ret = 0;
	else if (node->right != NullNode && (ret = _Dz1AATree_travelBackward2(node->right, func, param, NullNode, errp)) != 0) { }
	else if ((ret = func(param, node->user_data, errp)) != 0) { }
	else if ((node->left != NullNode) && (ret = _Dz1AATree_travelBackward2(node->left, func, param, NullNode, errp)) != 0) { }
	return ret;
}

int Dz1AATree_travelBackward2(Dz1AATree *ptr, Dz1AATreeTravelFunc2 func, void *param, Dz1Error *err)
{
	int ret = -1;
	_Dz1AATree *tree = (_Dz1AATree *)ptr;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (tree == NULL) Dz1Error_set(errp, EINVAL);
	else if (pthread_mutex_trylock(&tree->lock) != 0) ERR_SET_OUT(errp, EBUSY);
	else
	{
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&tree->lock);

		if ((ret = _Dz1AATree_travelBackward2(tree->root, func, param, tree->nullNode, errp)) < 0) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&tree->lock);
	}
	return ret;
}
// Travel 2
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1AATree_isEmpty
///////////////////////////////////////////////////////////////////////////////
bool_t Dz1AATree_isEmpty(Dz1AATree *ptr)
{
	_Dz1AATree *tree = (_Dz1AATree *)ptr;
	bool_t ret = FALSE;
	if (tree)
	{
		pthread_mutex_lock(&tree->lock);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&tree->lock);

		if (tree->root == tree->nullNode) ret = TRUE;

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&tree->lock);
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Dz1AATree_new
///////////////////////////////////////////////////////////////////////////////
void *_Dz1AATree_new(Dz1CmpFunc userDataCmp, Dz1DelFunc userDataDel, Dz1DumpFunc userDataDump, Dz1Error *err, const char *file, int line)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	_Dz1AATree *ret = (_Dz1AATree *)_Dz1Malloc(sizeof(_Dz1AATree), errp, file, line);
	if (ret)
	{
		ret->userDataCmp = userDataCmp;
		ret->userDataDel = userDataDel;
		ret->userDataDump = userDataDump;

		ret->_nullNode.left = &ret->_nullNode;
		ret->_nullNode.right = &ret->_nullNode;
		ret->_nullNode.level = 1;
		ret->_nullNode.user_data = NULL;

		ret->nullNode = &ret->_nullNode;

		ret->root = ret->nullNode;

		ret->count = 0;

		pthread_mutex_init(&ret->lock, NULL);

		Dz1Error_set(errp, 0);
	}
	return ret;

}

///////////////////////////////////////////////////////////////////////////////
// Dz1AATree_del
void Dz1AATree_empty(Dz1AATree *ptr)
{
	_Dz1AATree *p = (_Dz1AATree *)ptr;
	if (!p) return;
	if (p->root) Dz1AATreeNode_delCascade(p->root, p->nullNode, p->userDataDel);
	p->root = p->nullNode;
}

void Dz1AATree_del(Dz1AATree *ptr)
{
	_Dz1AATree *p = (_Dz1AATree *)ptr;
	if (!p) return;
	if (p->root) Dz1AATreeNode_delCascade(p->root, p->nullNode, p->userDataDel);
	pthread_mutex_destroy(&p->lock);
	Dz1Free(p);
}
// Dz1AATree_del
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1AATree_dump
static void _Dz1AATree_dump(Dz1AATreeNode *node, int tab, Dz1AATreeNode *NullNode, Dz1DumpFunc userDataDump)
{
	if (node == NULL || node == NullNode) return;
	if (node->left != NullNode) _Dz1AATree_dump(node->left, tab, NullNode, userDataDump);
	if (userDataDump) { userDataDump(node->user_data, tab); }
	else Dz1Thread_tprintf(tab, "entry = %p\n", node->user_data);
	if (node->right != NullNode) _Dz1AATree_dump(node->right, tab, NullNode, userDataDump);
}

void Dz1AATree_dump(Dz1AATree *ptr, int tab)
{
	_Dz1AATree *tree = (_Dz1AATree *)ptr;
	if (tree == NULL || tree->root == tree->nullNode) return;
	_Dz1AATree_dump(tree->root, tab, tree->nullNode, tree->userDataDump);
}
// Dz1AATree_dump
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1AATree_count
///////////////////////////////////////////////////////////////////////////////
u32_t Dz1AATree_count(Dz1AATree *ptr)
{
	_Dz1AATree *tree = (_Dz1AATree *)ptr;
	return tree->count;
}



#if 1
typedef struct _Dz1AATreeCursor
{
	_Dz1AATree					*tree;
	struct _Dz1AATreeCursor		*parent;
	Dz1AATreeNode				*target;
	bool_t						 right_flag;
} _Dz1AATreeCursor;

static void _Dz1AATreeCursor_del(_Dz1AATreeCursor *p)
{
	if (p == NULL) return;
	if (p->parent) { _Dz1AATreeCursor_del(p->parent); p->parent = NULL; }
	Dz1Free(p);
}

void Dz1AATreeCursor_del(Dz1AATreeCursor *ptr)
{
	_Dz1AATreeCursor *p = (_Dz1AATreeCursor *)ptr;
	_Dz1AATreeCursor_del(p);
}

static void _Dz1AATreeCursor_delAndSetNull(void *ptr)
{
	_Dz1AATreeCursor **p = (_Dz1AATreeCursor **)ptr;
	_Dz1AATreeCursor_del(*p); *p = NULL;
}

static _Dz1AATreeCursor *_Dz1AATreeCursor_new(_Dz1AATree *tree, _Dz1AATreeCursor *parent, Dz1AATreeNode *target, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	_Dz1AATreeCursor *ret = (_Dz1AATreeCursor *)Dz1Calloc(sizeof(_Dz1AATreeCursor), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ret->tree = tree;
		ret->parent = parent;
		ret->target = target;
	}
	return ret;
}

Dz1AATreeCursor *Dz1AATreeCursor_clone(Dz1AATreeCursor *ptr, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	_Dz1AATreeCursor *src = (_Dz1AATreeCursor *)ptr;
	_Dz1AATreeCursor *ret = _Dz1AATreeCursor_new(src->tree, src->parent, src->target, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ret->right_flag = src->right_flag;
		Dz1Error_set(errp, 0);
	}
	return (Dz1AATreeCursor *)ret;
}


static _Dz1AATreeCursor *_Dz1AATreeCursor_gen(_Dz1AATree *tree, _Dz1AATreeCursor *parent, Dz1AATreeNode *target, bool_t right_side, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	_Dz1AATreeCursor *ret = _Dz1AATreeCursor_new(tree, parent, target, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(_Dz1AATreeCursor_delAndSetNull, (void *)&ret);
		if (right_side == FALSE)
		{
			if (target->left != tree->nullNode)
			{
				ret->right_flag = FALSE;
				if ((ret = _Dz1AATreeCursor_gen(tree, ret, target->left, right_side, errp)) == NULL) ERR_OUT(errp);
			}
		}
		else
		{
			if (target->right != tree->nullNode)
			{
				ret->right_flag = TRUE;
				if ((ret = _Dz1AATreeCursor_gen(tree, ret, target->right, right_side, errp)) == NULL) ERR_OUT(errp);
			}
		}
		pthread_cleanup_pop(errp->code); // (_Dz1AATreeCursor_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1AATreeCursor *Dz1AATreeCursor_create(Dz1AATree *ptr, bool_t init_to_tail, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	_Dz1AATreeCursor *ret = NULL;
	_Dz1AATree *tree = (_Dz1AATree *)ptr;
	if (Dz1AATree_isEmpty(ptr) == TRUE) ERR_SET_OUT(errp, ENOENT);
	else if ((ret = _Dz1AATreeCursor_gen(tree, NULL, tree->root, init_to_tail, errp)) == NULL) ERR_OUT(errp);
	return (Dz1AATreeCursor *)ret;
}

bool_t Dz1AATreeCursor_cond(Dz1AATreeCursor *ptr)
{
	bool_t ret = FALSE;
	_Dz1AATreeCursor *p = (_Dz1AATreeCursor *)ptr;
	_Dz1AATree *tree = p->tree;
	if (p->target != tree->nullNode) ret = TRUE;
	return ret;
}

Dz1AATreeCursor *Dz1AATreeCursor_next(Dz1AATreeCursor *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	_Dz1AATreeCursor *p = (_Dz1AATreeCursor *)ptr;

	_Dz1AATreeCursor *ret = NULL;

	_Dz1AATree *tree = p->tree;
	Dz1AATreeNode *target = p->target;
	if (target->right == tree->nullNode)
	{	// 오른쪽이 없다 -> 한단계 위로
		do 
		{
			if (p->parent == NULL)
			{
				p->target = tree->nullNode;
				ret = p;
				break;
			}
			else
			{
				ret = p->parent;
				p->parent = NULL;			// unlink
				_Dz1AATreeCursor_del(p);
				p = ret;
			}
		} while (p->right_flag == TRUE);
	}
	else
	{
		p->right_flag = TRUE;
		ret = _Dz1AATreeCursor_gen(tree, p, target->right, FALSE, errp);
	}

	return (Dz1AATreeCursor *)ret;
}

Dz1AATreeCursor *Dz1AATreeCursor_prev(Dz1AATreeCursor *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	_Dz1AATreeCursor *p = (_Dz1AATreeCursor *)ptr;
	_Dz1AATreeCursor *ret = NULL;

	_Dz1AATree *tree = p->tree;
	Dz1AATreeNode *target = p->target;
	if (target->left == tree->nullNode)
	{	// 왼쪽이 없다 -> 한단계 위로
		do 
		{
			if (p->parent == NULL)
			{
				p->target = tree->nullNode;
				ret = p;
				break;
			}
			else
			{
				ret = p->parent;
				p->parent = NULL;			// unlink
				_Dz1AATreeCursor_del(p);
				p = ret;
			}
		} while (p->right_flag == FALSE);
	}
	else
	{
		p->right_flag = FALSE;
		ret = _Dz1AATreeCursor_gen(tree, p, target->left, TRUE, errp);
	}

	return (Dz1AATreeCursor *)ret;
}

void *Dz1AATreeCursor_data(Dz1AATreeCursor *ptr)
{
	_Dz1AATreeCursor *p = (_Dz1AATreeCursor *)ptr;
	Dz1AATreeNode *target = p->target;
	return target->user_data;
}

#endif

///////////////////////////////////////////////////////////////////////////////
// AATree Cursor Node
typedef enum Dz1AATreeCursorNodeSelect
{
	Dz1AATreeCursorNodeSelect_none,
	Dz1AATreeCursorNodeSelect_left,
	Dz1AATreeCursorNodeSelect_self,
	Dz1AATreeCursorNodeSelect_right
} Dz1AATreeCursorNodeSelect;

typedef struct _Dz1AATreeCursorNode
{
	struct _Dz1AATreeCursorNode *parent;
	Dz1AATreeNode				*curr;
	Dz1AATreeCursorNodeSelect	 sel;
} _Dz1AATreeCursorNode;

static _Dz1AATreeCursorNode *_Dz1AATreeCursorNode_new(_Dz1AATreeCursorNode *parent, Dz1AATreeNode *curr, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	_Dz1AATreeCursorNode *ret = NULL;
	
	if (curr == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (_Dz1AATreeCursorNode *)Dz1Calloc(sizeof(_Dz1AATreeCursorNode), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ret->parent = parent;
		ret->curr = curr;
		ret->sel = Dz1AATreeCursorNodeSelect_none;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

static void _Dz1AATreeCursorNode_del(_Dz1AATreeCursorNode *p)
{
	_Dz1AATreeCursorNode *i = p, *parent;
	while(i != NULL)
	{
		parent = i->parent;
		Dz1Free(i);
		i = parent;
	}
}

static void _Dz1AATreeCursorNode_delAndSetNull(void *pptr)
{
	_Dz1AATreeCursorNode **p = (_Dz1AATreeCursorNode **)pptr;
	_Dz1AATreeCursorNode_del(*p); *p = NULL;
}
// AATree Cursor Node
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// AATree Cursor Handle
typedef struct _Dz1AATreeCursorHandle
{
	_Dz1AATree					*tree;
	_Dz1AATreeCursorNode		*index;
} _Dz1AATreeCursorHandle;

Dz1AATreeCursorHandle *Dz1AATreeCursorHandle_new(Dz1AATree *treep, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	_Dz1AATree *tree = (_Dz1AATree *)treep;
	_Dz1AATreeCursorHandle *ret = NULL;
	if (tree == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (_Dz1AATreeCursorHandle *)Dz1Calloc(sizeof(_Dz1AATreeCursorHandle), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ret->tree = tree;
		ret->index = NULL;
		Dz1Error_set(errp, 0);
	}
	return (Dz1AATreeCursorHandle *)ret;
}

void Dz1AATreeCursorHandle_del(Dz1AATreeCursorHandle *ptr)
{
	_Dz1AATreeCursorHandle *p = (_Dz1AATreeCursorHandle *)ptr;
	if (p == NULL) return;
	if (p->index) _Dz1AATreeCursorNode_delAndSetNull(&p->index);
	Dz1Free(p);
}

static _Dz1AATreeCursorNode *_create_index_by_key(_Dz1AATree *src, void *key, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	_Dz1AATreeCursorNode *ret = NULL, *p = NULL;
	Dz1AATreeNode *node = src->root;
	while(ret == NULL)
	{
		if ((p = _Dz1AATreeCursorNode_new(p, node, errp)) == NULL) ERR_OUT(errp);
		else 
		{
			int status = 0;
			pthread_cleanup_push(_Dz1AATreeCursorNode_delAndSetNull, (void *)&p);
			status = src->userDataCmp(node->user_data, key);
			if (status < 0)
			{
				if ((node = node->left) == src->nullNode)
					ERR_SET_OUT(errp, ENOENT);
				else p->sel = Dz1AATreeCursorNodeSelect_left;
			}
			else if (status > 0)
			{
				if ((node = node->right) == src->nullNode)
					ERR_SET_OUT(errp, ENOENT);
				else p->sel = Dz1AATreeCursorNodeSelect_right;
			}
			else
			{
				p->sel = Dz1AATreeCursorNodeSelect_self;
				ret = p;
			}
			pthread_cleanup_pop(errp->code); // (_Dz1AATreeCursorNode_delAndSetNull, (void *)&p);
		}
	}
	return ret;
}

static _Dz1AATreeCursorNode *_left_most(_Dz1AATree *tree, Dz1AATreeNode *node, _Dz1AATreeCursorNode *basis, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	_Dz1AATreeCursorNode *ret = NULL, *p = NULL, *first_create = NULL, *parent = NULL;
	while(ret == NULL)
	{
		pthread_cleanup_push(_Dz1AATreeCursorNode_delAndSetNull, (void *)&parent);
		if ((p = _Dz1AATreeCursorNode_new(parent, node, errp)) == NULL) ERR_OUT(errp);
		else
		{
			parent = p;
			if (first_create == NULL) first_create = p;

			if (node->left != tree->nullNode)
			{
				p->sel = Dz1AATreeCursorNodeSelect_left;
				node = node->left;
			}
			else
			{
				first_create->parent = basis;
				p->sel = Dz1AATreeCursorNodeSelect_self;
				ret = p;
			}
		}
		pthread_cleanup_pop(1); // (_Dz1AATreeCursorNode_delAndSetNull, (void *)&parent);
	}
	return ret;
}

static _Dz1AATreeCursorNode *_create_index_to_head(_Dz1AATree *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	_Dz1AATreeCursorNode *ret = NULL;
	if ((ret = _left_most(src, src->root, NULL, errp)) == NULL) ERR_OUT(errp);
	return ret;
}

static _Dz1AATreeCursorNode *_right_most(_Dz1AATree *tree, Dz1AATreeNode *node, _Dz1AATreeCursorNode *basis, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	_Dz1AATreeCursorNode *ret = NULL, *p = NULL, *first_create = NULL, *parent = NULL;
	while(ret == NULL)
	{
		pthread_cleanup_push(_Dz1AATreeCursorNode_delAndSetNull, (void *)&parent);
		if ((p = _Dz1AATreeCursorNode_new(parent, node, errp)) == NULL) ERR_OUT(errp);
		else
		{
			parent = p;
			if (first_create == NULL) first_create = p;

			if (node->right != tree->nullNode)
			{
				p->sel = Dz1AATreeCursorNodeSelect_right;
				node = node->right;
			}
			else
			{
				first_create->parent = basis;
				p->sel = Dz1AATreeCursorNodeSelect_self;
				ret = p;
			}
		}
		pthread_cleanup_pop(1); // (_Dz1AATreeCursorNode_delAndSetNull, (void *)&parent);
	}
	return ret;
}

static _Dz1AATreeCursorNode *_create_index_to_tail(_Dz1AATree *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	_Dz1AATreeCursorNode *ret = NULL;
	if ((ret = _right_most(src, src->root, NULL, errp)) == NULL) ERR_OUT(errp);
	return ret;
}

bool_t Dz1AATreeCursorHandle_initWithKey(Dz1AATreeCursorHandle *ptr, void *key, Dz1Error *err)
{
	bool_t ret = FALSE;
	_Dz1AATreeCursorHandle *dst = (_Dz1AATreeCursorHandle *)ptr;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (dst->tree == NULL || dst->index != NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((dst->index = _create_index_by_key(dst->tree, key, errp)) == NULL) ERR_OUT(errp);
	else { ret = TRUE; Dz1Error_set(errp, 0); }
	return ret;
}

bool_t Dz1AATreeCursorHandle_initFirst(Dz1AATreeCursorHandle *ptr, void *key, Dz1Error *err)
{
	bool_t ret = FALSE;
	_Dz1AATreeCursorHandle *dst = (_Dz1AATreeCursorHandle *)ptr;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (dst->tree == NULL || dst->index != NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((dst->index = _create_index_to_head(dst->tree, errp)) == NULL) ERR_OUT(errp);
	else { ret = TRUE; Dz1Error_set(errp, 0); }
	return ret;
}

bool_t Dz1AATreeCursorHandle_initLast(Dz1AATreeCursorHandle *ptr, void *key, Dz1Error *err)
{
	bool_t ret = FALSE;
	_Dz1AATreeCursorHandle *dst = (_Dz1AATreeCursorHandle *)ptr;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (dst->tree == NULL || dst->index != NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((dst->index = _create_index_to_tail(dst->tree, errp)) == NULL) ERR_OUT(errp);
	else { ret = TRUE; Dz1Error_set(errp, 0); }
	return ret;
}

bool_t Dz1AATreeCursorHandle_available(Dz1AATreeCursorHandle *ptr)
{
	bool_t ret = FALSE;
	_Dz1AATreeCursorHandle *p = (_Dz1AATreeCursorHandle *)ptr;
	if (p != NULL && p->tree != NULL && p->index != NULL)
	{
		_Dz1AATree *tree = p->tree;
		_Dz1AATreeCursorNode *index = p->index;
		if (index->curr != tree->nullNode) ret = TRUE;
	}
	ret = ret;// avoid warning
	return ret;
}

typedef struct CurserOperRollbackArg
{
	_Dz1AATreeCursorHandle *h;
	_Dz1AATreeCursorNode *old_index;
} CurserOperRollbackArg;

static void CurserOperRollback(void *ptr)
{
	CurserOperRollbackArg *arg = (CurserOperRollbackArg *)ptr;
	arg->h->index = arg->old_index;
}

bool_t Dz1AATreeCursorHandle_next(Dz1AATreeCursorHandle *ptr)
{
	bool_t ret = FALSE;
	_Dz1AATreeCursorHandle *p = (_Dz1AATreeCursorHandle *)ptr;
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (p == NULL || p->tree == NULL || p->index == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (p->index->sel != Dz1AATreeCursorNodeSelect_self) ERR_SET_OUT(errp, EFAULT);
	else
	{
		_Dz1AATree *tree = p->tree;
		_Dz1AATreeCursorNode *index = p->index;
		Dz1AATreeNode *curr = index->curr;
		if (curr == tree->nullNode)
		{
			_Dz1AATreeCursorNode *parent = index->parent;
			if (parent->sel == Dz1AATreeCursorNodeSelect_left)
			{	// 이전에 Prev를 해서 도착한 Null Node임으로
				index->parent = NULL;
				_Dz1AATreeCursorNode_delAndSetNull(&p->index);
				p->index = parent;

				p->index->sel = Dz1AATreeCursorNodeSelect_self;
				ret = TRUE;	// 사용 가능
			}
		}
		else
		{
			if (curr->right != tree->nullNode)
			{	// 오른쪽 노드가 NULL 노드가 아니면
				CurserOperRollbackArg arg = { p, p->index };
				pthread_cleanup_push(CurserOperRollback, (void *)&arg);
				// 오른쪽으로 넘어갔다고 표시하고
				index->sel = Dz1AATreeCursorNodeSelect_right;
				// 오른쪽 노드의 맨 왼쪽 노드를 가르키는 Index List를 만듬
				if ((p->index = _left_most(tree, curr->right, arg.old_index, errp)) == NULL) ERR_OUT(errp);
				else ret = TRUE; // 사용 가능

				pthread_cleanup_pop(errp->code); // (CurserOperRollback, (void *)&arg);
			}
			else if (Dz1AATree_getTail(tree) == curr->user_data) // 오른쪽 노드가 NULL
			{	// 맨 마지막에 닿음
				CurserOperRollbackArg arg = { p, p->index };
				pthread_cleanup_push(CurserOperRollback, (void *)&arg);
				// 오른쪽으로 넘어갔다고 표시하고
				index->sel = Dz1AATreeCursorNodeSelect_right;
				// Null Node를 가르키는 Index를 만듬
				if ((p->index = _Dz1AATreeCursorNode_new(arg.old_index, tree->nullNode, errp)) == NULL) ERR_OUT(errp);
				else p->index->sel = Dz1AATreeCursorNodeSelect_self;
				pthread_cleanup_pop(errp->code); // (CurserOperRollback, (void *)&arg);
			}
			else
			{
				_Dz1AATreeCursorNode *parent = NULL;
				do 
				{
					parent = p->index->parent;						// parent backup
					p->index->parent = NULL;						// 현재 Index의 Parent연결 해제
					_Dz1AATreeCursorNode_delAndSetNull(&p->index);	// 현재 Index삭제
					p->index = parent;								// 새로운 Index설정
				} while (p->index->sel == Dz1AATreeCursorNodeSelect_right);

				if (p->index->sel == Dz1AATreeCursorNodeSelect_left)
				{
					p->index->sel = Dz1AATreeCursorNodeSelect_self;
					ret = TRUE;	// 사용 가능
				}
			}
		}
	}
	ret = ret;// avoid warning
	return TRUE;
}

bool_t Dz1AATreeCursorHandle_prev(Dz1AATreeCursorHandle *ptr)
{
	bool_t ret = FALSE;
	_Dz1AATreeCursorHandle *p = (_Dz1AATreeCursorHandle *)ptr;
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (p == NULL || p->tree == NULL || p->index == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (p->index->sel != Dz1AATreeCursorNodeSelect_self) ERR_SET_OUT(errp, EFAULT);
	else
	{
		_Dz1AATree *tree = p->tree;
		_Dz1AATreeCursorNode *index = p->index;
		Dz1AATreeNode *curr = index->curr;
		if (curr == tree->nullNode)
		{
			_Dz1AATreeCursorNode *parent = index->parent;
			if (parent->sel == Dz1AATreeCursorNodeSelect_right)
			{	// 이전에 Next를 해서 도착한 Null Node임으로
				index->parent = NULL;
				_Dz1AATreeCursorNode_delAndSetNull(&p->index);
				p->index = parent;

				p->index->sel = Dz1AATreeCursorNodeSelect_self;
				ret = TRUE;	// 사용 가능
			}
		}
		else
		{
			if (curr->left != tree->nullNode)
			{	// 왼쪽 노드가 NULL 노드가 아니면
				CurserOperRollbackArg arg = { p, p->index };
				pthread_cleanup_push(CurserOperRollback, (void *)&arg);
				// 왼쪽으로 넘어갔다고 표시하고
				index->sel = Dz1AATreeCursorNodeSelect_left;
				// 왼쪽 노드의 맨 오른쪽 노드를 가르키는 Index List를 만듬
				if ((p->index = _right_most(tree, curr->right, arg.old_index, errp)) == NULL) ERR_OUT(errp);
				else ret = TRUE; // 사용 가능

				pthread_cleanup_pop(errp->code); // (CurserOperRollback, (void *)&arg);
			}
			else if (Dz1AATree_getHead(tree) == curr->user_data) // 왼쪽 노드가 NULL
			{	// 맨 처음에 닿음
				CurserOperRollbackArg arg = { p, p->index };
				pthread_cleanup_push(CurserOperRollback, (void *)&arg);
				// 왼쪽으로 넘어갔다고 표시하고
				index->sel = Dz1AATreeCursorNodeSelect_left;
				// Null Node를 가르키는 Index를 만듬
				if ((p->index = _Dz1AATreeCursorNode_new(arg.old_index, tree->nullNode, errp)) == NULL) ERR_OUT(errp);
				else p->index->sel = Dz1AATreeCursorNodeSelect_self;
				pthread_cleanup_pop(errp->code); // (CurserOperRollback, (void *)&arg);
			}
			else
			{
				_Dz1AATreeCursorNode *parent = NULL;
				do 
				{
					parent = p->index->parent;						// parent backup
					p->index->parent = NULL;						// 현재 Index의 Parent연결 해제
					_Dz1AATreeCursorNode_delAndSetNull(&p->index);	// 현재 Index삭제
					p->index = parent;								// 새로운 Index설정
				} while (p->index->sel == Dz1AATreeCursorNodeSelect_left);

				if (p->index->sel == Dz1AATreeCursorNodeSelect_self)
					Dz1Thread_eprintf("$$$ Warning : AATree Cursor has self node\n");

				if (p->index->sel == Dz1AATreeCursorNodeSelect_right)
				{
					p->index->sel = Dz1AATreeCursorNodeSelect_self;
					ret = TRUE;	// 사용 가능
				}
			}
		}
	}
	ret = ret;// avoid warning
	return TRUE;
}
// AATree Cursor Handle
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1QuickSrotEntry
static Dz1QuickSrotEntry *Dz1QuickSrotEntry_new(void *key, void *body, Dz1Error *errp)
{
	Dz1QuickSrotEntry *ret = (Dz1QuickSrotEntry *)Dz1Calloc(sizeof(Dz1QuickSrotEntry), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ret->key = key;
		ret->body = body;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

static void Dz1QuickSrotEntry_del(Dz1QuickSrotEntry *p, Dz1DelFunc key_del)
{
	if (p == NULL) return;
	if (key_del) key_del(p->key);
	Dz1Free(p);
}
// Dz1QuickSrotEntry
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1QuickSrotTable
Dz1QuickSrotTable *Dz1QuickSrotTable_new(int arr_cnt, Dz1DelFunc key_del, Dz1QuickSrotCmpF key_cmp, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1QuickSrotTable *ret = NULL;
	if (arr_cnt == 0 || key_cmp == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1QuickSrotTable *)Dz1Calloc(sizeof(Dz1QuickSrotTable), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1QuickSrotTable_delAndSetNull, (void *)&ret);
		if ((ret->arr = (Dz1QuickSrotEntry **)Dz1Calloc(sizeof(Dz1QuickSrotEntry *), arr_cnt, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->arr_cnt = arr_cnt;
			ret->key_del = key_del;
			ret->key_cmp = key_cmp;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1QuickSrotTable_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1QuickSrotTable_del(Dz1QuickSrotTable *p)
{
	if (p == NULL) return;
	if (p->arr != NULL)
	{
		int i;
		for (i = 0; i < p->arr_cnt; i++)
		{
			if (p->arr[i] != NULL)
			{
				Dz1QuickSrotEntry_del(p->arr[i], p->key_del);
				p->arr[i] = NULL;
			}
		}
		Dz1Memory_freeAndSetNull(&p->arr);
	}
	Dz1Free(p);
}

bool_t Dz1QuickSrotTable_addEntry(Dz1QuickSrotTable *dst, int idx, void *key, void *body, Dz1Error *err)
{
	bool_t ret = FALSE;
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1QuickSrotEntry *node = NULL;
	if (dst == NULL || idx >= dst->arr_cnt || key == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((node = Dz1QuickSrotEntry_new(key, body, errp)) == NULL) ERR_OUT(errp);
	else
	{
		if (dst->arr[idx] != NULL)
		{
			Dz1QuickSrotEntry_del(dst->arr[idx], dst->key_del);
			dst->arr[idx] = NULL;
		}
		dst->arr[idx] = node;
		Dz1Error_set(errp, 0);
		ret = TRUE;
	}
	return ret;
}
// Dz1QuickSrotTable
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Quick Sort
static void _Dz1QuickSort(Dz1QuickSrotEntry **arr, int left, int right, Dz1QuickSrotCmpF UserKeyCmp)
{
	int i = left, j = right, center = (left + right) >> 1;
	Dz1QuickSrotEntry *pivot = arr[center];
	Dz1QuickSrotEntry *temp = NULL;
	do {
		while (UserKeyCmp(arr[i]->key, pivot->key) < 0) i++;
		while (UserKeyCmp(arr[j]->key, pivot->key) > 0) j--;

		if (i <= j)
		{
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
			j--;
		}
	} while (i <= j);

	/* recursion */
	if (left < j) _Dz1QuickSort(arr, left, j, UserKeyCmp);
	if (i < right) _Dz1QuickSort(arr, i, right, UserKeyCmp);
}

void Dz1QuickSort(Dz1QuickSrotTable *table)
{
	_Dz1QuickSort(table->arr, 0, table->arr_cnt-1, table->key_cmp);
}
// Quick Sort
///////////////////////////////////////////////////////////////////////////////
