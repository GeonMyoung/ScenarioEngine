#ifndef _DZ1_TDC_DZ1_MFC_DEF_LOCAL_H_
#define _DZ1_TDC_DZ1_MFC_DEF_LOCAL_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "Dz1MfcDef.h"

////////////////////////////////////////////////////////////////////////////////
// _declare_Dz1MfcFolderTreeNode
struct Dz1MfcFolderTreeNode;
// _declare_Dz1MfcFolderTreeNode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFolderTreeChilds
typedef struct Dz1MfcFolderTreeChilds
{
	void *storage;
	unsigned int (*count)(struct Dz1MfcFolderTreeChilds *p);
	Dz1Error (*travel)(struct Dz1MfcFolderTreeChilds *p, Dz1Error (*func)(void *ptr, struct Dz1MfcFolderTreeNode *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1MfcFolderTreeChilds *p, Dz1Error (*func)(void *ptr, struct Dz1MfcFolderTreeNode *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1MfcFolderTreeChilds *p, Dz1Error (*func)(void *ptr, struct Dz1MfcFolderTreeNode *entry), void *ptr);
	struct Dz1MfcFolderTreeNode **(*get_array)(struct Dz1MfcFolderTreeChilds *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1MfcFolderTreeChilds *p, struct Dz1MfcFolderTreeNode *data);
	bool_t (*remove)(struct Dz1MfcFolderTreeChilds *p, struct Dz1MfcFolderTreeNode *key);
	struct Dz1MfcFolderTreeNode *(*extract)(struct Dz1MfcFolderTreeChilds *p, struct Dz1MfcFolderTreeNode *key);
	struct Dz1MfcFolderTreeNode *(*find)(struct Dz1MfcFolderTreeChilds *p, struct Dz1MfcFolderTreeNode *key);
	int (*cmp)(struct Dz1MfcFolderTreeNode *a, struct Dz1MfcFolderTreeNode *b);
} Dz1MfcFolderTreeChilds;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFolderTreeChilds *Dz1MfcFolderTreeChilds_new(Dz1Error *err);
static __inline__ Dz1MfcFolderTreeChilds *Dz1MfcFolderTreeChilds_gen(Dz1Error *err) { return Dz1MfcFolderTreeChilds_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFolderTreeChilds *Dz1MfcFolderTreeChilds_clone(Dz1MfcFolderTreeChilds *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFolderTreeChilds_purge(Dz1MfcFolderTreeChilds *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFolderTreeChilds_del(Dz1MfcFolderTreeChilds *p);
static __inline__ void Dz1MfcFolderTreeChilds_delAndSetNull(void *ptr)
{
	Dz1MfcFolderTreeChilds **p = (Dz1MfcFolderTreeChilds **)ptr;
	if (p != NULL) { Dz1MfcFolderTreeChilds_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFolderTreeChilds_dump(Dz1MfcFolderTreeChilds *p, int tab);

// Dz1MfcFolderTreeChilds
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFolderTreeNode
struct Dz1MfcFolderTreeNode;

typedef struct Dz1MfcFolderTreeNode
{
	Dz1Str							 name;
	Dz1Str							 full_path;
	time_t							 stamp;
	struct Dz1MfcFolderTreeNode		*parent;
	Dz1MfcFolderTreeChilds			*childs;
} Dz1MfcFolderTreeNode;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFolderTreeNode *Dz1MfcFolderTreeNode_new(Dz1Str name, 
																	   time_t stamp, 
																	   struct Dz1MfcFolderTreeNode *parent, Dz1Error *err);
static __inline__ Dz1MfcFolderTreeNode *Dz1MfcFolderTreeNode_gen(Dz1Error *err) { return Dz1MfcFolderTreeNode_new(NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1MfcFolderTreeNode_copy(Dz1MfcFolderTreeNode *dst, Dz1MfcFolderTreeNode *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFolderTreeNode *Dz1MfcFolderTreeNode_clone(Dz1MfcFolderTreeNode *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFolderTreeNode_purge(Dz1MfcFolderTreeNode *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFolderTreeNode_del(Dz1MfcFolderTreeNode *p);
static __inline__ void Dz1MfcFolderTreeNode_delAndSetNull(void *ptr)
{
	Dz1MfcFolderTreeNode **p = (Dz1MfcFolderTreeNode **)ptr;
	if (p) { Dz1MfcFolderTreeNode_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFolderTreeNode_dump(Dz1MfcFolderTreeNode *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1MfcFolderTreeNode_cmp(Dz1MfcFolderTreeNode *a, Dz1MfcFolderTreeNode *b); 
// Dz1MfcFolderTreeNode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFolderTreeRefChilds
typedef struct Dz1MfcFolderTreeRefChilds
{
	void *storage;
	unsigned int (*count)(struct Dz1MfcFolderTreeRefChilds *p);
	Dz1Error (*travel)(struct Dz1MfcFolderTreeRefChilds *p, Dz1Error (*func)(void *ptr, Dz1MfcFolderTreeNode *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1MfcFolderTreeRefChilds *p, Dz1Error (*func)(void *ptr, Dz1MfcFolderTreeNode *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1MfcFolderTreeRefChilds *p, Dz1Error (*func)(void *ptr, Dz1MfcFolderTreeNode *entry), void *ptr);
	Dz1MfcFolderTreeNode **(*get_array)(struct Dz1MfcFolderTreeRefChilds *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1MfcFolderTreeRefChilds *p, Dz1MfcFolderTreeNode *data);
	bool_t (*remove)(struct Dz1MfcFolderTreeRefChilds *p, Dz1MfcFolderTreeNode *key);
	Dz1MfcFolderTreeNode *(*extract)(struct Dz1MfcFolderTreeRefChilds *p, Dz1MfcFolderTreeNode *key);
	Dz1MfcFolderTreeNode *(*find)(struct Dz1MfcFolderTreeRefChilds *p, Dz1MfcFolderTreeNode *key);
	int (*cmp)(Dz1MfcFolderTreeNode *a, Dz1MfcFolderTreeNode *b);
} Dz1MfcFolderTreeRefChilds;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFolderTreeRefChilds *Dz1MfcFolderTreeRefChilds_new(Dz1Error *err);
static __inline__ Dz1MfcFolderTreeRefChilds *Dz1MfcFolderTreeRefChilds_gen(Dz1Error *err) { return Dz1MfcFolderTreeRefChilds_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFolderTreeRefChilds *Dz1MfcFolderTreeRefChilds_clone(Dz1MfcFolderTreeRefChilds *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFolderTreeRefChilds_purge(Dz1MfcFolderTreeRefChilds *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFolderTreeRefChilds_del(Dz1MfcFolderTreeRefChilds *p);
static __inline__ void Dz1MfcFolderTreeRefChilds_delAndSetNull(void *ptr)
{
	Dz1MfcFolderTreeRefChilds **p = (Dz1MfcFolderTreeRefChilds **)ptr;
	if (p != NULL) { Dz1MfcFolderTreeRefChilds_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFolderTreeRefChilds_dump(Dz1MfcFolderTreeRefChilds *p, int tab);

// Dz1MfcFolderTreeRefChilds
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFolderTree
typedef struct Dz1MfcFolderTree
{
	Dz1MfcFolderTreeChilds		*hdd_roots;
	Dz1MfcFolderTreeChilds		*share_roots;
} Dz1MfcFolderTree;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFolderTree *Dz1MfcFolderTree_new(Dz1Error *err);
static __inline__ Dz1MfcFolderTree *Dz1MfcFolderTree_gen(Dz1Error *err) { return Dz1MfcFolderTree_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFolderTree_purge(Dz1MfcFolderTree *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFolderTree_del(Dz1MfcFolderTree *p);
static __inline__ void Dz1MfcFolderTree_delAndSetNull(void *ptr)
{
	Dz1MfcFolderTree **p = (Dz1MfcFolderTree **)ptr;
	if (p) { Dz1MfcFolderTree_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFolderTree_dump(Dz1MfcFolderTree *p, int tab);
// Dz1MfcFolderTree
////////////////////////////////////////////////////////////////////////////////

#endif
