#ifndef DZ1_TODEC_H_LOCAL
#define DZ1_TODEC_H_LOCAL

#include "dz1_todec_struct.h"
#include <dz1_todec.h>

#define NEW_LINE			"\r\n"

#define PSEUDO_NAME_PRESENT			"@present"
#define PSEUDO_NAME_SWITCHED		"@switched"

#define PSEUDO_NAME_COUNT			"@count"
#define PSEUDO_NAME_BODY			"@body"

#define TEMPORARY_FILE_NAME		"_temporary_output_"

DZ1_CPPLINK Dz1TodecUnitSize _resolve_prim_size(PrimitiveInfo *info, Dz1Error *err);

DZ1_CPPLINK Dz1Error Dz1Todec_addTarget(Dz1Todec *dst, Dz1TodecTarget *node);

DZ1_CPPLINK extern ObjectInfo *pseudo_obj_u32;
DZ1_CPPLINK extern ObjectInfo *pseudo_obj_void;

typedef struct PublishEnv
{
	str_t					 text;

	str_t					*inc_path;
	u32_t					 inc_path_cnt;

	FILE					*fp_src;
	FILE					*fp_hdr;

	u32_t					 flags;
} PublishEnv;

DZ1_CPPLINK PublishEnv *PublishEnv_new(str_t path, str_t name, str_t ext, Dz1TodecPubArg *arg, Dz1Error *err);
DZ1_CPPLINK void PublishEnv_del(PublishEnv *p);
static __inline__ void PublishEnv_delAndSetNull(void *pptr)
{
	PublishEnv **p = (PublishEnv **)pptr;
	PublishEnv_del(*p); *p = NULL;
}


typedef struct ObjectTypeMembPublishApi
{
	ObjectType		 type;
	Dz1Error		 (*pub_read)(FILE *fp, StreamElementVariable *var, void *ptr, bool_t *need_else, bool_t do_gen, int tab);
	Dz1Error		 (*pub_write)(FILE *fp, StreamElementVariable *var, void *ptr, bool_t *need_else, bool_t ptr_chk, int tab);
} ObjectTypeMembPublishApi;

extern ObjectTypeMembPublishApi membDefPublishApi[];
extern ObjectTypeMembPublishApi membAltPublishApi[];
extern ObjectTypeMembPublishApi membPartPublishApi[];

extern ObjectTypeMembPublishApi membDefSzPublishApi[];
extern ObjectTypeMembPublishApi membAltSzPublishApi[];
extern ObjectTypeMembPublishApi membPartSzPublishApi[];

extern ObjectTypeMembPublishApi membRstrPublishApi[];
extern ObjectTypeMembPublishApi membRstrSzPublishApi[];

DZ1_CPPLINK ObjectTypeMembPublishApi *ObjectTypeMembPublishApi_find(ObjectTypeMembPublishApi *tbl, ObjectType type);

// typedef struct ObjectTypeGenPublishApi
// {
// 	ObjectType			 type;
// 	Dz1Error			 (*pub_src)(FILE *fp, Dz1TodecTargetCodecMode mode, ObjectInfo *tgt);
// 	Dz1Error			 (*pub_hdr)(FILE *fp, Dz1TodecTargetCodecMode mode, ObjectInfo *tgt);
// } ObjectTypeGenPublishApi;
// DZ1_CPPLINK ObjectTypeGenPublishApi *ObjectTypeGenPublishApi_find(ObjectType type);

DZ1_CPPLINK Dz1Todec *Dz1Todec_parse(str_t src_text, Dz1Error *err);
DZ1_CPPLINK Dz1Error Dz1Todec_gen_src(FILE *fp, Dz1Todec *src, Dz1MdefcModule *module);
DZ1_CPPLINK StreamList *Dz1Todec_analysis(Dz1Todec *todec, Dz1MdefcModule *module, Dz1Error *err);
DZ1_CPPLINK StreamInfo *Dz1TodecTargetCodecEntry_analysis(Dz1TodecTargetCodecEntry *codec, ObjectInfo *src, Dz1MdefcModule *module, Dz1Error *err);

DZ1_CPPLINK Dz1Error StreamElementSimple_pub_read(FILE *fp, StreamElementSimple *p, bool_t *need_else, int tab);
DZ1_CPPLINK Dz1Error StreamElementSimple_pub_write(FILE *fp, StreamElementSimple *p, bool_t *need_else, int tab);
DZ1_CPPLINK Dz1Error StreamElementSimple_pub_sz_read(FILE *fp, StreamElementSimple *p, bool_t *need_else, bool_t do_gen, int tab);
DZ1_CPPLINK Dz1Error StreamElementSimple_pub_sz_write(FILE *fp, StreamElementSimple *p, bool_t *need_else, bool_t ptr_chk, int tab);

DZ1_CPPLINK Dz1Error StreamElementConditional_pub_read(FILE *fp, StreamElementConditional *p, bool_t *need_else, int tab);
DZ1_CPPLINK Dz1Error StreamElementConditional_pub_write(FILE *fp, StreamElementConditional *p, bool_t *need_else, int tab);

DZ1_CPPLINK Dz1Error Dz1TodecInclude_append(Dz1TodecInclude *dst, str_t incld);
#endif
