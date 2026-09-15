#include <ctype.h>
#include <dz1_malloc.h>
#include <dz1_thread_stdio.h>

#include "dz1_parser_token.h"
#include "dz1_parser_lexer.h"

//#define LEXER_DEBUG

static int isinitialletter(char letter)
{
	switch(letter)
	{
		case '_':
			return 1;
		default:
			return 0;
	}
}

static int isidletter(char letter)
{
	switch(letter)
	{
		case '-':
		case '_':
			return 1;
		default:
			return 0;
	}
}

static int isHexaDigit(char c)
{
	if (c>='0' && c<='9') return TRUE;
	if (c>='a' && c<='f') return TRUE;
	if (c>='A' && c<='F') return TRUE;
	return FALSE;
}

static int hexaDigitToDecimal(char c)
{
	if (c>='a' && c<='f') return c - 'a' + 10;
	if (c>='A' && c<='F') return c - 'A' + 10;
	return c - '0';
}

static int isOctalDigit(char c)
{
	if (c>='0' && c<='7') return TRUE;
	return FALSE;
}

static int octalDigitToDecimal(char c)
{
	return c - '0';
}

static int isBinaryDigit(char c)
{
	if (c == '0' || c == '1') return TRUE;
	return FALSE;
}

static int binaryDigitToDecimal(char c)
{
	return octalDigitToDecimal(c);
}

static int digit_lex_decimal(u32_t *tokenType, char *buffer, char *dst)
{
	char *cp = buffer, *c = dst;
	char *trim = NULL, *cp_backup = NULL;
	u32_t type = NUMBER_DECIMAL;

	// take integral part
	while(isdigit((int)*cp & 0xFF)) *c++ = *cp++;
	*c = 0;

	// save position
	cp_backup = cp;
	trim = c;

	if (*cp == '.')
	{	// real number fraction part
		*c++ = *cp++;										// pass '.'
		if (isdigit((int)(*cp) & 0xFF) == FALSE)
		{	// fraction part is not digit -> rollback & return
			*trim = 0;
			cp = cp_backup;

			(*tokenType) |= type;
			return (int)(cp - buffer);
		}
		else
		{	// take fractional digits
			while(isdigit((int)*cp)) *c++ = *cp++;				// pass fraction digits
			*c = 0;
			type = NUMBER_FLOAT;
			// new rollback point
			cp_backup = cp;
			trim = c;
		}
	}

	if (*cp == 'e' || *cp == 'E')
	{	// exponential format part
		u32_t type_backup = type;
		bool_t exp_sign = FALSE;

		*c++ = 'E'; cp++;									// pass 'E'
		if (*cp == '+' || *cp == '-')
		{
			*c++ = *cp++;									// pass '+' or '-'
			exp_sign = TRUE;
		}

		if (isdigit((int)(*cp) & 0xFF) == FALSE)
		{	// 1.23E or 3E it's not exponential -> rollback
			*trim = 0;
			cp = cp_backup;
			type = type_backup;
		}
		else
		{	// 1.23E+3, 2.34E-2, 3.45E1
			if (exp_sign == FALSE) *c++ = '+';				// make sure exponent sign

			while(isdigit((int)*cp & 0xFF)) *c++ = *cp++;	// pass exponent number
			c = 0;

			type = NUMBER_EXPONENT;
		}
	}

	(*tokenType) |= type;
	return (int)(cp - buffer);
}

static int digit_lex(u32_t *tokenType, char *buffer, char *dst, Dz1Error *err)
{
	char *cp = buffer, *c = dst;
	Dz1Error_set(err, 0);
	if (*cp == '0')
	{
		cp++;
		// Hex Digit
		if (*cp == 'x')
		{
			s64_t temp = 0; cp++; (*tokenType) |= NUMBER_HEXA;
			while(isHexaDigit(*cp)) temp = (temp << 4) + hexaDigitToDecimal(*cp++);
			sprintf(dst, DZ1_FMT64_A, temp);
		}
		// Octal Digit
		else if (*cp == 'o')
		{
			s64_t temp = 0; cp++; (*tokenType) |= NUMBER_OCT;
			while(isOctalDigit(*cp)) temp = (temp << 3) + octalDigitToDecimal(*cp++);
			sprintf(dst, DZ1_FMT64_A, temp);
		}
		// Binary Digit
		else if (*cp == 'b')
		{
			s64_t temp = 0; cp++; (*tokenType) |= NUMBER_BIN;
			while(isBinaryDigit(*cp)) temp = (temp << 1) + binaryDigitToDecimal(*cp++);
			sprintf(dst, DZ1_FMT64_A, temp);
		}
		// Normal Digit
		else
		{
			int sz = 0;

			*c++ = '0'; 
			sz = digit_lex_decimal(tokenType, cp, c);
			cp += sz;

// 			(*tokenType) |= (NUMBER_TYPE_SPECIFIED | NUMBER_DECIMAL);
// 			while(isdigit((int)*cp)) *c++ = *cp++;
// 			*c = '\0';
		}
	}
	else
	{	// Normal Digit
		int sz = 0;
		sz = digit_lex_decimal(tokenType, cp, c);
		cp += sz;

// 		(*tokenType) |= (NUMBER_TYPE_SPECIFIED | NUMBER_DECIMAL);
// 		while(isdigit((int)*cp)) *c++ = *cp++;
// 		*c = '\0';
	}
	return (int)(cp - buffer);
}

static int string_lex(Dz1ParserLexer *l, char *buffer, char *dst, Dz1Error *err)
{
	char *cp = buffer, *c = dst;
	Dz1Error_set(err, 0);
	while(*cp=='"')
	{
		cp++; // Skip First Double Quotation
		while(1)
		{
			if (*cp == '\0')
			{
				Dz1Error_setWithComment(err, EINVAL, (DZ1_ERROR_ARG, "String Token Truncated at Line %d\n", l->getLineNum(l) + 1));
				return -1;
			}
			// Process Escape Sequence
			else if (*cp == '\\')
			{
				cp++;
				if (*cp)
				{
					if (*cp == '\n') l->lineNumber++;

					switch(*cp++)
					{
					case 'n':	// "\n"
						*c++ = '\n';
						break;
					case 'r':
						*c++ = '\r';
						break;
					case '\\':
						*c++ = '\\';
						break;
					default:
						Dz1Error_setWithComment(err, EINVAL, (DZ1_ERROR_ARG, "Unknown escape sequence at Line %d\n", l->getLineNum(l) + 1));
						return -1;
					}
				}
				else
				{
					Dz1Error_setWithComment(err, EINVAL, (DZ1_ERROR_ARG, "String Token Truncated at Line %d\n", l->getLineNum(l) + 1));
					return -1;
				}
			}
			// Skip Last Double quotation and exit while loop
			else if (*cp == '"') { cp++; break; }
			// Process LF Counter
			else 
			{ 
				if (*cp == '\n') l->lineNumber++; 
				*c++ = *cp++;
			}
		}
		// Processing Continued String :: "abcdefg"[white Space]+"hijklmn" to "abcdefghijklmn"
		while(*cp && isspace((int)*cp))
		{
			if (*cp == '\n') l->lineNumber++;
			cp++; // Trim front white space
		}
		if (*cp == '\0') break;
	}
	*c='\0';
	return (int)(cp - buffer);
}

static int letter_lex(Dz1ParserLexer *l, char *buffer, char *dst, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	char *cp = buffer, *c = dst;
	cp++; // Skip first single quotation
	// Process Numeric Letter Notation
	if (*cp == '\\')
	{
		cp++; // Skip Escape Letter
		// Process Hexa Decimal Notation
		if (*cp == 'x')
		{
			int result = 0;
			cp++;
			while(isHexaDigit(*cp)) result = (result << 4) + hexaDigitToDecimal(*cp++);
			sprintf(dst, "%d", result);
		}
		// Process Decimal Notation
		else if (isdigit((int)*cp)) { while(isdigit((int)*cp)) *c++ = *cp++; *c = '\0'; }
		// Take Escape Letter
		else if (*cp == '\\') { int result = (int)*cp++; sprintf(dst, "%d", result); }
		// Exception
		else
		{
			Dz1Error_setWithComment(errp, EINVAL, (DZ1_ERROR_ARG, "invalid letter notation : line %d\n", l->getLineNum(l) + 1));
			return -1;
		}
	}
	// Normally Take One Letter
	else { int result = (int)*cp++; sprintf(dst, "%d", result); }

	// Check Last Single Quotation
	if (*cp != '\'')
	{
		Dz1Error_setWithComment(errp, EINVAL, (DZ1_ERROR_ARG, "invalid letter notation : line %d\n", l->getLineNum(l) + 1));
		return -1;
	}
	// Skip Last Single Quotation
	else cp++;
	return (int)(cp - buffer);
}

static bool_t isCP949(str_t p)
{
	bool_t ret = FALSE;
	if (*p != '\0' && *(p + 1) != '\0')
	{
		if (*p & 0x80 && *(p + 1) & 0x80) ret = TRUE;
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Lex Processing
///////////////////////////////////////////////////////////////////////////////
#ifdef LEXER_DEBUG
#define SET_CURRENT(l, type, val, e) \
	do {\
		if (((l)->current = Dz1ParserToken_new((type), (val), &(e))))\
		{\
			Dz1Thread_eprintf("Token Catched...\n"); \
			Dz1ParserToken_dump((l)->current, 0);\
		}\
	} while(0)
#else
#define SET_CURRENT(l, type, val, e) \
	do { if (((l)->current = Dz1ParserToken_new((type), (val), &(e)))) { } } while(0)
#endif
static Dz1Error _Dz1ParserLexer_lex(Dz1ParserLexer *lexer, const char *__file__, int __line__)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	str_t c = lexer->buf;

//	tabprintf(0,"Dz1ParserLexer_lex() : Called from %s:%d\n", __file__, __line)));

	Dz1ParserToken_DelAndSetNull(&lexer->current);

	while(*lexer->source != '\0')
	{
		// Trim front white space
		while(isspace((int)*(lexer->source) & 0xFF)) 
		{
			if (*lexer->source == '\n') lexer->lineNumber++;
			lexer->source++; 
		}

#ifdef LEXER_DEBUG
		Dz1Thread_eprintf("Current letter (%c)\n", *(lexer->source));
#endif
		// Check EOF
		if (*(lexer->source) == '\0') { SET_CURRENT(lexer, DZ1_PARSER_TOKEN_DONE, NULL, err); }

		// Check Simple Tokens
		else if (*(lexer->source)=='(') { lexer->source++; SET_CURRENT(lexer, DZ1_PARSER_TOKEN_LBRACKET, NULL, err); }
		else if (*(lexer->source)==')') { lexer->source++; SET_CURRENT(lexer, DZ1_PARSER_TOKEN_RBRACKET, NULL, err); }
		else if (*(lexer->source)=='{') { lexer->source++; SET_CURRENT(lexer, DZ1_PARSER_TOKEN_LISTSTART, NULL, err); }
		else if (*(lexer->source)=='}') { lexer->source++; SET_CURRENT(lexer, DZ1_PARSER_TOKEN_LISTEND, NULL, err); }
		else if (*(lexer->source)=='[') { lexer->source++; SET_CURRENT(lexer, DZ1_PARSER_TOKEN_BLOCKSTART, NULL, err); }
		else if (*(lexer->source)==']') { lexer->source++; SET_CURRENT(lexer, DZ1_PARSER_TOKEN_BLOCKEND, NULL, err); }
		else if (*(lexer->source)=='=')
		{ 
			lexer->source++; 
			switch(*lexer->source)
			{
			case '=':
				lexer->source++;
				SET_CURRENT(lexer, DZ1_PARSER_TOKEN_BOOL_EQUAL, NULL, err);
				break;
			default:
				SET_CURRENT(lexer, DZ1_PARSER_TOKEN_EQUAL, NULL, err);
				break;
			}
		}
		else if (*(lexer->source)=='!')
		{
			lexer->source++; 
			if (*lexer->source == '=')
			{
				lexer->source++;
				SET_CURRENT(lexer, DZ1_PARSER_TOKEN_BOOL_NOTEQ, NULL, err);
			}
			else SET_CURRENT(lexer, DZ1_PARSER_TOKEN_BOOL_NOT, NULL, err);
		}
		else if (*(lexer->source)=='|')
		{ 
			lexer->source++; 
			if (*lexer->source == '|')
			{
				lexer->source++;
				SET_CURRENT(lexer, DZ1_PARSER_TOKEN_BOOL_OR, NULL, err);
			}
			else SET_CURRENT(lexer, DZ1_PARSER_TOKEN_ALTERNATE, NULL, err);
		}
		else if (*(lexer->source)==',') { lexer->source++; SET_CURRENT(lexer, DZ1_PARSER_TOKEN_COMMA, NULL, err); }
		else if (*(lexer->source)=='<')
		{
			lexer->source++;
			SET_CURRENT(lexer, DZ1_PARSER_TOKEN_LESS, NULL, err);
		}
		else if (*(lexer->source)=='>')
		{
			lexer->source++; 
			SET_CURRENT(lexer, DZ1_PARSER_TOKEN_GT, NULL, err);
		}
		else if (*(lexer->source)=='*') { lexer->source++; SET_CURRENT(lexer, DZ1_PARSER_TOKEN_MUL, NULL, err); }
		else if (*(lexer->source)=='^') { lexer->source++; SET_CURRENT(lexer, DZ1_PARSER_TOKEN_POW, NULL, err); }
		else if (*(lexer->source)=='%') { lexer->source++; SET_CURRENT(lexer, DZ1_PARSER_TOKEN_MOD, NULL, err); }
		else if (*(lexer->source)==';') { lexer->source++; SET_CURRENT(lexer, DZ1_PARSER_TOKEN_SEMICOLON, NULL, err); }
		else if (*(lexer->source)=='&')
		{
			lexer->source++;
			if (*lexer->source == '&')
			{
				lexer->source++;
				SET_CURRENT(lexer, DZ1_PARSER_TOKEN_BOOL_AND, NULL, err);
			}
			else SET_CURRENT(lexer, DZ1_PARSER_TOKEN_AND, NULL, err);
		}
		else if (*(lexer->source)=='@') { lexer->source++; SET_CURRENT(lexer, DZ1_PARSER_TOKEN_AT, NULL, err); }
		else if (*(lexer->source)=='#') { lexer->source++; SET_CURRENT(lexer, DZ1_PARSER_TOKEN_HASH, NULL, err); }
		else if (*(lexer->source)=='/') 
		{	// Check long comment or DIV
			lexer->source++;
			if (*lexer->source == '*')
			{	// is start of comment
				char *ep = NULL;
				lexer->source++;
				if ((ep = strstr(lexer->source, "*/")) == NULL) Dz1Error_setWithComment(&err, EINVAL, (DZ1_ERROR_ARG, "Invalid comment at %d\n", lexer->getLineNum(lexer) + 1));
				else
				{
					char *sp = lexer->source;
					while(sp < ep)
					{
						if (*sp == '\n') lexer->lineNumber++;
						sp++;
					}

					lexer->source = ep + 2;	// pass "*/"
					c = lexer->buf;
					continue;
				}
			}
			else SET_CURRENT(lexer, DZ1_PARSER_TOKEN_DIV, NULL, err); 
		}
		else if (*(lexer->source)==':')
		{	// Check COLON | ASSIGN
			lexer->source++;
			if (*(lexer->source) == ':')
			{
				lexer->source++;
				if (*(lexer->source) == '=') { lexer->source++; SET_CURRENT(lexer, DZ1_PARSER_TOKEN_ASSIGN, NULL, err); } // ASSIGN
				else { Dz1Error_setWithComment(&err, EINVAL, (DZ1_ERROR_ARG, "Invalid Token at %d. expect token is \"::=\"\n", lexer->getLineNum(lexer) + 1)); }
			}
			else { SET_CURRENT(lexer, DZ1_PARSER_TOKEN_COLON, NULL, err); }
		}
		else if (*(lexer->source) == '$')
		{	// Check LITERAL
			lexer->source++;
			while(isalnum((int)*(lexer->source) & 0xFF) || isidletter(*(lexer->source))) *c++=*(lexer->source)++;
			*c='\0';
			SET_CURRENT(lexer, DZ1_PARSER_TOKEN_LITERAL, lexer->buf, err);
		}
		else if (*(lexer->source)=='.')
		{	// Check DOT | DOTDOT
			lexer->source++;
			if (*(lexer->source) == '.')
			{
				lexer->source++;
				if (*(lexer->source) == '.')
				{
					lexer->source++;
					SET_CURRENT(lexer, DZ1_PARSER_TOKEN_DOTDOTDOT, NULL, err); // DOTDOTDOT
				}
				else SET_CURRENT(lexer, DZ1_PARSER_TOKEN_DOTDOT, NULL, err); // DOTDOT
			}
			else { SET_CURRENT(lexer, DZ1_PARSER_TOKEN_DOT, NULL, err); } // DOT
		}
		else if (isalpha((int)*(lexer->source) & 0xFF) || isinitialletter(*(lexer->source)) || isCP949(lexer->source))
		{	// Check SYMBOL
			bool_t cp949 = FALSE;
			while(isalnum((int)*(lexer->source) & 0xFF) || isidletter(*(lexer->source)) || (cp949 = isCP949(lexer->source)) || *lexer->source == '-')
			{
				if (cp949)
				{	// take 2 byte
					*c++ = *(lexer->source)++;
					*c++ = *(lexer->source)++;
				}
				else if (*lexer->source == '-')
				{
					*c++ = '_';
					lexer->source++;
				}
				else *c++ = *(lexer->source)++;
			}
			*c ='\0';
			SET_CURRENT(lexer, DZ1_PARSER_TOKEN_SYMBOL, lexer->buf, err);
		}
		// Check MINUS or COMMENT or -NUMBER or PLUS or +NUMBER
		else if (*(lexer->source)=='-' || *(lexer->source)=='+')
		{	// Plus, Minus, Single Line Comment, +Number, -Number
			char sign = *c++ = *lexer->source++;
			if (isdigit((int)*(lexer->source) & 0xFF))
			{ // Digit : -Number or +Number
				u32_t tokenType = (DZ1_PARSER_TOKEN_NUMBER | NUMBER_SIGN_SPECIFIED);
				int len = 0;
				if ((len = digit_lex(&tokenType, lexer->source, c, &err)) == -1) { }
				else { lexer->source += len; SET_CURRENT(lexer, tokenType, lexer->buf, err); }
			}
			// Plus, Minus, Comment
			else if (*(lexer->source) == '-')
			{	// Single Line Comment
				while(*(lexer->source) && *(lexer->source) != '\n') lexer->source++;
				c = lexer->buf;
				continue;
			}
			else
			{	// Plus, Minus
				u32_t type = sign == '+' ? DZ1_PARSER_TOKEN_PLUS : DZ1_PARSER_TOKEN_MINUS;
				SET_CURRENT(lexer, type, NULL, err);
			}
		}
		// Check NUMBER
		else if (isdigit((int)*(lexer->source) & 0xFF))
		{	// 0x... 0o... 0b... 12345
			int len = 0;
			u32_t tokenType = DZ1_PARSER_TOKEN_NUMBER;
			if ((len = digit_lex(&tokenType, lexer->source, c, &err)) == -1) { }
			else { lexer->source += len; SET_CURRENT(lexer, tokenType, lexer->buf, err); }
		}
		// Check String
		else if (*(lexer->source)=='\"')
		{
			int len = 0;
			if ((len = string_lex(lexer, lexer->source, c, &err)) == -1) { }
			else { lexer->source += len; SET_CURRENT(lexer, DZ1_PARSER_TOKEN_STRING, lexer->buf, err); }
		}
		// Check LETTER
		else if (*(lexer->source) == '\'')
		{
			int len = 0;
			if ((len = letter_lex(lexer, lexer->source, c, &err)) == -1) { }
			else { lexer->source += len; SET_CURRENT(lexer, DZ1_PARSER_TOKEN_LETTER, c, err); }
		}
		// Does not match any case. then send up transparently to Parsing Layer;
		else
		{
			// printf("None:%c(%02x)\n", (u8t)*(lexer->source), (u8t)*(lexer->source));
			*c++ = *(lexer->source)++;
			*c = '\0';
			SET_CURRENT(lexer, DZ1_PARSER_TOKEN_NONE, lexer->buf, err);
		}
		// Dz1ParserToken_dump(con, lexer->current, 0);
		return err;
	}
	SET_CURRENT(lexer, DZ1_PARSER_TOKEN_DONE, NULL, err);
	return err;
}

static Dz1Error Dz1ParserLexer_setSrc(Dz1ParserLexer *lexer, str_t text)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (!text || !strlen(text)) Dz1Error_set(&err, EINVAL); 
	else
	{
		lexer->source = text;
		lexer->lineNumber = 0;
	}
	return err;
}

static u32_t Dz1ParserLexer_getLineNum(Dz1ParserLexer *lexer) { return lexer->lineNumber; }
static void Dz1ParserLexer_setLineNum(Dz1ParserLexer *lexer, u32_t num) { lexer->lineNumber = num; }

Dz1ParserLexer *Dz1ParserLexer_new(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1ParserLexer *ret = (Dz1ParserLexer *)Dz1Malloc(sizeof(Dz1ParserLexer), errp);
	if (ret)
	{
		ret->source = NULL;
		ret->lineNumber = 0;
		memset(ret->buf, 0, DZ1_PARSER_LEX_MAX_SEGMENT);
		ret->current = NULL;
		ret->lex = _Dz1ParserLexer_lex;
		ret->setSrc = Dz1ParserLexer_setSrc;
		ret->getLineNum = Dz1ParserLexer_getLineNum;
		ret->setLineNum = Dz1ParserLexer_setLineNum;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

void Dz1ParserLexer_del(Dz1ParserLexer *p)
{
	if (!p) return;
	if (p->current) Dz1ParserToken_del(p->current);
	p->current = NULL;
	Dz1Free(p);
}
