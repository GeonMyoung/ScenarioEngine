ROOT		= ../..
include $(ROOT)/dz1build.mk

EXCLUDESRC	= $(wildcard hae*.c)
EXCLUDE		= $(EXCLUDESRC:%.c=%.o)

#####################################################
### Defines for buileing TestProgram or Execution ###
#####################################################

LIBNAME		= dz1shell
LIBFILE		= lib$(LIBNAME).a

SUB_LDFLAGS	= -l$(LIBNAME) -ldz1struct -ldz1termio -ldz1kernel

VARMAIN		=	dz1_shell_var_main.o
MAINS		+= 	$(VARMAIN)

VARPROG		=	dz1_shell_var_main
PROGS		+= 	$(VARPROG)

HISMAIN		=	dz1_shell_history_main.o
MAINS		+= 	$(HISMAIN)

HISPROG		=	dz1_shell_history_main
PROGS		+= 	$(HISPROG)

ARGMAIN		=	dz1_shell_args_main.o
MAINS		+= 	$(ARGMAIN)

ARGPROG		=	dz1_shell_args_main
PROGS		+= 	$(ARGPROG)

PRSMAIN		=	dz1_shell_parse_main.o
MAINS		+= 	$(PRSMAIN)

PRSPROG		=	dz1_shell_parse_main
PROGS		+= 	$(PRSPROG)

CMDMAIN		=	dz1_shell_cmd_main.o
MAINS		+= 	$(CMDMAIN)

CMDPROG		=	dz1_shell_cmd_main
PROGS		+= 	$(CMDPROG)

INPMAIN		=	dz1_shell_input_main.o
MAINS		+= 	$(INPMAIN)

INPPROG		=	dz1_shell_input_main
PROGS		+= 	$(INPPROG)

MAIN		=	dz1_shell_main.o
MAINS		+= 	$(MAIN)

PROG		=	dz1_shell_main
PROGS		+= 	$(PROG)

#####################################################
###           Define Building Rules               ###  
#####################################################

local_build:objdir_chk libdir_chk lib

lib: $(OBJS) $(PLATFORM_OBJS)
	$(AR) rc $(LIBFILE) $(ROBJS) $(PLATFORM_OBJS)
	$(MV) $(LIBFILE) $(LIBDIR)

local_test:lib $(MAINS)
	$(CC) -o $(VARPROG)$(NATIVE_EXT) $(VARMAIN) $(LDFLAGS)
	$(STRIP) $(VARPROG)$(NATIVE_EXT) -o $(VARPROG)$(STRIP_EXT)

	$(CC) -o $(HISPROG)$(NATIVE_EXT) $(HISMAIN) $(LDFLAGS)
	$(STRIP) $(HISPROG)$(NATIVE_EXT) -o $(HISPROG)$(STRIP_EXT)

	$(CC) -o $(ARGPROG)$(NATIVE_EXT) $(ARGMAIN) $(LDFLAGS)
	$(STRIP) $(ARGPROG)$(NATIVE_EXT) -o $(ARGPROG)$(STRIP_EXT)

	$(CC) -o $(PRSPROG)$(NATIVE_EXT) $(PRSMAIN) $(LDFLAGS)
	$(STRIP) $(PRSPROG)$(NATIVE_EXT) -o $(PRSPROG)$(STRIP_EXT)

	$(CC) -o $(CMDPROG)$(NATIVE_EXT) $(CMDMAIN) $(LDFLAGS)
	$(STRIP) $(CMDPROG)$(NATIVE_EXT) -o $(CMDPROG)$(STRIP_EXT)

	$(CC) -o $(INPPROG)$(NATIVE_EXT) $(INPMAIN) $(LDFLAGS)
	$(STRIP) $(INPPROG)$(NATIVE_EXT) -o $(INPPROG)$(STRIP_EXT)

	$(CC) -o $(PROG)$(NATIVE_EXT) $(MAIN) $(LDFLAGS)
	$(STRIP) $(PROG)$(NATIVE_EXT) -o $(PROG)$(STRIP_EXT)

local_clean:
	$(RM) $(ROBJS) $(PLATFORM_OBJS) $(MAINS) $(LIBFILE) $(STRIPPED_PROGS) $(NATIVED_PROGS)
	$(RM) -r $(OBJDIR)

local_install:
