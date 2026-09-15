#ifndef DZ1_BIN_H
#define DZ1_BIN_H

#include <dz1_error.h>
#define Dz1ArrElCnt(el_type, var_name)		(sizeof(var_name) / sizeof(el_type))
#define Dz1ArrParam(el_type, var_name)		var_name, Dz1ArrElCnt(el_type, var_name)
typedef struct Dz1Binary
{
	u8_t *data;
	u32_t size;
} Dz1Binary;

#define DZ1_BIN_DATA_ALLOC				((u8_t *)-1)

#define								 Dz1Binary_new(dp, sz, errp) _Dz1Binary_new((dp), (sz), (errp), __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT Dz1Binary  *_Dz1Binary_new(u8_t *data, u32_t size, Dz1Error *err, const char *__file__, int __line__);
DZ1_CPPLINK DZ1_DLLPORT void		*Dz1Binary_gen(Dz1Error *err);
#define								 Dz1Binary_copy(dp, sp, ep)	_Dz1Binary_copy(dp, sp, ep, __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT bool_t		_Dz1Binary_copy(Dz1Binary *dst, Dz1Binary *src, Dz1Error *err, const char *__file__, int __line__);
#define								 Dz1Binary_clone(srcp, errp) _Dz1Binary_clone((srcp), (errp), __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT Dz1Binary  *_Dz1Binary_clone(Dz1Binary *src, Dz1Error *err, const char *__file__, int __line__);
DZ1_CPPLINK DZ1_DLLPORT void		 Dz1Binary_purge(Dz1Binary *p);
DZ1_CPPLINK DZ1_DLLPORT void		 Dz1Binary_del(Dz1Binary *p);
static __inline__ void				 Dz1Binary_delAndSetNull(void *ptr)
{
	Dz1Binary **p = (Dz1Binary **)ptr;
	Dz1Binary_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT int			 Dz1Binary_cmp(Dz1Binary *a, Dz1Binary *b);

DZ1_CPPLINK DZ1_DLLPORT void		 Dz1BinaryA_dump(Dz1Binary *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void		 Dz1BinaryA_dumpPartial(Dz1Binary *p, int tab, size_t dump_size);
DZ1_CPPLINK DZ1_DLLPORT void		 Dz1BinaryA_fdump(FILE *fp, Dz1Binary *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void		 Dz1BinaryW_dump(Dz1Binary *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void		 Dz1BinaryW_dumpPartial(Dz1Binary *p, int tab, size_t dump_size);
DZ1_CPPLINK DZ1_DLLPORT void		 Dz1BinaryW_fdump(FILE *fp, Dz1Binary *p, int tab);
#ifdef UNICODE
#define								 Dz1Binary_dump				Dz1BinaryW_dump
#define								 Dz1Binary_dumpPartial		Dz1BinaryW_dumpPartial
#define								 Dz1Binary_fdump			Dz1BinaryW_fdump
#else // UNICODE
#define								 Dz1Binary_dump				Dz1BinaryA_dump
#define								 Dz1Binary_dumpPartial		Dz1BinaryA_dumpPartial
#define								 Dz1Binary_fdump			Dz1BinaryA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define								 Dz1Binary_dump				Dz1BinaryA_dump
#define								 Dz1Binary_dumpPartial		Dz1BinaryA_dumpPartial
#define								 Dz1Binary_fdump			Dz1BinaryA_fdump
#endif // UNIX_SYSTEM

#define								 Dz1Binary2							 Dz1Binary
#define								 Dz1Binary2_new(dp, sz, errp)		_Dz1Binary_new((dp), (sz), (errp), __FILE__, __LINE__)
#define								 Dz1Binary2_gen(ep)					 Dz1Binary_gen(ep)
#define								 Dz1Binary2_copy(dp, sp, ep)		_Dz1Binary_copy(dp, sp, ep, __FILE__, __LINE__)
#define								 Dz1Binary2_clone(sp, ep)			_Dz1Binary_clone(sp, ep, __FILE__, __LINE__)
#define								 Dz1Binary2_purge(ptr)				 Dz1Binary_purge(ptr)
#define								 Dz1Binary2_del(ptr)				 Dz1Binary_del(ptr)
#define								 Dz1Binary2_delAndSetNull			 Dz1Binary_delAndSetNull
#define								 Dz1Binary2A_dump(ptr, tab)			 Dz1BinaryA_dumpPartial(ptr, tab, 16)
#define								 Dz1Binary2A_fdump(fp, ptr, tab)	 Dz1BinaryA_fdump(fp, ptr, tab)
#ifndef UNIX_SYSTEM
#define								 Dz1Binary2W_dump(ptr, tab)			 Dz1BinaryW_dumpPartial(ptr, tab, 16)
#define								 Dz1Binary2W_fdump(fp, ptr, tab)	 Dz1BinaryW_fdump(fp, ptr, tab)
#ifdef UNICODE
#define								 Dz1Binary2_dump					 Dz1Binary2W_dump
#define								 Dz1Binary2_fdump					 Dz1Binary2W_fdump
#else // UNICODE
#define								 Dz1Binary2_dump					 Dz1Binary2A_dump
#define								 Dz1Binary2_fdump					 Dz1Binary2A_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define								 Dz1Binary2_dump					 Dz1Binary2A_dump
#define								 Dz1Binary2_fdump					 Dz1Binary2A_fdump
#endif // UNIX_SYSTEM
#define								 Dz1Binary2_cmp(ptra, ptrb)			 Dz1Binary_cmp(ptra, ptrb)

#endif
