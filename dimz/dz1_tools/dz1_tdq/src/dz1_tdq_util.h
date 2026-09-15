#ifndef DZ1_TDQ_UTIL_H_LOCAL
#define DZ1_TDQ_UTIL_H_LOCAL

#include <dz1_str.h>
#include <dz1_elastic_buf.h>
#include <dz1_tdq_util.h>

#define ELB_PUSH_STR(elb, str, ep)		do { if (Dz1ElasticBuf_pushStr(elb, str, ep) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0); } while(0)
#define ELB_PUSH_STRe(elb, str, ep)		do { if (Dz1ElasticBuf_pushStr(elb, str, ep) == FALSE) ERR_OUT_RET(errp, err); else Dz1Error_set(errp, 0); } while(0)
#define ELB_PUSH_STR_(elb, str, ep)		do { if (Dz1ElasticBuf_pushStr(elb, str, ep) == FALSE) ERR_OUT(errp); else Dz1Error_set(errp, 0); } while(0)

#define ELB_PUSH_CRLF(elb, ep)			do { if (Dz1ElasticBuf_pushStr(elb, Dz1Text("\r\n"), ep) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0); } while(0)
#define ELB_PUSH_CRLFe(elb, ep)			do { if (Dz1ElasticBuf_pushStr(elb, Dz1Text("\r\n"), ep) == FALSE) ERR_OUT_RET(errp, err); else Dz1Error_set(errp, 0); } while(0)
#define ELB_PUSH_CRLF_(elb, ep)			do { if (Dz1ElasticBuf_pushStr(elb, Dz1Text("\r\n"), ep) == FALSE) ERR_OUT_RET(errp); else Dz1Error_set(errp, 0); } while(0)

#define ELB_PUSH_CHR(elb, letter, ep)	do { if (Dz1ElasticBuf_pushChr(elb, letter, ep) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0); } while(0)
#define ELB_PUSH_CHRe(elb, letter, ep)	do { if (Dz1ElasticBuf_pushChr(elb, letter, ep) == FALSE) ERR_OUT_RET(errp, err); else Dz1Error_set(errp, 0); } while(0)
#define ELB_PUSH_CHR_(elb, letter, ep)	do { if (Dz1ElasticBuf_pushChr(elb, letter, ep) == FALSE) ERR_OUT(errp); else Dz1Error_set(errp, 0); } while(0)

#define ELB_PUSH_EOS(elb, ep)	do { if (Dz1ElasticBuf_pushChr(elb, 0, ep) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0); } while(0)
#define ELB_PUSH_EOSe(elb, ep)	do { if (Dz1ElasticBuf_pushChr(elb, 0, ep) == FALSE) ERR_OUT_RET(errp, err); else Dz1Error_set(errp, 0); } while(0)
#define ELB_PUSH_EOS_(elb, ep)	do { if (Dz1ElasticBuf_pushChr(elb, 0, ep) == FALSE) ERR_OUT(errp); else Dz1Error_set(errp, 0); } while(0)

#endif
