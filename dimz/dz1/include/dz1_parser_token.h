#ifndef DZ1_PARSER_TOKEN_H
#define DZ1_PARSER_TOKEN_H

#include <dz1.h>

#define DZ1_PARSER_TOKEN_LBRACKET				0x00000000 // (																			X
#define DZ1_PARSER_TOKEN_RBRACKET				0x00000001 // )																			X
#define DZ1_PARSER_TOKEN_LISTSTART				0x00000002 // {																			X
#define DZ1_PARSER_TOKEN_LISTEND				0x00000003 // }																			X
#define DZ1_PARSER_TOKEN_BLOCKSTART				0x00000004 // [																			X
#define DZ1_PARSER_TOKEN_BLOCKEND				0x00000005 // ]																			X

#define DZ1_PARSER_TOKEN_COLON					0x00000006 // :																			X
#define DZ1_PARSER_TOKEN_ASSIGN					0x00000007 // ::=																		X
#define DZ1_PARSER_TOKEN_EQUAL					0x00000008 // =																			X
#define DZ1_PARSER_TOKEN_BOOL_EQUAL				0x00000009 // ==																		X
#define DZ1_PARSER_TOKEN_BOOL_NOT				0x0000000A // !																			X
#define DZ1_PARSER_TOKEN_BOOL_NOTEQ				0x0000000B // !=																		X
#define DZ1_PARSER_TOKEN_DOT					0x0000000C // .																			X
#define DZ1_PARSER_TOKEN_DOTDOT					0x0000000D // ..																		X
#define DZ1_PARSER_TOKEN_DOTDOTDOT				0x0000000E // ...																		X
#define DZ1_PARSER_TOKEN_ALTERNATE				0x0000000F // |																			X
#define DZ1_PARSER_TOKEN_BOOL_OR				0x00000010 // ||																		X
#define DZ1_PARSER_TOKEN_COMMA					0x00000011 // ,																			X

#define DZ1_PARSER_TOKEN_LESS					0x00000012 // <																			x
//#define DZ1_PARSER_TOKEN_LESSEQ					0x00000013 // <=(, =<)																	x
#define DZ1_PARSER_TOKEN_GT						0x00000014 // >																			x
//#define DZ1_PARSER_TOKEN_GTEQ					0x00000015 // (>=,) =>																	x
#define DZ1_PARSER_TOKEN_PLUS					0x00000016 // +																			x
#define DZ1_PARSER_TOKEN_MINUS					0x00000017 // -																			x
#define DZ1_PARSER_TOKEN_MUL					0x00000018 // *																			x
#define DZ1_PARSER_TOKEN_DIV					0x00000019 // /																			x
#define DZ1_PARSER_TOKEN_POW					0x0000001A // ^                                                                         x
#define DZ1_PARSER_TOKEN_MOD					0x00000020 // %                                                                         x
#define DZ1_PARSER_TOKEN_SEMICOLON				0x00000021 // ;																			x
#define DZ1_PARSER_TOKEN_AND					0x00000022 // &																			x
#define DZ1_PARSER_TOKEN_BOOL_AND				0x00000023 // &&																		x
#define DZ1_PARSER_TOKEN_AT						0x00000024 // @																			x
#define DZ1_PARSER_TOKEN_HASH					0x00000025 // #																			x

#define DZ1_PARSER_TOKEN_SYMBOL					0x10000001 // [A-Z|a-z][A-Z|a-z|0-9|_|-]*												O
#define DZ1_PARSER_TOKEN_LITERAL				0x10000002 // $[A-Z|a-z][A-Z|a-z|0-9|_|-]*												O
#define DZ1_PARSER_TOKEN_STRING					0x10000003 // "[Any ASCII Letters]+"													O
#define DZ1_PARSER_TOKEN_LETTER					0x10000004 // '[A-Z|a-z]' or ('\x[0-9|A-F|a-f]' or '\[0-9]+' with decimal range 0~255)	O

#define DZ1_PARSER_TOKEN_NUMBER					0x20000000 // [+|-]*[0-9]+ or 0x[0-9|A-F|a-f]+ or 0b[0-1]+ or 0o[0-7]+					O

#define DZ1_PARSER_TOKEN_NUMBER_MASK			0xF0000000
#define DZ1_PARSER_TOKEN_isNUMBER(t)			(((t & DZ1_PARSER_TOKEN_NUMBER_MASK) == DZ1_PARSER_TOKEN_NUMBER) ? TRUE : FALSE)
// NUMBER Family
// 				  nnnnn		No Signed	Decimal
// 			 [+|-]nnnnn		Signed		Decimal
// 		[0x|0o|0b]nnnnn		No Signed,  Hex, Oct, Bin
// [+|-][0x|0o|0b]nnnnn		Signed,     Hex, Oct, Bin
// Last 5bit of TokkenType is
// SignSpecified(1) | TypeSpecified(1) | SignIndicator(1) | TypeBit(2)
#define NUMBER_SIGN_SPECIFIED						0x00000010	// '+' or '-' is presented
//#define NUMBER_SIGN_INDICATED						0x00000008	// Signed Bit

//#define NUMBER_TYPE_SPECIFIED						0x00000008	// '0x' or '0o' or '0b' is presented

#define NUMBER_TYPE_MASK							0x0000000F

#define NUMBER_DECIMAL								0x00000001	// Decimal Type		: 1234567890
#define NUMBER_HEXA									0x00000002	// Hex Type			: 123456789ABCDEF0
#define NUMBER_OCT									0x00000003	// Octal Type		: 12345670
#define NUMBER_BIN									0x00000004	// Binary Type		: 10

#define NUMBER_FLOAT								0x00000008	// float type		: 1.23
#define NUMBER_EXPONENT								0x00000009	// exponent type	: 2.34E-4, 34.56E+3, 1E+6


// Marco for Match Condition
#define DZ1_PARSER_TOKEN_NUMBER_S(sign)			(DZ1_PARSER_TOKEN_NUMBER | ((sign) ? NUMBER_SIGN_SPECIFIED : 0) )
#define DZ1_PARSER_TOKEN_NUMBER_T(type)			(DZ1_PARSER_TOKEN_NUMBER | (type) )
#define DZ1_PARSER_TOKEN_NUMBER_ST(flag, type)	(DZ1_PARSER_TOKEN_NUMBER | ((flag) ? NUMBER_SIGN_SPECIFIED : 0) | (type) )

// Lex Make These Tokens
// #define DZ1_PARSER_TOKEN_NUMBER_SU_D			(DZ1_PARSER_TOKEN_NUMBER |							NUMBER_TYPE_SPECIFIED | NUMBER_DECIMAL) //	 [0-9]+
// #define DZ1_PARSER_TOKEN_NUMBER_SU_H			(DZ1_PARSER_TOKEN_NUMBER |							NUMBER_TYPE_SPECIFIED | NUMBER_HEXA)	// 0x[0-9|A-F]+
// #define DZ1_PARSER_TOKEN_NUMBER_SU_O			(DZ1_PARSER_TOKEN_NUMBER |							NUMBER_TYPE_SPECIFIED | NUMBER_OCT)		// 0o[0-7]+
// #define DZ1_PARSER_TOKEN_NUMBER_SU_B			(DZ1_PARSER_TOKEN_NUMBER |							NUMBER_TYPE_SPECIFIED | NUMBER_BIN)		// 0b[0-1]+
// 
// #define DZ1_PARSER_TOKEN_NUMBER_SI_D			(DZ1_PARSER_TOKEN_NUMBER | NUMBER_SIGN_SPECIFIED |	NUMBER_TYPE_SPECIFIED | NUMBER_DECIMAL)	// [+|-][0-9]+
// #define DZ1_PARSER_TOKEN_NUMBER_SI_H			(DZ1_PARSER_TOKEN_NUMBER | NUMBER_SIGN_SPECIFIED |	NUMBER_TYPE_SPECIFIED | NUMBER_HEXA)	// [+|-]0x[0-9|A-F]+
// #define DZ1_PARSER_TOKEN_NUMBER_SI_O			(DZ1_PARSER_TOKEN_NUMBER | NUMBER_SIGN_SPECIFIED |	NUMBER_TYPE_SPECIFIED | NUMBER_OCT)		// [+|-]0o[0-7]+
// #define DZ1_PARSER_TOKEN_NUMBER_SI_B			(DZ1_PARSER_TOKEN_NUMBER | NUMBER_SIGN_SPECIFIED |	NUMBER_TYPE_SPECIFIED | NUMBER_BIN)		// [+|-]0b[0-1]+

#define DZ1_PARSER_TOKEN_DONE					0xF0000001 // End of FILE																X
#define DZ1_PARSER_TOKEN_NONE					0xF0000002 // Unknown Token																X

#define DZ1_PARSER_TOKEN_STATUS_FRESH			0x00000000
#define DZ1_PARSER_TOKEN_STATUS_OLD				0x00000001
#define DZ1_PARSER_TOKEN_STATUS_EMIT			0x00000002

typedef struct Dz1ParserToken
{
	__DZ1ALIGN(u32_t, t);
	__DZ1ALIGN(str_t, v);
} Dz1ParserToken;

#endif
