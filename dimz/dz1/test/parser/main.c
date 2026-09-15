#ifdef CPP_BUILDER_WIN32
#include <stdio.h>
#pragma hdrstop
#endif

#include <dz1_cleanup.h>
#include <dz1_thread_stdio.h>
#include <dz1_malloc.h>

#include <dz1_parser_init.h>

#ifdef WIN32
#ifdef _DEBUG
#include <conio.h>
#endif
#endif

#include "stack.h"

static Dz1Error pop_oper(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Stack *p = (Stack *)param;
	char oper = p->pop(p, &err);
	if (oper == '\0') { }
	else printf("%c\n", oper);
	return err;
}

static char token2oper(u32_t type)
{
	switch(type)
	{
		case DZ1_PARSER_TOKEN_PLUS:
			return '+';
		case DZ1_PARSER_TOKEN_MINUS:
			return '-';
		case DZ1_PARSER_TOKEN_MUL:
			return '*';
		case DZ1_PARSER_TOKEN_DIV:
			return '/';
		default:
			return '\0';
	}
}
static Dz1Error push_oper(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Stack *p = (Stack *)param;
	char oper = token2oper(t->t);
	if (oper == '\0') { }
	else err = p->push(p, oper);
	return err;
}

static str_t decimal = NULL, fraction = NULL;

static Dz1Error print_num(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	printf("%s", decimal); Dz1Free(decimal); decimal = NULL;
	if (fraction)
	{
		printf(".%s\n", fraction);
		Dz1Free(fraction); fraction = NULL;
	}
	else printf("\n");

	return err;
}

static Dz1Error set_decimal(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	decimal = t->v;
	t->v = NULL;
	return err;
}

static Dz1Error set_frac(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (fraction) Dz1Error_set(&err, EINVAL);
	else
	{
		fraction = t->v;
		t->v = NULL;
	}
	return err;
}

int main(void)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Stack *stack = NULL;
	void *p = NULL;

	str_t text ="main = <expr> <semicolon> <done>;\n"
				"expr = <term> [<terms>=pop_oper]*;\n"
				"term = <factor> [<factors>=pop_oper]*;\n"
				"terms = <plus>|<minus>=push_oper <term>;\n"
				"factor = <bexpr>|<num>;\n"
				"factors = <mul>|<div>=push_oper <factor>;\n"
				"bexpr = <lbracket> <expr> <rbracket>;\n"
				"num = <realnum>=print_num;\n"
				"realnum = <number>=set_decimal [<fraction>];\n"
				"fraction = <dot> <number_no_sign_decimal>=set_frac;\n";

	str_t expr = "9.8765 * (16 + 4) * 7.9 + 1 / (2 + 3);";
	//str_t expr = "9;";

	Dz1Cleanup_init();

	if ((stack = Stack_new(&err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Stack_del, (void *)stack);

		if ((p = Dz1Parser_new(&err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Dz1Parser_del, (void *)p);

			if ((err = Dz1Parser_addEmiter(p, "pop_oper", pop_oper)).code) ERR_OUT(&err);
			else if ((err = Dz1Parser_addEmiter(p, "push_oper", push_oper)).code) ERR_OUT(&err);
			else if ((err = Dz1Parser_addEmiter(p, "print_num", print_num)).code) ERR_OUT(&err);
			else if ((err = Dz1Parser_addEmiter(p, "set_decimal", set_decimal)).code) ERR_OUT(&err);
			else if ((err = Dz1Parser_addEmiter(p, "set_frac", set_frac)).code) ERR_OUT(&err);
			else
			{
				if ((err = Dz1ParserInit_parse(p, text)).code) ERR_OUT(&err);
				else
				{
					Dz1Parser_dump(p, 1);
					Dz1Thread_printf("[%s]-----------------------------------------------\n", expr);
					Dz1Parser_prepare(p, expr);
					if ((err = Dz1Parser_process(p, "main", stack, 0)).code) Dz1Thread_printf("Expression Compile Fail\n");
					else
					{
					//	Stack_dump(stack, 0);
						Dz1Thread_printf("Success\n");
					}
				}
			}
			pthread_cleanup_pop(1); // (Dz1Parser_del, (void *)p);
		}
		pthread_cleanup_pop(1); // ((Dz1DelFunc)Stack_del, (void *)stack);
	}
#ifdef _DEBUG
#if (_MSC_VER < 1930)
	printf("Press Any Key...\n");
	while(!kbhit()) Sleep(10);
	fflush(stdin);
#endif
#endif
	return err.code;
}
