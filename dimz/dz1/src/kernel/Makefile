ROOT		= ../..
include $(ROOT)/dz1build.mk

EXCLUDESRC	= $(wildcard hae*.c) dz1_thread_mainb.c

EXCLUDE		= $(EXCLUDESRC:%.c=%.o)

ifeq (LINUX,$(PLATFORM))
PLATFORM_OBJS	= dz1_console_tty_linux.o
endif

#####################################################
### Defines for buileing TestProgram or Execution ###
#####################################################

LIBNAME		= dz1kernel
LIBFILE		= lib$(LIBNAME).a

SUB_LDFLAGS	= -ldz1util -l$(LIBNAME)  # 20250619 gm

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

local_build:objdir_chk libdir_chk lib

lib: $(OBJS) $(PLATFORM_OBJS)
	$(AR) rc $(LIBFILE) $(ROBJS) $(OBJDIR)/$(PLATFORM_OBJS) ../util/$(OBJDIR)/dz1_base64.o #20250619 gm
	$(MV) $(LIBFILE) $(LIBDIR)

local_test:lib $(MAINS)
	$(CC) -o $(CONPROG)$(NATIVE_EXT) $(CONMAIN) $(LDFLAGS)
	$(STRIP) $(CONPROG)$(NATIVE_EXT) -o $(CONPROG)$(STRIP_EXT)

	$(CC) -o $(MEMPROG)$(NATIVE_EXT) $(MEMMAIN) $(LDFLAGS)
	$(STRIP) $(MEMPROG)$(NATIVE_EXT) -o $(MEMPROG)$(STRIP_EXT)

	$(CC) -o $(THPROG)$(NATIVE_EXT) $(THMAIN) $(LDFLAGS)
	$(STRIP) $(THPROG)$(NATIVE_EXT) -o $(THPROG)$(STRIP_EXT)

local_clean:
	$(RM) $(ROBJS) $(OBJDIR)/$(PLATFORM_OBJS) $(MAINS) $(LIBFILE) $(STRIPPED_PROGS) $(NATIVED_PROGS)
	$(RM) -r $(OBJDIR)

local_install:
