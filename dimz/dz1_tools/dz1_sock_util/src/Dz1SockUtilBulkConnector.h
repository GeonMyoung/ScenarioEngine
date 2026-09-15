#ifndef DZ1_SOCK_UTIL_BULK_CONNECTOR_H_LOCAL
#define DZ1_SOCK_UTIL_BULK_CONNECTOR_H_LOCAL

#include <Dz1SockUtil.h>

typedef struct Dz1SockUtilBulkConnectReqeust
{
	Dz1SockAddr				*peer;
	u32_t					 period;
	bool_t					 wait_and_connect;
	void					*userData;
	Dz1DelFunc				 userDataDel;
	bool_t					 isCanceled;
} Dz1SockUtilBulkConnectReqeust;			// with api dump, compare

DZ1_CPPLINK Dz1SockUtilBulkConnectReqeust *Dz1SockUtilBulkConnectReqeust_new(Dz1SockAddr *peer, u32_t period, bool_t wait_and_connect,
																			 void *userData, Dz1DelFunc userDataDel,
																			 Dz1Error *err);

DZ1_CPPLINK void Dz1SockUtilBulkConnectReqeust_del(Dz1SockUtilBulkConnectReqeust *p);
static __inline__ void Dz1SockUtilBulkConnectReqeust_delAndSetNull(void *ptr)
{
	Dz1SockUtilBulkConnectReqeust **p = (Dz1SockUtilBulkConnectReqeust **)ptr;
	Dz1SockUtilBulkConnectReqeust_del(*p); *p = NULL;
}

DZ1_CPPLINK void	 Dz1SockUtilBulkConnectReqeustA_dump(Dz1SockUtilBulkConnectReqeust *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK void	 Dz1SockUtilBulkConnectReqeustW_dump(Dz1SockUtilBulkConnectReqeust *p, int tab);
#ifdef UNICODE
#define				 Dz1SockUtilBulkConnectReqeust_dump		Dz1SockUtilBulkConnectReqeustW_dump
#else // UNICODE
#define				 Dz1SockUtilBulkConnectReqeust_dump		Dz1SockUtilBulkConnectReqeustA_dump
#endif // UNICODE
#else // UNIX_SYSTEM
#define				 Dz1SockUtilBulkConnectReqeust_dump		Dz1SockUtilBulkConnectReqeustA_dump
#endif // UNIX_SYSTEM
DZ1_CPPLINK int Dz1SockUtilBulkConnectReqeust_cmp(Dz1SockUtilBulkConnectReqeust *a, Dz1SockUtilBulkConnectReqeust *b);
#endif