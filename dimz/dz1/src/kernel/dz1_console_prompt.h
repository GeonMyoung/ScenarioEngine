#ifndef DZ1_CONSOLE_PROMPT_H_LOCAL
#define DZ1_CONSOLE_PROMPT_H_LOCAL

#include <dz1_error.h>

typedef enum Dz1ConsolePromptMode
{
	Dz1ConsolePromptMode_longTime,
	Dz1ConsolePromptMode_shortTime,
	Dz1ConsolePromptMode_userSpecific
} Dz1ConsolePromptMode;

typedef Dz1Error (*Dz1ConsolePromptFunc)(void *userPtr, u8_t buf[64]);

typedef struct Dz1ConsolePrompt
{
	time_t					 lastBuilt;
	Dz1ConsolePromptMode	 mode;
	u8_t					 buf[64];
	Dz1ConsolePromptFunc	 func;
	void					*userPtr;
} Dz1ConsolePrompt;
#define Dz1ConsolePromptInitializer		{ 0, Dz1ConsolePromptMode_longTime, { 0, }, NULL, NULL }

DZ1_CPPLINK void	 Dz1ConsolePrompt_init(Dz1ConsolePrompt *p);
DZ1_CPPLINK Dz1Error Dz1ConsolePrompt_set(Dz1ConsolePrompt *p, Dz1ConsolePromptMode mode, Dz1ConsolePromptFunc func, void *userPtr);

DZ1_CPPLINK str_t	 Dz1ConsolePromptA_get(Dz1ConsolePrompt *p);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t	 Dz1ConsolePromptW_get(Dz1ConsolePrompt *p);
#endif
#endif
