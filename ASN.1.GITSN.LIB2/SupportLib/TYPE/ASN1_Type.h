#ifndef _ASN1_TYPE_H
#define _ASN1_TYPE_H
#include "../OS/ASN1_Sys.h"
/*
* Open Type
*/
typedef struct {
	ASNUINT32     numocts;
	ASNUINT8*     data;
} OpenType;

typedef ASNBOOL BOOLEAN;

typedef ASNINT64 INTEGER;

typedef struct BITSTRING
{  	
	ASNUINT32L	 numbits;  //effective bits 		
	ASNUINT8*	 data;     //encode data      
} BITSTRING;

typedef struct OCTETSTRING
{
	ASNUINT32		 numbits;	
	ASNUINT8*    	data;       	
} OCTETSTRING;

typedef struct {        
	ASNUINT32     numids;			
	ASNUINT32     subid[128];     
} OBJECTIDENTIFIER;

typedef ASNREAL REAL;

typedef ASNINT32 ENUMERATED;

typedef struct {        
	ASNUINT32     numids;		
	ASNUINT32     subid[128];    
} RELATIVE_OID; //roid struct

typedef struct 
{
	ASNINT32  nchar;
	ASNUINT8* asnstring;	
} ASNSTRING;

typedef struct BMPString{        
	ASNUINT32     nchar;	
	ASNUINT16*    data;     
} BMPString;

typedef struct UniversalString{        
	ASNUINT32     nchar;		
	ASNUINT32*    data;      
} UniversalString;

/*typedef OCTETSTRING CHARACTERSTRING;*/
#ifdef AVIOD_NAME_COLLISION_UTF8_STRING
typedef ASNSTRING UTF8Str;
#else
typedef ASNSTRING UTF8String;
#endif
typedef ASNSTRING NumericString;
typedef ASNSTRING PrintableString;
typedef ASNSTRING TeletexString;
typedef ASNSTRING VideotexString;
typedef ASNSTRING IA5String;
typedef ASNSTRING UTCTime;
typedef ASNSTRING GeneralizedTime;
typedef ASNSTRING GraphicString;
typedef ASNSTRING VisibleString;
typedef ASNSTRING GeneralString;
typedef ASNSTRING ObjectDescriptor;

/*CHARSTRING*/
struct ASN1CHARACTERSTRING_identification_syntaxes{
	OBJECTIDENTIFIER abstract;
	OBJECTIDENTIFIER transfer;
}; 
#ifndef STRUC_ASN1CHARACTERSTRING_identification_syntaxes
#define STRUC_ASN1CHARACTERSTRING_identification_syntaxes
typedef struct ASN1CHARACTERSTRING_identification_syntaxes ASN1CHARACTERSTRING_identification_syntaxes;
#endif

struct ASN1CHARACTERSTRING_identification_context_negotiation{
	INTEGER presentation_context_id;
	OBJECTIDENTIFIER transfer_syntax;
}; 
#ifndef STRUC_ASN1CHARACTERSTRING_identification_context_negotiation
#define STRUC_ASN1CHARACTERSTRING_identification_context_negotiation
typedef struct ASN1CHARACTERSTRING_identification_context_negotiation ASN1CHARACTERSTRING_identification_context_negotiation;
	#endif

#ifndef STRUC_ASN1CHARACTERSTRING_identification_syntaxes
#define STRUC_ASN1CHARACTERSTRING_identification_syntaxes
typedef struct ASN1CHARACTERSTRING_identification_syntaxes ASN1CHARACTERSTRING_identification_syntaxes;
#endif

#ifndef STRUC_ASN1CHARACTERSTRING_identification_context_negotiation
#define STRUC_ASN1CHARACTERSTRING_identification_context_negotiation
typedef struct ASN1CHARACTERSTRING_identification_context_negotiation ASN1CHARACTERSTRING_identification_context_negotiation;
#endif

struct ASN1CHARACTERSTRING_identification{
	ASNUINT64 M;
#define DEF_ASN1CHARACTERSTRING_identification_syntaxes	0
#define DEF_ASN1CHARACTERSTRING_identification_syntax	1
#define DEF_ASN1CHARACTERSTRING_identification_presentation_context_id	2
#define DEF_ASN1CHARACTERSTRING_identification_context_negotiation	3
#define DEF_ASN1CHARACTERSTRING_identification_transfer_syntax	4
#define DEF_ASN1CHARACTERSTRING_identification_fixed	5
	union {
		ASN1CHARACTERSTRING_identification_syntaxes* syntaxes;
		OBJECTIDENTIFIER syntax;
		INTEGER presentation_context_id;
		ASN1CHARACTERSTRING_identification_context_negotiation* context_negotiation;
		OBJECTIDENTIFIER transfer_syntax;
		ASNUINT8 fixed;	
	} elements; 
}; 

#ifndef STRUC_ASN1CHARACTERSTRING_identification
#define STRUC_ASN1CHARACTERSTRING_identification
typedef struct ASN1CHARACTERSTRING_identification ASN1CHARACTERSTRING_identification;
	#endif

#ifndef STRUC_ASN1CHARACTERSTRING_identification
#define STRUC_ASN1CHARACTERSTRING_identification
typedef struct ASN1CHARACTERSTRING_identification ASN1CHARACTERSTRING_identification;
#endif
struct ASN1CHARACTERSTRING{
	ASN1CHARACTERSTRING_identification* identification;
	OCTETSTRING string_value;
}; 
#ifndef STRUC_ASN1CHARACTERSTRING
#define STRUC_ASN1CHARACTERSTRING
typedef struct ASN1CHARACTERSTRING ASN1CHARACTERSTRING;
#endif
typedef ASN1CHARACTERSTRING CHARACTERSTRING;
#endif

