ROOT		= ../../..
TESTROOT	= ..
include $(TESTROOT)/build.mk

EXCLUDESRC	= $(wildcard hae*.c)
EXCLUDE		= $(EXCLUDESRC:%.c=%.o) $(MAINS)

#####################################################
### Defines for buileing TestProgram or Execution ###
#####################################################
LIBNAME		= Dz1TcpCallbackMsg
LIBFILE		= lib$(LIBNAME).a

SUB_LDFLAGS	= -L$(LIBDIR) -l$(LIBNAME) -ldz1shell -ldz1struct -ldz1termio -ldz1kernel

#####################################################
###           Define Building Rules               ###  
#####################################################

local_build:lib

lib:objdir_chk libdir_chk test_libdir_chk $(OBJS) $(PLATFORM_OBJS)
	$(AR) rc $(LIBFILE) $(ROBJS) $(PLATFORM_OBJS)
	$(MV) $(LIBFILE) $(TESTLIBDIR)

local_clean:
	$(RM) $(OBJS) $(PLATFORM_OBJS) $(MAINS) $(LIBFILE) $(STRIPPED_PROGS) $(NATIVED_PROGS)
	$(RM) -r $(OBJDIR)

local_install:


test_libdir_chk:
	@if ! [ -d $(TESTLIBDIR) ]; then \
		mkdir -p $(TESTLIBDIR); \
	fi

