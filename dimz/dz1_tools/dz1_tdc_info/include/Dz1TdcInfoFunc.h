#ifndef FUNCTION_INFO_H_LOCAL
#define FUNCTION_INFO_H_LOCAL

#include <dz1_fifo.h>

// typedef func <return type> (*name)(<type> <name>, ...);
struct ObjectInfo;
typedef struct FunctionArg
{
	struct ObjectInfo	*argType;
	s32_t				 argForward;
	s32_t				 argPtrCnt;
	str_t				 instance;
} FunctionArg;
DZ1_CPPLINK FunctionArg *FunctionArg_new(struct ObjectInfo *argType, s32_t argForward, s32_t argPtrCnt, str_t instance, Dz1Error *err); // instance taken pointer not clone
DZ1_CPPLINK void FunctionArg_del(FunctionArg *p);
DZ1_CPPLINK void FunctionArg_dump(FunctionArg *p, int tab);
static __inline__ void FunctionArg_delAndSetNull(void *ptr)
{
	FunctionArg **p = (FunctionArg **)ptr;
	FunctionArg_del(*p); *p = NULL;
}

typedef struct FunctionArgs
{
	Dz1Fifo *list;
	Dz1Error (*add)(struct FunctionArgs *list, struct ObjectInfo *argType, s32_t argForward, s32_t argPtrCnt, str_t instance);
	Dz1Error (*insert)(struct FunctionArgs *list, FunctionArg *e);
	u32_t (*count)(struct FunctionArgs *list);
	Dz1Error (*travel)(struct FunctionArgs *list, Dz1Error (*func)(void *ptr, FunctionArg *p), void *ptr);
} FunctionArgs;

DZ1_CPPLINK FunctionArgs *FunctionArgs_new(Dz1Error *err);
DZ1_CPPLINK void FunctionArgs_del(FunctionArgs *p);
DZ1_CPPLINK void FunctionArgs_dump(FunctionArgs *p, int tab);
static __inline__ void FunctionArgs_delAndSetNull(void *ptr)
{
	FunctionArgs **p = (FunctionArgs **)ptr;
	FunctionArgs_del(*p); *p = NULL;
}

#define FUNCTION_RET_FORWARD_NONE		0
#define FUNCTION_RET_FORWARD_STRUCT		1
#define FUNCTION_RET_FORWARD_UNION		2

typedef struct FunctionInfo
{
	struct ObjectInfo	*retType;		// reference
	bool_t				 retIsPointer;
	s32_t				 retForward;
	FunctionArgs		*args;
} FunctionInfo;
DZ1_CPPLINK FunctionInfo *FunctionInfo_new(struct ObjectInfo *retType, bool_t retIsPointer, s32_t retForward, Dz1Error *err);
DZ1_CPPLINK void FunctionInfo_del(FunctionInfo *p);
DZ1_CPPLINK void FunctionInfo_dump(FunctionInfo *p, int tab);
static __inline__ void FunctionInfo_delAndSetNull(void *ptr)
{
	FunctionInfo **p = (FunctionInfo **)ptr;
	FunctionInfo_del(*p); *p = NULL;
}

DZ1_CPPLINK FunctionInfo *FunctionInfo_gen(Dz1Error *err);
DZ1_CPPLINK ssize_t FunctionInfo_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err);
DZ1_CPPLINK ssize_t FunctionInfo_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err);

#endif

