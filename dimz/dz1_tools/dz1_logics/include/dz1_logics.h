#ifndef DZ1_LOGICS_H
#define DZ1_LOGICS_H

#include <dz1_logics_def.h>

#ifndef UNIX_SYSTEM
#ifdef UNICODE
#define				Dz1LogicMatch				Dz1LogicMatchW
#define				Dz1LogicMatch_dump			Dz1LogicMatchW_dump
#else // UNICODE
#define				Dz1LogicMatch				Dz1LogicMatchA
#define				Dz1LogicMatch_dump			Dz1LogicMatchA_dump
#endif // UNICODE
#else // UNIX_SYSTEM
#define				Dz1LogicMatch				Dz1LogicMatchA
#define				Dz1LogicMatch_dump			Dz1LogicMatchA_dump
#endif // UNIX_SYSTEM

//DZ1_CPPLINK Dz1Error Dz1Logics_express(Dz1LogicMatchValueType type, void *addr_of_value, Dz1LogicMatch *match, bool_t *ret_status);
DZ1_CPPLINK Dz1Error Dz1LogicsA_express(Dz1LogicMatchValueType type, void *addr_of_value, Dz1LogicMatchA *match, bool_t *ret_status);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK Dz1Error Dz1LogicsW_express(Dz1LogicMatchValueType type, void *addr_of_value, Dz1LogicMatchW *match, bool_t *ret_status);
#ifdef UNICODE
#define					 Dz1Logics_express		Dz1LogicsW_express
#else // UNICODE
#define					 Dz1Logics_express		Dz1LogicsA_express
#endif // UNICODE
#else // UNIX_SYSTEM
#define					 Dz1Logics_express		Dz1LogicsA_express
#endif // UNIX_SYSTEM

#endif
