#ifndef ITS_ISO_14827_TYPES_H
#define ITS_ISO_14827_TYPES_H

#include <dz1_sock_addr.h>

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827SessionKey
typedef struct ItsIso14827SessionKey
{
	Dz1SockAddr *peer;
	Dz1SockAddr *local;
	u32_t        sid;
} ItsIso14827SessionKey;

#define												 ItsIso14827SessionKey_new(peerp, localp, sid, ep)	_ItsIso14827SessionKey_new(peerp, localp, sid, ep, __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827SessionKey	   *_ItsIso14827SessionKey_new(Dz1SockAddr *peer, Dz1SockAddr *local, u32_t sid, Dz1Error *err, const char *__file, int __line);
static __inline__ ItsIso14827SessionKey			  *__ItsIso14827SessionKey_new(Dz1SockAddr *peer, Dz1SockAddr *local, u32_t sid, Dz1Error *err) { return ItsIso14827SessionKey_new(peer, local, sid, err); }

#define												 ItsIso14827SessionKey_gen(ep)						_ItsIso14827SessionKey_gen(ep, __FILE__, __LINE__)
static __inline__ ItsIso14827SessionKey			   *_ItsIso14827SessionKey_gen(Dz1Error *err, const char *__file, int __line) { return _ItsIso14827SessionKey_new(NULL, NULL, 0, err, __file, __line); }
static __inline__ ItsIso14827SessionKey			  *__ItsIso14827SessionKey_gen(Dz1Error *err) { return ItsIso14827SessionKey_gen(err); }

#define												 ItsIso14827SessionKey_clone(srcp, ep) _ItsIso14827SessionKey_clone(srcp, ep, __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827SessionKey	   *_ItsIso14827SessionKey_clone(ItsIso14827SessionKey *src, Dz1Error *err, const char *__file, int __line);
static __inline__ ItsIso14827SessionKey			  *__ItsIso14827SessionKey_clone(ItsIso14827SessionKey *src, Dz1Error *err) { return ItsIso14827SessionKey_clone(src, err); }

DZ1_CPPLINK DZ1_DLLPORT void						 ItsIso14827SessionKey_del(ItsIso14827SessionKey *p);
static __inline__ void								 ItsIso14827SessionKey_delAndSetNull(void *ptr)
{
	ItsIso14827SessionKey **p = (ItsIso14827SessionKey **)ptr;
	ItsIso14827SessionKey_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void						 ItsIso14827SessionKey_dump(ItsIso14827SessionKey *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int							 ItsIso14827SessionKey_cmp(ItsIso14827SessionKey *a, ItsIso14827SessionKey *b);
// ItsIso14827SessionKey
////////////////////////////////////////////////////////////////////////////////

#endif
