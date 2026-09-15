#ifndef ISO14827_TEST_HELPER_MSG_SET_H
#define ISO14827_TEST_HELPER_MSG_SET_H

#include <dz1_asn1.h>


//
/////////////////////////////////////////////////////////////////////////////////
//// Iso14827TestMsgStructAPI
//typedef struct Iso14827TestMsgStructAPI
//{
//	Dz1Str						 oid;
//	void* (*get_eam_list)(void* struct_ptr, Dz1Error* err);
//	void* (*eam_gen_empty)(Dz1Error* err);
//	void						 (*eam_delAndSetNull)(void* pptr);
//	void* (*struct_convert_from_eam)(void* eam_list_ptr, Dz1Error* err);
//	Dz1Binary* (*struct_encode)(void* struct_ptr, Dz1Asn1Codec codec, Dz1Error* err);
//	void* (*struct_decode)(Dz1Binary* bin, Dz1Asn1Codec codec, Dz1Error* err);
//	Dz1DumpFunc					 struct_dump;
//	Dz1FDumpFunc				 struct_fdump;
//	void						 (*struct_delAndSetNull)(void* pptr);
//}Iso14827TestMsgStructAPI;
//
//
//DZ1_CPPLINK Dz1Binary* Iso14827TestMsgStructAPI_convert(Iso14827TestMsgStructAPI* api, void* eam_list_ptr, Dz1Asn1Codec codec, Dz1Error* err);
//DZ1_CPPLINK Dz1Binary* Iso14827TestMsgStructAPI_encode(Iso14827TestMsgStructAPI* api, void* struct_ptr, Dz1Asn1Codec codec, Dz1Error* err);
//DZ1_CPPLINK void Iso14827TestMsgStructAPI_dump(Iso14827TestMsgStructAPI* api, void* struct_ptr, int tab);
//
//#define _encoder_declare_(struct_name, asn_name)\
//Dz1Binary *struct_name##_encode(void *struct_ptr, Dz1Asn1Codec codec, Dz1Error *errp)\
//{\
//	Dz1Binary *ret = NULL;\
//	struct_name *p = (struct_name *)struct_ptr;\
//	asn_name asn;\
//	ASN1WorkSpace ws;\
//	ASN1_INIT_WS_INFO(&ws);\
//	pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);\
//	if ((*errp = struct_name##_toASN(&asn, p, &ws)).code) ERR_OUT(errp);\
//	else\
//	{\
//		switch(codec)\
//		{\
//		case Dz1Asn1Codec_ber:\
//			if (ASN1_BER_Enc_##asn_name(&ws, &asn, ASN1EXPL) < 0) ERR_SET_OUT(errp, EFAULT);\
//			else Dz1Error_set(errp, 0);\
//			break;\
//		default: ERR_SET_OUT(errp, ENOSYS); break;\
//		}\
//		if (errp->code == 0)\
//		{\
//			if ((ret = Dz1Binary_new(ASN1WorkSpace_getEncodePtr(&ws), ASN1WorkSpace_getEncodedSize(&ws, codec), errp)) == NULL) ERR_OUT(errp);\
//			else Dz1Error_set(errp, 0);\
//		}\
//	}\
//	pthread_cleanup_pop(1);\
//	return ret;\
//}
//
//#define _decoder_declare_(struct_name, asn_name)\
//void *struct_name##_decode(Dz1Binary *src, Dz1Asn1Codec codec, Dz1Error *err)\
//{\
//	DZ1_ERROR_SAFE_PTR(errp, err);\
//	void *ret = NULL;\
//	ASN1WorkSpace ws;\
//	size_t consume_sz = 0;\
//	asn_name asn;\
//	ASN1_INIT_WS_INFO(&ws);\
//	pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);\
//	ASN1_Save_WORKSPACE(&ws, src->data, src->size);\
//	ws.dataSize = src->size;\
//	switch(codec)\
//	{\
//	case Dz1Asn1Codec_ber:\
//		if (ASN1_BER_Dec_##asn_name(&ws, &asn, src->size, ASN1EXPL) < 0) ERR_SET_OUT(errp, EFAULT);\
//		else\
//		{\
//			consume_sz = ws.buffer.current - ws.buffer.data;\
//			Dz1Error_set(errp, 0);\
//		}\
//		break;\
//	default: ERR_SET_OUT(errp, ENOSYS); break;\
//	}\
//	if (errp->code == 0)\
//	{\
//		if ((ret = struct_name##_newFromASN(&asn, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);\
//		else Dz1Error_set(errp, 0);\
//	}\
//	pthread_cleanup_pop(1);\
//	return ret;\
//}
//
//#define _get_eam_list_declare_(StandardName, StructName, struct_name, json_spec_name, file_path)\
//void* StructName##_get_eam_list(void *struct_ptr, Dz1Error *errp)\
//{\
//	void* *ret = NULL;\
//	Dz1Str filePath = file_path;\
//	Dz1Str jsonStr = Dz1Str_loadFromFile(filePath, errp);\
//	Dz1JsonSpec* spec = StandardName##Def_genJsonSpec(errp);\
//	pthread_cleanup_push(Dz1JsonSpec_delAndSetNull, (void*)&spec);\
//	if (filePath == NULL) ERR_OUT(errp);\
//	else if (jsonStr == NULL) ERR_OUT(errp);\
//	else if (spec == NULL) ERR_OUT(errp);\
//	else\
//	{\
//		Dz1Json* json = NULL;\
//		if ((json = Dz1Json_new("UTF-8", spec, json_spec_name, errp)) == NULL) ERR_OUT(errp);\
//		else\
//		{\
//			pthread_cleanup_push(Dz1Json_delAndSetNull, (void*)&json);\
//			ssize_t sz;\
//			int cnt;\
//			if (json == NULL) ERR_OUT(errp);\
//			else if ((sz = Dz1Json_push_stream(json, jsonStr, strlen((const char*)jsonStr), errp)) < 0) ERR_OUT(errp);\
//			else if (sz != (ssize_t)strlen(jsonStr)) ERR_SET_OUT(errp, EFAULT);\
//			else if ((cnt = Dz1Json_parse(json, errp)) < 0) ERR_OUT(errp);\
//			else\
//			{\
//				StandardName##_Eam* eam = NULL;\
//				if ((eam = (StandardName##_Eam*)Dz1Json_read(json, errp)) == NULL) ERR_OUT(errp);\
//				else\
//				{\
//					pthread_cleanup_push(StandardName##_Eam_delAndSetNull, (void*)&eam);\
//					(StructName*)ret = StructName##_clone(eam->x.struct_name, errp);\
//					eam = NULL;\
//					Dz1Error_set(errp, 0);\
//					pthread_cleanup_pop(1);\
//				}\
//				json = NULL;\
//				Dz1Error_set(errp, 0);\
//			}\
//			pthread_cleanup_pop(1);\
//		}\
//	}\
//	pthread_cleanup_pop(1);\
//	return ret;\
//}
//
//
//#define Iso14827TestMsgUtilAPIEntry(oid_str, eam_list_struct, struct_name)\
//		{\
//			oid_str,\
//			eam_list_struct##_get_eam_list,\
//			eam_list_struct##_gen,\
//			eam_list_struct##_delAndSetNull,\
//			eam_list_struct##_convert,\
//			struct_name##_encode,\
//			struct_name##_decode,\
//			(Dz1DumpFunc)struct_name##_dump,\
//			(Dz1FDumpFunc)struct_name##_fdump,\
//			struct_name##_delAndSetNull\
//		}
//
//// Iso14827TestMsgStructAPI
/////////////////////////////////////////////////////////////////////////////////
//
//DZ1_CPPLINK_VAR Iso14827TestMsgStructAPI Iso14827TestMsgSet[];
//DZ1_CPPLINK_VAR Iso14827TestMsgStructAPI Iso14827TestMsgSetNoSub[];
//
/////////////////////////////////////////////////////////////////////////////////
//// MSG UTIL
//DZ1_CPPLINK Iso14827TestMsgStructAPI* Iso14827TestMsgSet_findAPI(Iso14827TestMsgStructAPI* tbl, Dz1Str oidStr, u32_t* ret_oid_idx);
//DZ1_CPPLINK Iso14827TestMsgStructAPI* Iso14827TestMsgSet_findByIDX(Iso14827TestMsgStructAPI* tbl, u32_t idx);
//DZ1_CPPLINK Dz1Binary* Iso14827TestMsgSet_getPublicationData(Iso14827TestMsgStructAPI* tbl, Dz1Str oidStr, Dz1Asn1Codec codec, Dz1Error* err);
//DZ1_CPPLINK	Dz1Binary* Iso14827TestMsgSet_getNullData(Dz1Asn1Codec codec, Dz1Error* err);
//

#endif // !ISO14827_TEST_HELPER_MSG_SET_H
