#ifndef ASNSYS_H_
#define ASNSYS_H_ 


#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "limits.h"

#define AVIOD_NAME_COLLISION_UTF8_STRING

/* Common Def */
#ifdef __cplusplus
#define ASN1_CPPLINK		extern "C"
#else
#define ASN1_CPPLINK
#endif

/************************************************************************/
/* OCTET String struct                                                  */
/************************************************************************/

#define  ASN1_MALLOC   malloc
#define  ASN1_REALLOC  realloc
#define  ASN1_FREE     free
#define PLUS 1.7e+308
#define MINUS -1.7e+308

typedef void ASNVoid;
typedef unsigned char ASNBOOL;
typedef unsigned char ASNUINT8;
typedef signed char ASNINT8;
typedef short int ASNINT16;
typedef unsigned short ASNUINT16;
typedef double ASNREAL;
typedef float ASNFLOAT;
typedef long ASNINT32L;
typedef unsigned long ASNUINT32L;
typedef int ASNINT32;
typedef unsigned int ASNUINT32;

#if defined(_WIN32) || defined(WIN32) || defined(__BORLANDC__) 
#define ASN1_CONST64(v) v##i64
#define ASN1_CONSTu64(v) v##ui64
typedef __int64 ASNINT64;
typedef unsigned  __int64 ASNUINT64;

#ifdef UNICODE
typedef wchar_t ASN1TCHAR;
#else
typedef char ASN1TCHAR;
#endif

#else
#define ASN1_CONST64(v) v##LL
#define ASN1_CONSTu64(v) v##LLU
typedef long long ASNINT64;
typedef unsigned  long long  ASNUINT64;

typedef char ASN1TCHAR;
#endif

typedef enum { UNCONS, CONS,SEMICONS } ASN1PERCons;

typedef enum { XER_REF,XER_PRI,XER_NULL} ASN1XERFlag;

typedef enum { ASN1IMPL, ASN1EXPL,UNASN1IMEXPL } ASN1TagType;

typedef enum {ALIGN,UNALIGN} ASN1PERAlign;

typedef enum {BASIC,CANONICAL} ASN1XERType;

typedef enum EnumTypeData 
{
	ASN1_TYPE_BOOLEAN = 1,
		ASN1_TYPE_INTEGER = 2,
		ASN1_TYPE_BITSTRING = 3,
		ASN1_TYPE_OCTETSTRING = 4,
		ASN1_TYPE_NULL = 5,
		ASN1_TYPE_OBJECTIDENTIFIER = 6,
		ASN1_TYPE_OBJECTDESCRIPION = 7,
		ASN1_TYPE_EXTERNAL = 8,
		ASN1_TYPE_INSTANCEOF = 8,
		ASN1_TYPE_REAL = 9,
		ASN1_TYPE_ENUMERATED = 10,
		ASN1_TYPE_EMBEDDEDPDV = 11,
		ASN1_TYPE_UFT8String = 12,
		ASN1_TYPE_RELATIVEOID = 13,
		ASN1_TYPE_SEQUENCE = 16,
		ASN1_TYPE_SEQUENCEOF = 16,
		ASN1_TYPE_SET = 17,
		ASN1_TYPE_SETOF = 17,
		ASN1_TYPE_NumericString = 18,
		ASN1_TYPE_PrintableString = 19,
		ASN1_TYPE_TeletexString = 20,
		ASN1_TYPE_T61String = 20,
		ASN1_TYPE_VideotexString = 21,
		ASN1_TYPE_IA5String = 22,
		ASN1_TYPE_UTCTime = 23,
		ASN1_TYPE_GeneralizedTime = 24,
		ASN1_TYPE_GraphicString = 25,
		ASN1_TYPE_VisibleString = 26,
		ASN1_TYPE_ISO646String = 26,
		ASN1_TYPE_GeneralString = 27,
		ASN1_TYPE_UniversalString = 28,
		ASN1_TYPE_CHARACTER_STRING = 29,
		ASN1_TYPE_BMPString = 30,
}ASN1_TagValue;

typedef struct Asn1ConsInfo
{
	ASNINT64 lower;
	ASNINT64 upper;
	ASNUINT8* charSet;
	ASNBOOL extflag;
	ASN1PERCons consType;
	ASNBOOL enumextbit;
	ASNBOOL BitVector;
} Asn1ConsInfo;

typedef struct ASN1ConsCheck
{
	ASNINT64 *StringforRange;
	ASNUINT8 *StringforAlphabet;
	ASNINT32 Length[2];/*1,INT;2,STRING*/
} ASN1ConsCheck;

typedef struct PER_Flag{
	ASNINT16  Is_Alphable;
	ASNINT16  Is_Size;
	ASNINT32  L_En_Flag;
	ASNINT32  V_En_Align;
	ASNINT32  Value_length;
	ASNINT32  Char_set_length;
	
	ASNINT16 ext_flag; 
	ASNUINT8* Alphable_table;
	ASNUINT8  Base_Letter;
	
	ASNINT64 Range;
	
	ASNUINT32 PER_Dec_Len;
}ASN1PER_F;


typedef struct ASN1_Buffer
{
	ASNUINT8* data;    	
	ASNUINT8* head;   
	ASNUINT8* end; 
	ASNUINT8* current;
	ASNUINT8* Vdeocd_valid;
	ASNUINT8* openType;
	ASNUINT16 bitOffset;		
	ASNUINT32 byteIndex;		
}ASN1_Buffer;




typedef struct ASN1_CtxtValue
{
	ASN1_Buffer buffer;     
	ASNINT32 dataSize;
	ASNINT32 iscons;
	struct mpool* Pmemory;
} ASN1WorkSpace;


#define ASN1_BER_ERROR_BEGIN -201
#define ASN1_BER_CHECK_LENGTH_ERROR  ASN1_BER_ERROR_BEGIN 
#define ASN1_BER_ERROR_END -400

#define ASN1_PER_ERROR_BEGIN -401
#define ASN1_PER_CHECK_LENGTH_ERROR  ASN1_PER_ERROR_BEGIN
#define ASN1_PER_ERROR_END -600

#define ASN1_XER_ERROR_BEGIN -601
#define ASN1_XER_CHECK_LENGTH_ERROR  ASN1_XER_ERROR_BEGIN
#define ASN1_XER_ERROR_END -800
 

#endif


		




