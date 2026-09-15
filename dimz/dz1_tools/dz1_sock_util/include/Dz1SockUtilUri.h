#ifndef DZ1_SOCK_UTIL_URI_H
#define DZ1_SOCK_UTIL_URI_H

#include <Dz1SockUtilUriDef.h>

#define							 Dz1SockUtilUriInfoU				Dz1SockUtilUriInfoA
#define							 Dz1SockUtilUriInfoU_new			Dz1SockUtilUriInfoA_new
#define							 Dz1SockUtilUriInfoU_gen			Dz1SockUtilUriInfoA_gen
#define							 Dz1SockUtilUriInfoU_clone			Dz1SockUtilUriInfoA_clone
#define							 Dz1SockUtilUriInfoU_del			Dz1SockUtilUriInfoA_del
#define							 Dz1SockUtilUriInfoU_delAndSetNull	Dz1SockUtilUriInfoA_delAndSetNull
#define							 Dz1SockUtilUriInfoU_dump			Dz1SockUtilUriInfoA_dump
DZ1_CPPLINK Dz1SockUtilUriInfoU *Dz1SockUtilUriInfoU_parse(str_t src_u8, Dz1Error *err);

DZ1_CPPLINK Dz1SockUtilUriInfoA	*Dz1SockUtilUriInfoA_parse(str_t src, Dz1Error *err);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK Dz1SockUtilUriInfoW	*Dz1SockUtilUriInfoW_parse(wstr_t src, Dz1Error *err);
#ifdef UNICODE
#define							 Dz1SockUtilUriInfo					Dz1SockUtilUriInfoW
#define							 Dz1SockUtilUriInfo_new				Dz1SockUtilUriInfoW_new
#define							 Dz1SockUtilUriInfo_gen				Dz1SockUtilUriInfoW_gen
#define							 Dz1SockUtilUriInfo_clone			Dz1SockUtilUriInfoW_clone
#define							 Dz1SockUtilUriInfo_del				Dz1SockUtilUriInfoW_del
#define							 Dz1SockUtilUriInfo_delAndSetNull	Dz1SockUtilUriInfoW_delAndSetNull
#define							 Dz1SockUtilUriInfo_dump			Dz1SockUtilUriInfoW_dump
#define							 Dz1SockUtilUriInfo_parse			Dz1SockUtilUriInfoW_parse
#else // UNICODE
#define							 Dz1SockUtilUriInfo					Dz1SockUtilUriInfoA
#define							 Dz1SockUtilUriInfo_new				Dz1SockUtilUriInfoA_new
#define							 Dz1SockUtilUriInfo_gen				Dz1SockUtilUriInfoA_gen
#define							 Dz1SockUtilUriInfo_clone			Dz1SockUtilUriInfoA_clone
#define							 Dz1SockUtilUriInfo_del				Dz1SockUtilUriInfoA_del
#define							 Dz1SockUtilUriInfo_delAndSetNull	Dz1SockUtilUriInfoA_delAndSetNull
#define							 Dz1SockUtilUriInfo_dump			Dz1SockUtilUriInfoA_dump
#define							 Dz1SockUtilUriInfo_parse			Dz1SockUtilUriInfoA_parse
#endif // UNICODE
#else // UNIX_SYSTEM
#define							 Dz1SockUtilUriInfo					Dz1SockUtilUriInfoA
#define							 Dz1SockUtilUriInfo_new				Dz1SockUtilUriInfoA_new
#define							 Dz1SockUtilUriInfo_gen				Dz1SockUtilUriInfoA_gen
#define							 Dz1SockUtilUriInfo_clone			Dz1SockUtilUriInfoA_clone
#define							 Dz1SockUtilUriInfo_del				Dz1SockUtilUriInfoA_del
#define							 Dz1SockUtilUriInfo_delAndSetNull	Dz1SockUtilUriInfoA_delAndSetNull
#define							 Dz1SockUtilUriInfo_dump			Dz1SockUtilUriInfoA_dump
#define							 Dz1SockUtilUriInfo_parse			Dz1SockUtilUriInfoA_parse
#endif // UNIX_SYSTEM


#endif // DZ1_SOCK_UTIL_URI_H
