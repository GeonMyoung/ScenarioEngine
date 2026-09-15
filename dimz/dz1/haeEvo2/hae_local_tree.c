#include <errno.h>
#include <hae_output.h>
#include <hae_local_memory.h>

#include "hae_local_tree.h"
static HaeLocalTreeChildNode *haeLocalTreeChildNode_create(HaeLocalTreeNode *tree_node)
{
	HaeLocalTreeChildNode *ret = (HaeLocalTreeChildNode *)LOCAL_MALLOC(sizeof(HaeLocalTreeChildNode));
	if (!ret)
	{
		HaeOut->fprintf(stdout, 0, "haeLocalTreeChildNode_create() : Memory allocation error\n");
		exit(1);
	}
	ret->prev = NULL;
	ret->next = NULL;
	ret->tree_node = tree_node;
	return ret;
}

static void haeLocalTreeNode_del(HaeLocalTreeNode *tree_node, HaeGeneralDelFunc data_del);
static void haeLocalTreeNode_dump(HaeLocalTreeNode *tree_node, int tab, HaeGeneralDumpFunc data_dump);
static HaeLocalTreeNode *haeLocalTreeNode_find(HaeLocalTreeNode *tree_node, void *key, HaeGeneralCmpFunc data_cmp);
static HaeLocalTreeNode *haeLocalTreeNode_get_first_child(HaeLocalTreeNode *p);

static void haeLocalTreeChildNode_del(HaeLocalTreeChildNode *p, HaeGeneralDelFunc data_del)
{
	if (!p) return;
	if (p->tree_node) haeLocalTreeNode_del(p->tree_node, data_del);
	LOCAL_FREE(p);
}

static void haeLocalTreeChildNode_dump(HaeLocalTreeChildNode *p, int tab, HaeGeneralDumpFunc data_dump)
{
	if (!p) return;
	haeLocalTreeNode_dump(p->tree_node, tab, data_dump);
}

static HaeLocalTreeChildList *haeLocalTreeChildList_create(void)
{
	HaeLocalTreeChildList *ret = (HaeLocalTreeChildList *)LOCAL_MALLOC(sizeof(HaeLocalTreeChildList));
	if (!ret)
	{
		HaeOut->fprintf(stdout, 0, "haeLocalTreeChildList_create() : Memory allocation error\n");
		exit(1);
	}
	ret->head = NULL;
	ret->tail = NULL;
	return ret;
}

static void haeLocalTreeChildList_del(HaeLocalTreeChildList *list, HaeGeneralDelFunc data_del)
{
	if (!list) return;
	if (list->head)
	{
		HaeLocalTreeChildNode *p = list->head, *next = NULL;
		while(p)
		{
			next = p->next;
			haeLocalTreeChildNode_del(p, data_del);
			p = next;
		}
	}
	LOCAL_FREE(list);
}

static void haeLocalTreeChildList_dump(HaeLocalTreeChildList *list, int tab, HaeGeneralDumpFunc data_dump)
{
	if (!list) return;
	if (list->head)
	{
		HaeLocalTreeChildNode *p = NULL;
		for (p = list->head; p; p = p->next)
			haeLocalTreeChildNode_dump(p, tab, data_dump);
	}
	else
		HaeOut->printf(tab, "[Empty]\n");
}

static void haeLocalTreeChildList_add(HaeLocalTreeChildList *list, HaeLocalTreeNode *tree_node)
{
	HaeLocalTreeChildNode *node = haeLocalTreeChildNode_create(tree_node);
	if (list->head)
	{
		list->tail->next = node;
		node->prev = list->tail;
		list->tail = node;
	}
	else
		list->head = list->tail = node;
}

static void haeLocalTreeChildList_remove(HaeLocalTreeChildList *list, HaeLocalTreeNode *tree_node, HaeGeneralDelFunc data_del)
{
	HaeLocalTreeChildNode *node;
	for (node = list->head; node; node = node->next)
		if (node->tree_node == tree_node) break;
	if (node)
	{
		if (list->head == list->tail && list->tail == node)
			list->head = list->tail = NULL;
		else if (list->head == node)
			list->head = list->head->next;
		else if (list->tail == node)
			list->tail = list->tail->prev;
		else
		{
			node->prev->next = node->next;
			node->next->prev = node->prev;
		}
		node->next = NULL;
		node->prev = NULL;
		haeLocalTreeChildNode_del(node, data_del);
	}
}

static HaeLocalTreeNode *haeLocalTreeChildList_find(HaeLocalTreeChildList *list, void *key, HaeGeneralCmpFunc data_cmp)
{
	HaeLocalTreeNode *ret = NULL;
	HaeLocalTreeChildNode *p = NULL;
	for (p = list->head; p; p = p->next)
		if ((ret = haeLocalTreeNode_find(p->tree_node, key, data_cmp))) return ret;
	return NULL;
}

static HaeLocalTreeNode *haeLocalTreeChildList_get_first(HaeLocalTreeChildList *list)
{
	if (!list) return NULL;
	if (list->head)
	{
		HaeLocalTreeChildNode *node = list->head;
		HaeLocalTreeNode *tree_node = node->tree_node;
		return haeLocalTreeNode_get_first_child(tree_node);
	}
	else
		return NULL;
}

static HaeLocalTreeNode *haeLocalTreeNode_create(HaeLocalTreeNode *parent, void *data)
{
	HaeLocalTreeNode *ret = (HaeLocalTreeNode *)LOCAL_MALLOC(sizeof(HaeLocalTreeNode));
	if (!ret)
	{
		HaeOut->fprintf(stdout, 0, "haeLocalTreeNode_create() : Memory allocation error\n");
		exit(1);
	}
	ret->parent = parent;
	ret->child = haeLocalTreeChildList_create();
	ret->data = data;
	return ret;
}

static void haeLocalTreeNode_del(HaeLocalTreeNode *p, HaeGeneralDelFunc data_del)
{
	if (!p) return;
	if (p->child) haeLocalTreeChildList_del(p->child, data_del);
	if (p->data) data_del(p->data);
	LOCAL_FREE(p);
}

static void haeLocalTreeNode_dump(HaeLocalTreeNode *p, int tab, HaeGeneralDumpFunc data_dump)
{
	if (!p) return;
	if (p->data) data_dump(p->data, tab);
	if (p->child) haeLocalTreeChildList_dump(p->child, tab+1, data_dump);
}

static HaeLocalTreeNode *haeLocalTreeNode_find(HaeLocalTreeNode *p, void *key, HaeGeneralCmpFunc data_cmp)
{
	if (data_cmp(p->data, key)==0) return p;
	else
		return haeLocalTreeChildList_find(p->child, key, data_cmp);
}

static HaeLocalTreeNode *haeLocalTreeNode_get_first_child(HaeLocalTreeNode *p)
{
	HaeLocalTreeNode *ret = haeLocalTreeChildList_get_first(p->child);
	return ret ? ret : p;
}

static int haeLocalTree_add(HaeLocalTree *p, void *parent, void *data)
{
	HaeLocalTreeChildList *child = NULL;
	HaeLocalTreeNode *parent_node = NULL;
	HaeLocalTreeNode *child_node = NULL;

	if (p->data_cmp(p->data, parent)==0)
		child = p->child;
	else
	{
		parent_node = p->find(p, parent);
		if (!parent_node) return ESRCH;
		child = parent_node->child;
	}
	child_node = haeLocalTreeNode_create(parent_node, data);
	haeLocalTreeChildList_add(child, child_node);
	return 0;
}

static int haeLocalTree_remove(HaeLocalTree *p, void *data)
{
	HaeLocalTreeNode *tree_node = haeLocalTreeChildList_find(p->child, data, p->data_cmp);
	if (!tree_node) return ESRCH;
	else
	{
		haeLocalTreeChildList_remove(tree_node->parent->child, tree_node, p->data_del);
		return 0;
	}
}

static HaeLocalTreeNode *haeLocalTree_find(HaeLocalTree *p, void *key)
{
	return haeLocalTreeChildList_find(p->child, key, p->data_cmp);
}

static HaeLocalTreeNode *haeLocalTree_get_first_leaf(HaeLocalTree *p)
{
	return haeLocalTreeChildList_get_first(p->child);
}

static HaeLocalTree *haeLocalTree_create(void *data, HaeGeneralDelFunc data_del, HaeGeneralDumpFunc data_dump, HaeGeneralCmpFunc data_cmp)
{
	HaeLocalTree *ret = (HaeLocalTree *)LOCAL_MALLOC(sizeof(HaeLocalTree));
	if (!ret)
	{
		HaeOut->fprintf(stdout, 0, "haeLocalTree_create() : Memory allocation error\n");
		exit(1);
	}
	ret->child = haeLocalTreeChildList_create();
	ret->data = data;
	ret->data_del = data_del;
	ret->data_dump = data_dump;
	ret->data_cmp = data_cmp;
	ret->add = haeLocalTree_add;
	ret->remove = haeLocalTree_remove;
	ret->find = haeLocalTree_find;
	return ret;
}

static void haeLocalTree_del(HaeLocalTree *p)
{
	if (!p) return;
	if (p->child) haeLocalTreeChildList_del(p->child, p->data_del);
	if (p->data) p->data_del(p->data);
}

static void haeLocalTree_dump(HaeLocalTree *p, int tab)
{
	if (!p) return;
	if (p->data) p->data_dump(p->data, tab);
	haeLocalTreeChildList_dump(p->child, tab+1, p->data_dump);
}

struct HaeLocalTreeCtl HaeLocalTreeCtl =
{
	haeLocalTree_create,
	haeLocalTree_del,
	haeLocalTree_dump
};
