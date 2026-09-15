#ifndef DZ1_JSON_H
#define DZ1_JSON_H

#include <Dz1JsonDef.h>

// #define MY_SYSTEM_CHARSET	DZ1_SYSTEM_CHARSET

// #ifndef	UNIX_SYSTEM
// 
// #ifdef	UNICODE
// 
// #if 	DZ1_ENDIAN == DZ1_ENDIAN_LITTLE
// #define MY_SYSTEM_CHARSET		"UCS2-LE"	// Little Endian
// #elif 	DZ1_ENDIAN == DZ1_ENDIAN_BIG
// #define MY_SYSTEM_CHARSET		"UCS2-BE"	// Big Endian
// #else// ENDIAN
// #error ENDIAN								// No Endian
// #endif//ENDIAN
// 
// #else// UNICODE
// 
// #define MY_SYSTEM_CHARSET		"EUC-KR"	// MBCS
// 
// #endif//UNICODE
// 
// #else// UNIX_SYSTEM
// 
// #define MY_SYSTEM_CHARSET		"UTF-8"
// #endif


DZ1_CPPLINK Dz1JsonSpec			*Dz1JsonSpec_generate(Dz1Error *err);
DZ1_CPPLINK Dz1Error			 Dz1JSonSpec_add_construct(Dz1JsonSpec *dst, Dz1Str name, Dz1JsonObjGenF genf, Dz1JsonObjDelF delf, 
														   Dz1JsonConstructSetChildF scf, Dz1JsonConstructGetChildF gcf, 
														   Dz1JsonSpecChild *arr, Dz1JsonConstructType type);
DZ1_CPPLINK Dz1Error			 Dz1JSonSpec_add_array(Dz1JsonSpec *dst, Dz1Str name, Dz1JsonObjGenF genf, Dz1JsonObjDelF delf, 
													   Dz1JsonArrayAppendF apnd, Dz1JsonArrayCountF cntf, 
													   Dz1JsonArrayTravelF travelf, Dz1Str memb_type);
DZ1_CPPLINK Dz1Error			 Dz1JsonSpec_add_primitive(Dz1JsonSpec *dst, Dz1Str name, Dz1JsonObjGenF genf, Dz1JsonObjDelF delf, 
														   Dz1JsonSpecPrimitiveLoaderF loadf, Dz1JsonSpecPrimitiveStringifyF stringifyf);
DZ1_CPPLINK bool_t				*Dz1JsonSpec_check(Dz1JsonSpec *spec, Dz1Error *err);

DZ1_CPPLINK Dz1JsonSpecChild	*Dz1JsonSpecChilds_findByIdx(Dz1JsonSpecChilds *list, int idx);

typedef void Dz1Json;
DZ1_CPPLINK Dz1Json				*Dz1Json_new(str_t ingress_charset, Dz1JsonSpec *spec_ref, Dz1Str root_type_name, Dz1Error *err);
DZ1_CPPLINK void				 Dz1Json_del(Dz1Json *p);
static __inline__ void			 Dz1Json_delAndSetNull(void *pptr)
{
	Dz1Json **p = (Dz1Json **)pptr;
	Dz1Json_del(*p); *p = NULL;
}

DZ1_CPPLINK ssize_t	 Dz1Json_push_stream(Dz1Json *h, u8_t *src, size_t size, Dz1Error *err);							// save  JSON Text to   parse buffer of Dz1Json Handle
DZ1_CPPLINK int		 Dz1Json_parse(Dz1Json *h, Dz1Error *err);															// parse JSON Text from parse buffer of Dz1Json Handle
DZ1_CPPLINK void	*Dz1Json_read(Dz1Json *h, Dz1Error *err);															// extract object  from Object FIFO  of Dz1Json Handle

DZ1_CPPLINK bool_t	 Dz1Json_stringify(Dz1Json *h, Dz1Str type_name, void *obj, Dz1JsonNewLine nl_mode, Dz1Error *err);	// print   JSON Text to   output buffer of Dz1Json Handle
DZ1_CPPLINK ssize_t	 Dz1Json_squeeze(Dz1Json *h, u8_t *buf, size_t sz, Dz1Error *err);									// extract JSON Text from output buffer of Dz1Json Handle
DZ1_CPPLINK Dz1Str	 Dz1Json_stringified(Dz1Json *h, Dz1Error *err);													// extract complete JSON Text from output buffer of Dz1Json Handle

#define DZ1_JSON_LEVER_DEBUG_STREAM			0x80000000
DZ1_CPPLINK bool_t	 Dz1Json_setDebugFlagsLexer(Dz1Json *h, u32_t flag, Dz1Error *err);

/////////////////////////////////////////////////////////////////////////////////////////////
// Typical Primitive Loader & Stringify
DZ1_CPPLINK bool_t Dz1Json_real64_t_load(Dz1JsonVarBind *dst, Dz1JsonToken *tok, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1Json_real64_t_stringify(void *obj, Dz1ElasticBuf *elb, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1Json_real32_t_load(Dz1JsonVarBind *dst, Dz1JsonToken *tok, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1Json_real32_t_stringify(void *obj, Dz1ElasticBuf *elb, Dz1Error *err);

DZ1_CPPLINK bool_t Dz1Json_u64_t_load(Dz1JsonVarBind *dst, Dz1JsonToken *tok, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1Json_u64_t_stringify(void *obj, Dz1ElasticBuf *elb, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1Json_s64_t_stringify(void *obj, Dz1ElasticBuf *elb, Dz1Error *err);

DZ1_CPPLINK bool_t Dz1Json_u32_t_load(Dz1JsonVarBind *dst, Dz1JsonToken *tok, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1Json_u32_t_stringify(void *obj, Dz1ElasticBuf *elb, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1Json_s32_t_stringify(void *obj, Dz1ElasticBuf *elb, Dz1Error *err);

DZ1_CPPLINK bool_t Dz1Json_u16_t_load(Dz1JsonVarBind *dst, Dz1JsonToken *tok, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1Json_u16_t_stringify(void *obj, Dz1ElasticBuf *elb, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1Json_s16_t_stringify(void *obj, Dz1ElasticBuf *elb, Dz1Error *err);

DZ1_CPPLINK bool_t Dz1JsonUtil_stringify_null(Dz1ElasticBuf *buf, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1JsonUtil_stringify_quotstr(Dz1ElasticBuf *elb, Dz1Str v, Dz1Error *err);	// make quotation string and push
DZ1_CPPLINK bool_t Dz1JsonUtil_stringify_s32(Dz1ElasticBuf *elb, s32_t v, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1JsonUtil_stringify_u32(Dz1ElasticBuf *elb, u32_t v, Dz1Error *err);

DZ1_CPPLINK bool_t Dz1Json_u8_t_load(Dz1JsonVarBind *dst, Dz1JsonToken *tok, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1Json_u8_t_stringify(void *obj, Dz1ElasticBuf *elb, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1Json_s8_t_stringify(void *obj, Dz1ElasticBuf *elb, Dz1Error *err);

DZ1_CPPLINK bool_t Dz1Json_Dz1IPv4_load(Dz1JsonVarBind *dst, Dz1JsonToken *tok, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1Json_Dz1IPv4_stringify(void *obj, Dz1ElasticBuf *elb, Dz1Error *err);

DZ1_CPPLINK bool_t Dz1Json_Dz1Str_load(Dz1JsonVarBind *dst, Dz1JsonToken *tok, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1Json_Dz1Str_stringify(void *obj, Dz1ElasticBuf *elb, Dz1Error *err);
// Typical Primitive Loader & Stringify
/////////////////////////////////////////////////////////////////////////////////////////////

DZ1_CPPLINK str_t Dz1JsonUtilA_stringConvToHost(const str_t json_codec_str, Dz1Error *err);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1JsonUtilW_stringConvToHost(const wstr_t json_codec_str, Dz1Error *err);
#ifdef UNICODE
#define Dz1JsonUtil_stringConvToHost		Dz1JsonUtilW_stringConvToHost
#else
#define Dz1JsonUtil_stringConvToHost		Dz1JsonUtilA_stringConvToHost
#endif
#else
#define Dz1JsonUtil_stringConvToHost		Dz1JsonUtilW_stringConvToHost
#endif

DZ1_CPPLINK void *Dz1JosnUtil_parseFile( Dz1Str parse_type, Dz1Str fn,							  Dz1JsonSpec *spec, Dz1Error *err);
DZ1_CPPLINK void *Dz1JosnUtil_parseFile2(Dz1Str parse_type, Dz1Str path, Dz1Str name_ext,		  Dz1JsonSpec *spec, Dz1Error *err);
DZ1_CPPLINK void *Dz1JosnUtil_parseFile3(Dz1Str parse_type, Dz1Str path, Dz1Str name, Dz1Str ext, Dz1JsonSpec *spec, Dz1Error *err);

DZ1_CPPLINK bool_t Dz1JosnUtil_emitFile( Dz1Str emit_type, void *emit_ptr, Dz1Str fn,							 Dz1JsonSpec *spec, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1JosnUtil_emitFile2(Dz1Str emit_type, void *emit_ptr, Dz1Str path, Dz1Str name_ext,		 Dz1JsonSpec *spec, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1JosnUtil_emitFile3(Dz1Str emit_type, void *emit_ptr, Dz1Str path, Dz1Str name, Dz1Str ext, Dz1JsonSpec *spec, Dz1Error *err);

#endif

