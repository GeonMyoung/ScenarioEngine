#ifndef DZ1_AATREE_H
#define DZ1_AATREE_H

#include <dz1_error.h>

typedef void Dz1AATree;
typedef Dz1Error	(*Dz1AATreeTravelFunc)(void *param, void *data);
typedef int			(*Dz1AATreeTravelFunc2)(void *param, void *data, Dz1Error *errp);
typedef bool_t		(*Dz1AATreeCheckFunc)(void *arg, void *data);
typedef void		(*Dz1AATreeDoFunc)(void *arg, void *data);
/*
 * Dz1AATree_new : Create New AATree
 *
 * @cmp : user data compare function
 * @del : user data delete function
 * @dump : user data dump function
 * @errp : Dz1Error structure pointer
 *
 * return Address of AATree Structure
 */
#define							 Dz1AATree_new(cmp, del, dump, errp)			_Dz1AATree_new(cmp, del, dump, errp, __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT void   *_Dz1AATree_new(Dz1CmpFunc userDataCmp,
											   Dz1DelFunc userDataDel,
											   Dz1DumpFunc userDataDump,
											   Dz1Error *err, const char *file, int line);

/*
 * Dz1AATree_insert : Insert a user data to target AATree
 *
 * @tree : target AATree
 * @user_data : address of user data structure
 *
 * return Dz1Error
 *
 */
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1AATree_insert(Dz1AATree *tree, void *user_data);


DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1AATree_insertAndDo(Dz1AATree *ptr, void *user_data, Dz1AATreeDoFunc doFunc, void *func_arg);
/*
 * Dz1AATree_remove : Remove a user data from target AATree
 *
 * @tree : target AATree
 * @key : address of user data structure that contain key value
 */
DZ1_CPPLINK DZ1_DLLPORT bool_t	 Dz1AATree_remove(Dz1AATree *tree, void *key);

/*
 * Dz1AATree_removeConditional : Remove a user data from target AATree which user check function tell yes
 *
 * @tree : target AATree
 * @key : address of user data structure that contain key value
 * @func : condition check function pointer
 * @func_arg : user data that need to perform check function
 * @existence : user_data existence status
 *
 * return : remove status, TRUE mean user_data is exist and deleted
 *          FALSE mean user_data does not deleted or does not exist
 *          check existence for user_data existence
 */
DZ1_CPPLINK DZ1_DLLPORT bool_t	 Dz1AATree_removeConditional(Dz1AATree *ptr, void *key, Dz1AATreeCheckFunc func, void *func_arg, bool_t *existence);
/*
 * Dz1AATree_extract : Extract a user data from target AATree
 *
 * @tree : target AATree
 * @key : address of user data structure that contain key value
 *
 * return : address of user data structure or NULL
 *
 * NOTE : user data is truncate out from target AATree
 */
DZ1_CPPLINK DZ1_DLLPORT void	*Dz1AATree_extract(Dz1AATree *tree, void *key);

/*
 * Dz1AATree_extractConditional : Extract a user data from target AATree which user check function tell yes
 *
 * @tree : target AATree
 * @key : address of user data structure that contain key value
 * @func : condition check function pointer
 * @func_arg : user data that need to perform check function
 * @existence : user_data existence status
 *
 * return : address of user data structure or NULL
 *
 * NOTE : user data is truncate out from target AATree
 *        if return NULL, check existence value
 *        existence value is TRUE then user_data is exist but condition is FALSE
 */
DZ1_CPPLINK DZ1_DLLPORT void	*Dz1AATree_extractConditional(Dz1AATree *ptr, void *key, Dz1AATreeCheckFunc func, void *func_arg, bool_t *existence);

/*
 * Dz1AATree_find : Find user data from target AATree
 *
 * @tree : target AATree
 * @key : address of user data structure that contain key value
 *
 * return : address of user data structure or NULL
 */
DZ1_CPPLINK DZ1_DLLPORT void	*Dz1AATree_find(Dz1AATree *tree, void *key);
DZ1_CPPLINK DZ1_DLLPORT void	*Dz1AATree_findAndDo(Dz1AATree *tree, void *key, Dz1AATreeDoFunc func, void *func_arg);
DZ1_CPPLINK DZ1_DLLPORT void	*Dz1AATree_search(Dz1AATree *ptr, void *key, Dz1CmpFunc userDataCmp);

/*
 * Dz1AATree_func: Find user data from target AATree and call user function with that node
 *
 * @tree : target AATree
 * @key : address of user data structure that contain key value
 * @func : function pointer
 * @arg : user data that needs to perform function
 *
 * return : Dz1Error
 */
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1AATree_func(Dz1AATree *ptr, void *key, Dz1AATreeTravelFunc func, void *arg);

/*
 * Dz1AATree_min : return address of user data structure that store minimum key value
 *
 * @tree : target AATree
 *
 * return address of user data structure
 */
DZ1_CPPLINK DZ1_DLLPORT void	*Dz1AATree_min(Dz1AATree *tree);
#define							 Dz1AATree_getHead		Dz1AATree_min

/*
 * Dz1AATree_max : return address of user data structure that store maximum key value
 *
 * @tree : target AATree
 *
 * return address of user data structure
 */
DZ1_CPPLINK DZ1_DLLPORT void	*Dz1AATree_max(Dz1AATree *tree);
#define							 Dz1AATree_getTail		Dz1AATree_max

/*
 * Dz1AATree_travel : execute user function with each all nodes of target AATree
 *
 * @tree : target AATree
 * @func : user function
 * @param : Address of Function Argument Structure
 *
 * return : Dz1Error structure
 */
#define							 Dz1AATree_travel	Dz1AATree_travelForward
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1AATree_travelForward(Dz1AATree *tree, Dz1AATreeTravelFunc func, void *param);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1AATree_travelBackward(Dz1AATree *tree, Dz1AATreeTravelFunc func, void *param);

#define							 Dz1AATree_travel2	Dz1AATree_travelForward2
DZ1_CPPLINK DZ1_DLLPORT int		 Dz1AATree_travelForward2(Dz1AATree *tree, Dz1AATreeTravelFunc2 func, void *param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT int		 Dz1AATree_travelBackward2(Dz1AATree *tree, Dz1AATreeTravelFunc2 func, void *param, Dz1Error *err);

/*
 * Dz1AATree_isEmpty : Test target tree is empty
 *
 * @tree : target AATree
 *
 * return : boolean value
 */
DZ1_CPPLINK DZ1_DLLPORT bool_t	 Dz1AATree_isEmpty(Dz1AATree *tree);

/*
 * Dz1AATree_del : Delete target AATree Structure
 *
 * @tree : target AATree
 */
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1AATree_empty(Dz1AATree *tree);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1AATree_del(Dz1AATree *tree);
static __inline__ void			 Dz1AATree_delAndSetNull(void *ptr)
{
	Dz1AATree **p = (Dz1AATree **)ptr;
	Dz1AATree_del(*p); *p = NULL;
}

/*
 * Dz1AATree_dump : Dump target AATree to target console
 *
 * @tree : target tree
 * @tab : indent level
 */
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1AATree_dump(Dz1AATree *tree, int tab);

/*
 * Dz1AATree_count : Return Total Number of Leafs
 *
 * @tree : target tree
 */
DZ1_CPPLINK DZ1_DLLPORT u32_t	 Dz1AATree_count(Dz1AATree *ptr);


typedef void Dz1AATreeCursor;
DZ1_CPPLINK DZ1_DLLPORT Dz1AATreeCursor *Dz1AATreeCursor_create(Dz1AATree *tree, bool_t init_to_max, Dz1Error *err);
#define									 Dz1AATreeCursor_init(treep, errp)		Dz1AATreeCursor_create((treep), FALSE, (errp))
DZ1_CPPLINK DZ1_DLLPORT Dz1AATreeCursor *Dz1AATreeCursor_clone(Dz1AATreeCursor *ptr, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1AATreeCursor_del(Dz1AATreeCursor *ptr);
static __inline__ void					 Dz1AATreeCursor_delAndSetNull(void *ptr)
{
	Dz1AATreeCursor **p = (Dz1AATreeCursor **)ptr;
	Dz1AATreeCursor_del(*p); *p = NULL;
}

DZ1_CPPLINK DZ1_DLLPORT bool_t			 Dz1AATreeCursor_cond(Dz1AATreeCursor *ptr);

/*
 * Do not use old cursor ptr
 * if u need old cursor info, should clone it
 */
DZ1_CPPLINK DZ1_DLLPORT Dz1AATreeCursor *Dz1AATreeCursor_next(Dz1AATreeCursor *ptr);
DZ1_CPPLINK DZ1_DLLPORT Dz1AATreeCursor *Dz1AATreeCursor_prev(Dz1AATreeCursor *ptr);

DZ1_CPPLINK DZ1_DLLPORT void			*Dz1AATreeCursor_data(Dz1AATreeCursor *ptr);

///////////////////////////////////////////////////////////////////////////////
// New Version of Cursor : Dz1AATreeCursorHandle
typedef void Dz1AATreeCursorHandle;
DZ1_CPPLINK DZ1_DLLPORT Dz1AATreeCursorHandle	*Dz1AATreeCursorHandle_new(Dz1AATree *tree, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void					 Dz1AATreeCursorHandle_del(Dz1AATreeCursorHandle *p);
static __inline__ void Dz1AATreeCursorHandle_delAndSetNull(void *pptr)
{
	Dz1AATreeCursorHandle **p = (Dz1AATreeCursorHandle **)pptr;
	Dz1AATreeCursorHandle_del(*p); *p = NULL;
}

DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1AATreeCursorHandle_initWithKey(Dz1AATreeCursorHandle *dst, void *key, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1AATreeCursorHandle_initFirst(Dz1AATreeCursorHandle *dst, void *key, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1AATreeCursorHandle_initLast(Dz1AATreeCursorHandle *dst, void *key, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1AATreeCursorHandle_available(Dz1AATreeCursorHandle *p);
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1AATreeCursorHandle_next(Dz1AATreeCursorHandle *p);
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1AATreeCursorHandle_prev(Dz1AATreeCursorHandle *p);

// New Version of Cursor : Dz1AATreeCursorHandle
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Quick Sort
typedef int (*Dz1QuickSrotCmpF)(void *keyA, void *keyB);

typedef struct Dz1QuickSrotEntry
{
	void *key;
	void *body;
} Dz1QuickSrotEntry;

typedef struct Dz1QuickSrotTable
{
	Dz1QuickSrotEntry		**arr;
	int						 arr_cnt;

	Dz1DelFunc				 key_del;
	Dz1QuickSrotCmpF		 key_cmp;
} Dz1QuickSrotTable;
DZ1_CPPLINK Dz1QuickSrotTable	*Dz1QuickSrotTable_new(int arr_cnt, Dz1DelFunc key_del, Dz1QuickSrotCmpF key_cmp, Dz1Error *err);
DZ1_CPPLINK void				 Dz1QuickSrotTable_del(Dz1QuickSrotTable *p);
static __inline__ void			 Dz1QuickSrotTable_delAndSetNull(void *pptr)
{
	Dz1QuickSrotTable **p = (Dz1QuickSrotTable **)pptr;
	Dz1QuickSrotTable_del(*p); *p = NULL;
}
DZ1_CPPLINK bool_t				 Dz1QuickSrotTable_addEntry(Dz1QuickSrotTable *dst, int idx, void *key, void *body, Dz1Error *err);

DZ1_CPPLINK void Dz1QuickSort(Dz1QuickSrotTable *table);
// Quick Sort
///////////////////////////////////////////////////////////////////////////////
#endif
