#include <dz1_malloc.h>
#include <dz1_str.h>

#include "../kernel/dz1_thread_stdio.h"
#include "dz1_parser_token.h"

str_t Dz1ParserToken_typeStr(Dz1ParserTokenTypeStr str, u32_t tokenType)
{
	switch(tokenType)
	{
		case DZ1_PARSER_TOKEN_LBRACKET:					// '('
			sprintf(str, "LEFT BRACKET"); break;
		case DZ1_PARSER_TOKEN_RBRACKET:					// ')'
			sprintf(str, "RIGHT BRACKET"); break;
		case DZ1_PARSER_TOKEN_LISTSTART:				// '{'
			sprintf(str,"LIST START"); break;
		case DZ1_PARSER_TOKEN_LISTEND:					// '}'
			sprintf(str,"LIST END"); break;
		case DZ1_PARSER_TOKEN_BLOCKSTART:				// '['
			sprintf(str, "BLOCK START"); break;
		case DZ1_PARSER_TOKEN_BLOCKEND:					// ']'
			sprintf(str, "BLOCK END"); break;
		case DZ1_PARSER_TOKEN_COLON:					// ':'
			sprintf(str,"COLON"); break;
		case DZ1_PARSER_TOKEN_ASSIGN:					// '::='
			sprintf(str, "ASSIGN"); break;
		case DZ1_PARSER_TOKEN_EQUAL:					// '='
			sprintf(str, "EQUAL"); break;
		case DZ1_PARSER_TOKEN_BOOL_EQUAL:				// ==
			sprintf(str, "BOOL_EQ"); break;
		case DZ1_PARSER_TOKEN_BOOL_NOT:					// !
			sprintf(str, "BOOL_NOT"); break;
		case DZ1_PARSER_TOKEN_BOOL_NOTEQ:				// !=
			sprintf(str, "BOOL_NOTEQ"); break;
		case DZ1_PARSER_TOKEN_DOT:						// '.'
			sprintf(str,"DOT"); break;
		case DZ1_PARSER_TOKEN_DOTDOT:					// '..'
			sprintf(str,"DOTDOT"); break;
		case DZ1_PARSER_TOKEN_DOTDOTDOT:				// '...'
			sprintf(str,"DOTDOTDOT"); break;
		case DZ1_PARSER_TOKEN_ALTERNATE:				// '|'
			sprintf(str,"ALTNATE"); break;
		case DZ1_PARSER_TOKEN_BOOL_OR:					// '||'
			sprintf(str,"BOOL_OR"); break;
		case DZ1_PARSER_TOKEN_COMMA:					// ','
			sprintf(str,"COMMA"); break;
		case DZ1_PARSER_TOKEN_LESS:						// '<'
			sprintf(str,"LESS"); break;
		case DZ1_PARSER_TOKEN_GT:						// '>'
			sprintf(str,"GREAT"); break;
		case DZ1_PARSER_TOKEN_PLUS:						// '+'
			sprintf(str,"PLUS"); break;
		case DZ1_PARSER_TOKEN_MINUS:					// '-'
			sprintf(str,"MINUS"); break;
		case DZ1_PARSER_TOKEN_MUL:						// '*'
			sprintf(str,"MULTI"); break;
		case DZ1_PARSER_TOKEN_DIV:						// '/'
			sprintf(str,"DIVIDE"); break;
		case DZ1_PARSER_TOKEN_POW:						// '^'
			sprintf(str,"POW"); break;
		case DZ1_PARSER_TOKEN_MOD:						// '%'
			sprintf(str,"MOD"); break;
		case DZ1_PARSER_TOKEN_SEMICOLON:				// ';'
			sprintf(str,"SEMICOLON"); break;
		case DZ1_PARSER_TOKEN_AND:						// '&'
			sprintf(str,"AND"); break;
		case DZ1_PARSER_TOKEN_SYMBOL:					// [A-Z|a-z][A-Z|a-z|0-9|_|-]*
			sprintf(str,"SYMBOL"); break;
		case DZ1_PARSER_TOKEN_LITERAL:					// $[A-Z|a-z][A-Z|a-z|0-9|_|-]*
			sprintf(str,"LITERAL"); break;
		case DZ1_PARSER_TOKEN_NUMBER:					// [+|-]*[0-9]+ or 0x[0-9|A-F|a-f]+ or 0b[0-1]+ or 0o[0-7]+
			sprintf(str, "NUMBER"); break;
		case DZ1_PARSER_TOKEN_STRING:					// "[Any ASCII Letters]+"
			sprintf(str, "STRING"); break;
		case DZ1_PARSER_TOKEN_LETTER:					// '[A-Z|a-z]' or ('\x[0-9|A-F|a-f]' or '\[0-9]+' with decimal range 0~255)
			sprintf(str,"LETTER"); break;
		case DZ1_PARSER_TOKEN_DONE:					// eof
			sprintf(str,"DONE"); break;
		case DZ1_PARSER_TOKEN_NONE:					// not match above
			sprintf(str,"NONE"); break;
		default:
			sprintf(str, "U%x",tokenType); break;
	}
	return str;
}

Dz1ParserToken *_Dz1ParserToken_new(u32_t tokenType, str_t tokenValue, Dz1Error *err, const char *__file__, int __line__)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1ParserToken *ret = (Dz1ParserToken *)_Dz1Malloc(sizeof(Dz1ParserToken), errp, __file__, __line__);
	if (ret)
	{
		memset(ret, 0, sizeof(Dz1ParserToken));
		pthread_cleanup_push(Dz1ParserToken_DelAndSetNull, (void *)&ret);

		if (tokenValue && strlen(tokenValue) > 0 && (ret->v = Dz1StrA_dup(tokenValue, errp)) == NULL)
		{
			Dz1Thread_eprintf("tokenType = %08X\n", tokenType);
			Dz1Thread_eprintf("tokenValue = %p\n", tokenValue);
			Dz1Thread_eprintf("tokenValue = %s\n", tokenValue);
			Dz1Thread_eprintf("tokenValueLen = %d\n", strlen(tokenValue));
			ERR_OUT(errp);
		}
		else
		{
			ret->t = tokenType;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1ParserToken_DelAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1ParserToken_del(Dz1ParserToken *token)
{
	if (token == NULL) return;

	if (token->v) Dz1Free(token->v);
	token->v = NULL;

	Dz1Free(token);
}

void Dz1ParserToken_dump(Dz1ParserToken *t, int tab)
{
	Dz1ParserTokenTypeStr typeStr;
	if (t) 
	{
		if (t->t == DZ1_PARSER_TOKEN_NONE)
		{
			char buf[7] = "0x";
			if (t->v)
			{
				char tmp[3];
				sprintf(tmp, "%02x", (u8_t)t->v[0]);
				strcat(buf, tmp);
			}
			else
				strcpy(buf, "(null)");
			Dz1Thread_tprintf(tab, "[%s:%s]\n", Dz1ParserToken_typeStr(typeStr, t->t), buf);
		}
		else
			Dz1Thread_tprintf(tab, "[%s:%s]\n", Dz1ParserToken_typeStr(typeStr, t->t), t->v ? t->v: "(Not Assign)");
	}
	else Dz1Thread_tprintf(tab, "[NULL]");
}

