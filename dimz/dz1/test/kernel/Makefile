ROOT		= ../..
include $(ROOT)/dz1build.mk

EXCLUDESRC	= $(wildcard hae*.c) dz1_console_main.c dz1_malloc_main.c dz1_thread_mainb.c dz1_thread_main.c

EXCLUDE		= $(EXCLUDESRC:%.c=%.o)

ifeq (LINUX,$(PLATFORM))
PLATFORM_OBJS	=
endif

#####################################################
### Defines for buileing TestProgram or Execution ###
#####################################################

LIBNAME		= dz1kerneltest
LIBFILE		= lib$(LIBNAME).a

SUB_LDFLAGS	= -l$(LIBNAME) -ldz1shell -ldz1termio -ldz1struct -ldz1kernel

CONMAIN		=	dz1_console_main.o
MAINS		+= 	$(CONMAIN)

CONPROG		=	dz1_console_main
PROGS		+= 	$(CONPROG)

MEMMAIN		=	dz1_malloc_main.o
MAINS		+= 	$(MEMMAIN)

MEMPROG		=	dz1_malloc_main
PROGS		+= 	$(MEMPROG)

THMAIN		=	dz1_thread_main.o
MAINS		+= 	$(THMAIN)

THPROG		=	dz1_thread_main
PROGS		+= 	$(THPROG)

#####################################################
###           Define Building Rules               ###  
#####################################################

local_build:objdir_chk libdir_chk test

lib: $(OBJS) $(PLATFORM_OBJS)
	$(AR) rc $(LIBFILE) $(OBJS) $(PLATFORM_OBJS)
	$(MV) $(LIBFILE) $(LIBDIR)

local_test:lib $(MAINS)
	$(CC) -o $(CONPROG)$(NATIVE_EXT) $(OBJDIR)/$(CONMAIN) $(LDFLAGS) $(PLATFORM_OBJS)
	$(STRIP) $(CONPROG)$(NATIVE_EXT) -o $(CONPROG)$(STRIP_EXT)

	$(CC) -o $(MEMPROG)$(NATIVE_EXT) $(OBJDIR)/$(MEMMAIN) $(LDFLAGS) $(PLATFORM_OBJS)
	$(STRIP) $(MEMPROG)$(NATIVE_EXT) -o $(MEMPROG)$(STRIP_EXT)

	$(CC) -o $(THPROG)$(NATIVE_EXT) $(OBJDIR)/$(THMAIN) $(LDFLAGS) $(PLATFORM_OBJS)
	$(STRIP) $(THPROG)$(NATIVE_EXT) -o $(THPROG)$(STRIP_EXT)

local_clean:
	$(RM) $(OBJS) $(PLATFORM_OBJS) $(MAINS) $(LIBFILE) $(STRIPPED_PROGS) $(NATIVED_PROGS)
	$(RM) -r $(OBJDIR)

local_install:
