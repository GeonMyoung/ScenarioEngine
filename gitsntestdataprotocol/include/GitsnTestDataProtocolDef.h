#ifndef _DZ1_TDC_GITSN_TEST_DATA_PROTOCOL_DEF_H_
#define _DZ1_TDC_GITSN_TEST_DATA_PROTOCOL_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"

////////////////////////////////////////////////////////////////////////////////
// GitsnTestDataFrame
typedef struct GitsnTestDataFrame
{
	u16_t			 preamble;
	u16_t			 sequence;
	u8_t			 frameType;
	u16_t			 size;
	u8_t			 channelNum;
	Dz1Binary		*payload;
} GitsnTestDataFrame;

DZ1_CPPLINK DZ1_DLLPORT GitsnTestDataFrame *GitsnTestDataFrame_new(u16_t preamble, 
																   u16_t sequence, 
																   u8_t frameType, 
																   u16_t size, 
																   u8_t channelNum, 
																   Dz1Binary *payload, Dz1Error *err);
static __inline__ GitsnTestDataFrame *GitsnTestDataFrame_gen(Dz1Error *err) { return GitsnTestDataFrame_new(0, 0, 0, 0, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t GitsnTestDataFrame_copy(GitsnTestDataFrame *dst, GitsnTestDataFrame *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT GitsnTestDataFrame *GitsnTestDataFrame_clone(GitsnTestDataFrame *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void GitsnTestDataFrame_purge(GitsnTestDataFrame *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnTestDataFrame_del(GitsnTestDataFrame *p);
static __inline__ void GitsnTestDataFrame_delAndSetNull(void *ptr)
{
	GitsnTestDataFrame **p = (GitsnTestDataFrame **)ptr;
	if (p) { GitsnTestDataFrame_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnTestDataFrame_dump(GitsnTestDataFrame *p, int tab);
// GitsnTestDataFrame
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnTestDataFrames
typedef struct GitsnTestDataFrames
{
	void *storage;
	unsigned int (*count)(struct GitsnTestDataFrames *p);
	Dz1Error (*travel)(struct GitsnTestDataFrames *p, Dz1Error (*func)(void *ptr, GitsnTestDataFrame *entry), void *ptr);
	Dz1Error (*travelForward)(struct GitsnTestDataFrames *p, Dz1Error (*func)(void *ptr, GitsnTestDataFrame *entry), void *ptr);
	Dz1Error (*travelBackward)(struct GitsnTestDataFrames *p, Dz1Error (*func)(void *ptr, GitsnTestDataFrame *entry), void *ptr);
	GitsnTestDataFrame **(*get_array)(struct GitsnTestDataFrames *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct GitsnTestDataFrames *p, GitsnTestDataFrame *data);
	GitsnTestDataFrame *(*extract)(struct GitsnTestDataFrames *p, GitsnTestDataFrame *ptr);
	GitsnTestDataFrame *(*getHead)(struct GitsnTestDataFrames *p);
} GitsnTestDataFrames;

DZ1_CPPLINK DZ1_DLLPORT GitsnTestDataFrames *GitsnTestDataFrames_new(Dz1Error *err);
static __inline__ GitsnTestDataFrames *GitsnTestDataFrames_gen(Dz1Error *err) { return GitsnTestDataFrames_new(err); }
DZ1_CPPLINK DZ1_DLLPORT GitsnTestDataFrames *GitsnTestDataFrames_clone(GitsnTestDataFrames *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void GitsnTestDataFrames_purge(GitsnTestDataFrames *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnTestDataFrames_del(GitsnTestDataFrames *p);
static __inline__ void GitsnTestDataFrames_delAndSetNull(void *ptr)
{
	GitsnTestDataFrames **p = (GitsnTestDataFrames **)ptr;
	if (p != NULL) { GitsnTestDataFrames_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnTestDataFrames_dump(GitsnTestDataFrames *p, int tab);

// GitsnTestDataFrames
////////////////////////////////////////////////////////////////////////////////

#endif
