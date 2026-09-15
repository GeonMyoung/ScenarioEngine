#include <dz1_thread_stdio.h>

#include <Dz1Json.h>
#include "Dz1JsonFifo.h"
#include "Dz1JsonLexer.h"

#ifndef	UNIX_SYSTEM
#ifdef	UNICODE
#define _elb_putc				_elb_putcW
#define _elb_to_str				_elbW_to_str
#else// UNICODE
#define _elb_putc				_elb_putcA
#define _elb_to_str				_elbA_to_str
#endif//UNICODE
#else// UNIX_SYSTEM
#define _elb_putc				_elb_putcU8
#define _elb_to_str				_elbA_to_str
#endif

#ifndef UNIX_SYSTEM
static bool_t _elb_putcA(Dz1ElasticBuf *dst, SingleChar c32, Dz1Error *err)
{	// mbcs에서는 최대 2바이트까지 사용
	DZ1_ERROR_SAFE_PTR(errp, err);
	
	u8_t c[2] = { (c32 >> 8) & 0xFF, (c32 >> 0) & 0xFF }, *cp = c;
	if (*cp != 0)
	{
		if ((*errp = Dz1ElasticBuf_push(dst, c, 2)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		cp++;
		if ((*errp = Dz1ElasticBuf_push(dst, cp, 1)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _elb_putcW(Dz1ElasticBuf *dst, SingleChar c32, Dz1Error *err)
{	// wcs에서는 항상 2Byte 또는 4Byte 사용
	DZ1_ERROR_SAFE_PTR(errp, err);
#if DZ1_ENDIAN == DZ1_ENDIAN_BIG
	u8_t c[4] = { (u8_t)((c32 >> 24) & 0xFF), (u8_t)((c32 >> 16) & 0xFF), (u8_t)((c32 >> 8) & 0xFF), (u8_t)((c32 >> 0) & 0xFF) };
	if (c[0] > 0 || c[1] > 0)
	{
		if ((*errp = Dz1ElasticBuf_push(dst, c, 4)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		if ((*errp = Dz1ElasticBuf_push(dst, &c[2], 2)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
#elif DZ1_ENDIAN == DZ1_ENDIAN_LITTLE
	u8_t c[4] = { (u8_t)((c32 >> 0) & 0xFF), (u8_t)((c32 >> 8) & 0xFF), (u8_t)((c32 >> 16) & 0xFF), (u8_t)((c32 >> 24) & 0xFF) };
	if (c[2] > 0 || c[3] > 0)
	{
		if ((*errp = Dz1ElasticBuf_push(dst, c, 4)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		if ((*errp = Dz1ElasticBuf_push(dst, c, 2)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
#else
#error "No Endian"
#endif
	return errp->code == 0 ? TRUE : FALSE;
}
#else
static bool_t _elb_putcU8(Dz1ElasticBuf *dst, SingleChar c32, Dz1Error *err)
{	// mbcs에서는 항상 2Byte 또는 4Byte 사용
	DZ1_ERROR_SAFE_PTR(errp, err);
	u8_t c[4] = { (u8_t)((c32 >> 24) & 0xFF), (u8_t)((c32 >> 16) & 0xFF), (u8_t)((c32 >> 8) & 0xFF), (u8_t)((c32 >> 0) & 0xFF) };
	u8_t *cp = c;
	size_t sz = 4;
	while(*cp == 0 && sz > 0) { cp++, sz--; }
	if (sz == 0)
	{
		if ((*errp = Dz1ElasticBuf_push(dst, c, 1)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		if ((*errp = Dz1ElasticBuf_push(dst, cp, sz)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
#endif
static Dz1Str _elbA_to_str(Dz1ElasticBuf *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Str ret = NULL;
	Dz1Binary const * const bin = Dz1ElasticBuf_flatten(src, errp);
	if (bin == NULL)
	{
		if (errp->code != ENOENT) ERR_OUT(errp);
		// empty string
		else if ((ret = Dz1Calloc(sizeof(u8_t), 1, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if ((ret = Dz1Calloc(sizeof(u8_t), bin->size + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		memcpy(ret, bin->data, bin->size);
		Dz1Error_set(errp, 0);
	}
	return ret;
}

#ifndef UNIX_SYSTEM
static Dz1Str _elbW_to_str(Dz1ElasticBuf *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Str ret = NULL;
	Dz1Binary const * const bin = Dz1ElasticBuf_flatten(src, errp);
	if (bin == NULL)
	{
		if (errp->code != ENOENT) ERR_OUT(errp);
		// empty string
		else if ((ret = Dz1Calloc(sizeof(wchar_t), 1, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		size_t len = bin->size / sizeof(wchar_t);
		if ((ret = Dz1Calloc(sizeof(wchar_t), len + 1, errp)) == NULL) ERR_OUT(errp);
		else
		{
			memcpy(ret, bin->data, bin->size);
			Dz1Error_set(errp, 0);
		}
	}
	return ret;
}
#endif

static Dz1JsonTokenType _lex_simple_letter(u32_t c32)
{
	Dz1JsonTokenType ret = Dz1JsonTokenType_max;

	switch(c32)
	{
	case (u32_t)',':
		ret = Dz1JsonTokenType_comma;
		break;
	case (u32_t)'.':
		ret = Dz1JsonTokenType_dot;
		break;
	case (u32_t)' ':
	case (u32_t)'\t':
	case (u32_t)'\r':
	case (u32_t)'\n':
		ret = Dz1JsonTokenType_white_space;
		break;
	case (u32_t)'{':
		ret = Dz1JsonTokenType_lst_start;
		break;
	case (u32_t)'}':
		ret = Dz1JsonTokenType_lst_end;
		break;
	case (u32_t)'[':
		ret = Dz1JsonTokenType_blk_start;
		break;
	case (u32_t)']':
		ret = Dz1JsonTokenType_blk_end;
		break;
	case (u32_t)':':
		ret = Dz1JsonTokenType_colon;
		break;
	case (u32_t)'\"':
		ret = Dz1JsonTokenType_string;
		break;
	default:
		if ((c32 >= (u32_t)'0' && c32 <= (u32_t)'9') || c32 == (u32_t)'-') ret = Dz1JsonTokenType_number;
		else ret = Dz1JsonTokenType_symbol;
		break;
	}
	return ret;
}

typedef struct LexerApiMap
{
	Dz1JsonTokenType	 type;
	bool_t				 (*init)(Dz1JsonLexer *lex, SingleChar first_c, Dz1Error *err);

	// ret == NULL => (errp->code == EAGAIN) or critical
	Dz1JsonToken		*(*lex)(Dz1JsonLexer *lex, Dz1JsonFifo *src, Dz1Error *err);
	Dz1JsonLexerState	 state;
} LexerApiMap;

static bool_t Dz1JsonLexer_lexStringInit(Dz1JsonLexer *lex, SingleChar first_c, Dz1Error *err)
{
	bool_t ret = TRUE;
	Dz1ElasticBuf_empty(lex->buf);
	lex->flags = 0;
	return ret;
}

static bool_t _is_digit(u32_t c)
{
	bool_t ret = FALSE;
	if (c >= (u32_t)'0' && c <= (u32_t)'9') ret = TRUE;
	return ret;
}
static bool_t _is_hex(u32_t c)
{
	bool_t ret = FALSE;
	if (0) { }
	else if (c >= (u32_t)'A' && c <= (u32_t)'F') ret = TRUE;
	else if (c >= (u32_t)'a' && c <= (u32_t)'f') ret = TRUE;
	else ret = _is_digit(c);
	return ret;
}

static u32_t _to_value_from_digit(u32_t c)
{
	u32_t ret = 0;
	if (c >= (u32_t)'0' && c <= (u32_t)'9') ret = c - (u32_t)'0';
	return ret;
}

static u32_t _to_value_from_hex(u32_t c)
{
	u32_t ret = 0;
	if (0) { }
	else if (c >= (u32_t)'A' && c <= (u32_t)'F') ret = (c - (u32_t)'A') + 10;
	else if (c >= (u32_t)'a' && c <= (u32_t)'f') ret = (c - (u32_t)'a') + 10;
	else ret = _to_value_from_digit(c);
	return ret;
}

static Dz1JsonToken *Dz1JsonLexer_lexString(Dz1JsonLexer *lex, Dz1JsonFifo *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonToken *ret = NULL;

	int status = 0;
	bool_t done = FALSE;
	SingleChar c32 = 0;
	while(errp->code == 0 && done == FALSE)
	{
		if ((status = Dz1JsonFifo_getC(src, &c32, errp)) < 0) ERR_OUT(errp);	// read error
		else if (status == 0)
		{
			Dz1Error_set(errp, EAGAIN);						// need more data
		}
		else if (lex->flags == 1)							// escaped state
		{
			if (c32 == (u32_t)'u')
			{
				lex->flags = 2;		// set to character code parsing
				lex->temp = 0;		// init temp
				lex->t_len = 4;		// init length
			}
			else
			{	// single escaped letter
				lex->flags = 0;
				switch(c32)
				{
				case (u32_t)'t':	c32 = (u32_t)'\t';		break;
				case (u32_t)'n':	c32 = (u32_t)'\n';		break;
				case (u32_t)'r':	c32 = (u32_t)'\r';		break;
				default:			/* no change c32 */		break;
				}

				if (_elb_putc(lex->buf, c32, errp) == FALSE) ERR_OUT(errp);
				else
				{
					Dz1Error_set(errp, 0);
				}
			}
		}
		else if (lex->flags == 2)							// character code parsing
		{	
			if (_is_hex(c32) == FALSE) ERR_SET_OUT(errp, EINVAL);
			else
			{
				u32_t v = _to_value_from_hex(c32);
				lex->temp = (lex->temp << 4) | v;
				lex->t_len--;

				if (lex->t_len == 0)
				{
					lex->flags = 0;
					if (_elb_putc(lex->buf, lex->temp, errp) == FALSE) ERR_OUT(errp);
					else
					{
						Dz1Error_set(errp, 0);
						lex->temp = 0;
					}
				}
			}
		}
		// terminate of string
		else if (c32 == (u32_t)'\"')
		{
			done = TRUE;
		}
		// Set Escape to TRUE
		else if (c32 == (u32_t)'\\')
		{
			lex->flags = 1;		// 1 more byte
		}
		// Put in to Buffer
		else
		{
//			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "Dz1JsonLexer_lexString() : Letter = 0x%08X\n", c32);
			if (_elb_putc(lex->buf, c32, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
	}

	if (errp->code == 0 && done == TRUE)
	{
		if ((ret = Dz1JsonToken_new(Dz1JsonTokenType_string, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1JsonToken_delAndSetNull, (void *)&ret);
			if ((ret->v = _elb_to_str(lex->buf, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(errp->code); // (Dz1JsonToken_delAndSetNull, (void *)&ret);
		}
	}
	return ret;
}

static bool_t Dz1JsonLexer_lexNumberInit(Dz1JsonLexer *lex, SingleChar first_c, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	bool_t ret = FALSE;

	u32_t pos = 0;
	Dz1JsonNumberParse mode = Dz1JsonNumberParse_undef;

	if (first_c == (SingleChar)'-' || (first_c >= (SingleChar)'1' && first_c <= (SingleChar)'9')) 
		mode = Dz1JsonNumberParse_decimal;

	Dz1ElasticBuf_empty(lex->buf);
	if ((ret = _elb_putc(lex->buf, first_c, errp)) == FALSE) ERR_OUT(errp);
	else
	{
		pos++;
		Dz1Error_set(errp, 0);
		lex->flags = (((u32_t)mode & 0xF ) << 28) | (pos & 0xFF);
	}

	return ret;
}

static Dz1JsonToken *Dz1JsonLexer_lexNumber(Dz1JsonLexer *lex, Dz1JsonFifo *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonToken *ret = NULL;

	int status = 0;
	bool_t done = FALSE;
	SingleChar c32 = 0;
	Dz1JsonNumberParse	mode		= (lex->flags >> 28) & 0xF;
	u32_t				pos			=  lex->flags        & 0xFF;
	bool_t				dot			= (lex->flags        & 0x100) ? TRUE : FALSE;
	bool_t				ucase_expo	= (lex->flags        & 0x200) ? TRUE : FALSE;;
	while(errp->code == 0 && done == FALSE)
	{
		if ((status = Dz1JsonFifo_getC(src, &c32, errp)) < 0) ERR_OUT(errp);
		else if (status == 0) Dz1Error_set(errp, EAGAIN);
		else
		{
			switch(mode)
			{
			case Dz1JsonNumberParse_undef:	// => first is '0', pos == 1 (next can be 'x' 'X' 'o' 'O' 'b' 'B' '0~9', '.')
				switch(c32)
				{
				case (SingleChar)'x': case (SingleChar)'X':
					mode = Dz1JsonNumberParse_hex;
					if (_elb_putc(lex->buf, c32, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
					break;
				case (SingleChar)'o': case (SingleChar)'O':
					mode = Dz1JsonNumberParse_oct;
					if (_elb_putc(lex->buf, c32, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
					break;
				case (SingleChar)'b': case (SingleChar)'B':
					mode = Dz1JsonNumberParse_binary;
					if (_elb_putc(lex->buf, c32, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
					break;
				case (SingleChar)'.':
					dot = TRUE;
					mode = Dz1JsonNumberParse_decimal;
					if (_elb_putc(lex->buf, c32, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
					break;
				default:
					if (c32 >= (SingleChar)'0' && c32 <= (SingleChar)'9')
					{
						mode = Dz1JsonNumberParse_decimal;
						if (_elb_putc(lex->buf, c32, errp) == FALSE) ERR_OUT(errp);
						else Dz1Error_set(errp, 0);
					}
					else
					{
						Dz1JsonFifo_ungetC(src, c32, NULL);
						done = TRUE;
					}
					break;
				}
				break;
			case Dz1JsonNumberParse_decimal:	// 0~9, '.', 'e', 'e'
				if (c32 >= (SingleChar)'0' && c32 <= (SingleChar)'9')
				{
					if (_elb_putc(lex->buf, c32, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}
				else if (c32 == (SingleChar)'.' && dot == FALSE)
				{
					dot = TRUE;
					if (_elb_putc(lex->buf, c32, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}
				else if (c32 == (SingleChar)'e' || c32 == (SingleChar)'E')
				{
					if (dot == FALSE)
					{
						Dz1JsonFifo_ungetC(src, c32, NULL);
						done = TRUE;
					}
					else
					{
						if (c32 == (SingleChar)'E') ucase_expo = TRUE;
						else ucase_expo = FALSE;

						mode = Dz1JsonNumberParse_exponent;
					}
				}
				else
				{
					Dz1JsonFifo_ungetC(src, c32, NULL);
					done = TRUE;
				}
				break;
			case Dz1JsonNumberParse_exponent:
				if (c32 == (SingleChar)'+' || c32 == (SingleChar)'-')
				{
					mode = Dz1JsonNumberParse_exp_digit;
					if (_elb_putc(lex->buf, (SingleChar)'e', errp) == FALSE) ERR_OUT(errp);
					else if (_elb_putc(lex->buf, c32, errp) == FALSE) ERR_OUT(errp);
				}
				else
				{
					u32_t expo = ucase_expo ? (SingleChar)'E' : (SingleChar)'e';
					Dz1JsonFifo_ungetC(src, c32, NULL);
					Dz1JsonFifo_ungetC(src, expo, NULL);
					done = TRUE;
				}
				break;
			case Dz1JsonNumberParse_exp_digit:
				if (c32 >= (SingleChar)'0' && c32 <= (SingleChar)'9')
				{
					if (_elb_putc(lex->buf, c32, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}
				else
				{
					Dz1JsonFifo_ungetC(src, c32, NULL);
					done = TRUE;
				}
				break;
			case Dz1JsonNumberParse_hex:	// 0~9, A~F, a~f
				if ((c32 >= (SingleChar)'0' && c32 <= (SingleChar)'9') ||
					(c32 >= (SingleChar)'A' && c32 <= (SingleChar)'F') ||
					(c32 >= (SingleChar)'a' && c32 <= (SingleChar)'f'))
				{
					if (_elb_putc(lex->buf, c32, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}
				else
				{
					Dz1JsonFifo_ungetC(src, c32, NULL);
					done = TRUE;
				}
				break;
			case Dz1JsonNumberParse_oct:	// 0~7
				if (c32 >= (SingleChar)'0' && c32 <= (SingleChar)'7')
				{
					if (_elb_putc(lex->buf, c32, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}
				else
				{
					Dz1JsonFifo_ungetC(src, c32, NULL);
					done = TRUE;
				}
				break;
			case Dz1JsonNumberParse_binary:	// 0~1
				if (c32 >= (SingleChar)'0' && c32 <= (SingleChar)'1')
				{
					if (_elb_putc(lex->buf, c32, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}
				else
				{
					Dz1JsonFifo_ungetC(src, c32, NULL);
					done = TRUE;
				}
				break;
			default:
				break;
			}
		}
	}

	lex->flags = (((u32_t)mode & 0xF ) << 28) | (pos & 0xFF);
	if (dot) lex->flags |= 0x100;
	if (ucase_expo) lex->flags |= 0x200;

	if (errp->code == 0 && done == TRUE)
	{
		if ((ret = Dz1JsonToken_new(Dz1JsonTokenType_number, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1JsonToken_delAndSetNull, (void *)&ret);
			if ((ret->v = _elb_to_str(lex->buf, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(errp->code); // (Dz1JsonToken_delAndSetNull, (void *)&ret);
		}
	}
	return ret;
}

static bool_t Dz1JsonLexer_lexSymbolInit(Dz1JsonLexer *lex, SingleChar first_c, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	bool_t ret = FALSE;

	lex->flags = 0;
	Dz1ElasticBuf_empty(lex->buf);
	if ((ret = _elb_putc(lex->buf, first_c, errp)) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ret;
}

static Dz1JsonToken *Dz1JsonLexer_lexSymbol(Dz1JsonLexer *lex, Dz1JsonFifo *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonToken *ret = NULL;

	int status = 0;
	bool_t done = FALSE;
	SingleChar c32 = 0;
	while(errp->code == 0 && done == FALSE)
	{
		if ((status = Dz1JsonFifo_getC(src, &c32, errp)) < 0) ERR_OUT(errp);
		else if (status == 0) Dz1Error_set(errp, EAGAIN);
		else 
		{
			Dz1JsonTokenType type = _lex_simple_letter(c32);
			switch(type)
			{
			case Dz1JsonTokenType_dot:
			case Dz1JsonTokenType_plus:
			case Dz1JsonTokenType_minus:
			case Dz1JsonTokenType_number:
			case Dz1JsonTokenType_symbol:
				if (_elb_putc(lex->buf, c32, errp) == FALSE) ERR_OUT(errp);
				break;
			default:
				Dz1JsonFifo_ungetC(src, c32, NULL);
				done = TRUE;
				break;
			}
		}
	}

	if (errp->code == 0 && done == TRUE)
	{
		if ((ret = Dz1JsonToken_new(Dz1JsonTokenType_symbol, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1JsonToken_delAndSetNull, (void *)&ret);
			if ((ret->v = _elb_to_str(lex->buf, errp)) == NULL) ERR_OUT(errp);
			else
			{
				if (Dz1STRCMP(ret->v, Dz1Text("null")) == 0) ret->t = Dz1JsonTokenType_nul;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(errp->code); // (Dz1JsonToken_delAndSetNull, (void *)&ret);
		}
	}
	return ret;
}

static LexerApiMap lexerApiMap[] =
{
	{ Dz1JsonTokenType_string, Dz1JsonLexer_lexStringInit, Dz1JsonLexer_lexString, Dz1JsonLexerState_string_lexing },
	{ Dz1JsonTokenType_number, Dz1JsonLexer_lexNumberInit, Dz1JsonLexer_lexNumber, Dz1JsonLexerState_number_lexing },
	{ Dz1JsonTokenType_plus,  Dz1JsonLexer_lexNumberInit, Dz1JsonLexer_lexNumber, Dz1JsonLexerState_number_lexing },
	{ Dz1JsonTokenType_minus,  Dz1JsonLexer_lexNumberInit, Dz1JsonLexer_lexNumber, Dz1JsonLexerState_number_lexing },
	{ Dz1JsonTokenType_symbol, Dz1JsonLexer_lexSymbolInit, Dz1JsonLexer_lexSymbol, Dz1JsonLexerState_symbol_lexing },
	{ Dz1JsonTokenType_max, NULL, NULL, Dz1JsonLexerState_max }
};

static LexerApiMap *LexerApiMap_findByType(Dz1JsonTokenType type)
{
	LexerApiMap *i;
	for (i = lexerApiMap; i->type != Dz1JsonTokenType_max; i++)
		if (i->type == type) return i;
	return NULL;
}

static LexerApiMap *LexerApiMap_findByState(Dz1JsonLexerState state)
{
	LexerApiMap *i;
	for (i = lexerApiMap; i->type != Dz1JsonTokenType_max; i++)
		if (i->state == state) return i;
	return NULL;
}

// ret == Dz1JsonTokenType_max : error or EOF, else : some token with data in ret_c32
static Dz1JsonTokenType Dz1JsonLexer_lexGetC(Dz1JsonFifo *src, u32_t *ret_c32, Dz1Error *err)
{
	Dz1JsonTokenType ret = Dz1JsonTokenType_max, type = Dz1JsonTokenType_max;
	DZ1_ERROR_SAFE_PTR(errp, err);
	u32_t c32 = 0;
	int status = 0;
	bool_t done = FALSE;
	while(errp->code == 0 && done == FALSE)
	{
		if ((status = Dz1JsonFifo_getC(src, &c32, errp)) < 0) ERR_OUT(errp);
		else if (status == 0)
		{	// EOF
			Dz1Error_set(errp, 0);
			done = TRUE;
		}
		else if ((type = _lex_simple_letter(c32)) != Dz1JsonTokenType_white_space)
		{
			ret = type;
			*ret_c32 = c32;
			done = TRUE;
		}
	}
	return ret;
}
// 1 : success, 0 : need more data, -1 : error
#define DZ1_JSON_LEXER_DEBUG
static int Dz1JsonLexer_lex(Dz1JsonLexer *lex, Dz1JsonFifo *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	int ret = -1;
	LexerApiMap *api = NULL;
	if (lex->state == Dz1JsonLexerState_no_lexing)
	{
		u32_t c32 = 0;
		Dz1JsonTokenType type = Dz1JsonTokenType_max;

		if (lex->dbgs & DZ1_JSON_LEVER_DEBUG_STREAM)
		{
			TCHAR temp_text[33] = { 0, };
			ssize_t rd_sz = Dz1Stream_peek(src->pop_stream, (u8_t *)temp_text, 32, errp);
			if (rd_sz < 0) Dz1Thread_printf(Dz1T("DEBUG : Inspection fail\n"));
			else
			{
				size_t cnt = 0;
				TCHAR *dp = temp_text, *sp = temp_text;
				while(*sp)
				{
					switch(*sp)
					{
					case Dz1T(' '): case Dz1T('\r'): case Dz1T('\n'): case Dz1T('\t'): break;
					default: *dp++ = *sp; cnt++; break;
					}
					sp++;
				}
				*dp = 0;
				Dz1Thread_printf(Dz1T("Lexing text(%u/%d) = %s\n"), cnt, rd_sz, temp_text);
			}
		}

		if ((type = Dz1JsonLexer_lexGetC(src, &c32, errp)) == Dz1JsonTokenType_max)
		{
			if (errp->code) ERR_OUT(errp);
			else ret = 0;
		}
		else if ((api = LexerApiMap_findByType(type)) == NULL)
		{	// 단일 Token
			if ((lex->token = Dz1JsonToken_new(type, NULL, errp)) == NULL) ERR_OUT(errp);
			else
			{
				lex->state = Dz1JsonLexerState_no_lexing;
				ret = 1;
			}
		}
		else if (api->init(lex, c32, errp) == FALSE) ERR_OUT(errp);
		else if ((lex->token = api->lex(lex, src, errp)) == NULL)
		{
			if (errp->code != EAGAIN) ERR_OUT(errp);
			else
			{
				lex->state = api->state;
				ret = 0;
			}
		}
		else
		{
			lex->state = Dz1JsonLexerState_no_lexing;
			ret = 1;
		}
	}
	else if ((api = LexerApiMap_findByState(lex->state)) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((lex->token = api->lex(lex, src, errp)) == NULL)
	{
		if (errp->code != EAGAIN) ERR_OUT(errp);
		else
		{
			Dz1Error_set(errp, 0);
			ret = 0;
		}
	}
	else
	{
		lex->state = Dz1JsonLexerState_no_lexing;
		ret = 1;
	}
	return ret;
}

Dz1JsonToken *Dz1JsonLexer_get(Dz1JsonLexer *p, Dz1JsonFifo *fifo, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonToken *ret = NULL;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (p->token == NULL)
	{
		int status = Dz1JsonLexer_lex(p, fifo, errp);
		if (status < 0) ERR_OUT(errp);
		else if (status == 0) Dz1Error_set(errp, 0);
		else if ((ret = p->token) == NULL) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);
	}
	else 
	{
		ret = p->token;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

void Dz1JsonLexer_consume(Dz1JsonLexer *p)
{
//	Dz1Thread_printf("@@@ Lexer Consume = "); Dz1JsonToken_dump(p->token, 0);
	Dz1JsonToken_delAndSetNull(&p->token);
}

Dz1JsonLexer *Dz1JsonLexer_create(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonLexer *ret = Dz1JsonLexer_new(NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1JsonLexer_delAndSetNull, (void *)&ret);
		if ((ret->buf = Dz1ElasticBuf_new(4096, FALSE, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1JsonLexer_delAndSetNull, (void *)&ret);
	}
	return ret;
}
