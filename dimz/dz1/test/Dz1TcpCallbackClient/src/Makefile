ROOT		= ../../..
TESTROOT	= ..
include $(TESTROOT)/build.mk

EXCLUDESRC	= $(wildcard hae*.c)
EXCLUDE		= $(EXCLUDESRC:%.c=%.o) $(MAINS)

#####################################################
### Defines for buileing TestProgram or Execution ###
#####################################################
LIBNAME		= Dz1TcpCallbackClient
LIBFILE		= lib$(LIBNAME).a

SUB_LDFLAGS	= -L$(MSGLIBDIR) -L$(TESTLIBDIR) -l$(LIBNAME) -l$(MSGLIBNAME) -ldz1task -ldz1socket -ldz1shell -ldz1struct -ldz1termio -ldz1kernel

#####################################################
###           Define Building Rules               ###  
#####################################################

local_build:lib

lib:test_libdir_chk objdir_chk $(OBJS) $(PLATFORM_OBJS)
	$(AR) rc $(LIBFILE) $(ROBJS) $(PLATFORM_OBJS)
	$(MV) $(LIBFILE) $(TESTLIBDIR)

local_test:lib $(MAINS)
	$(CC) -o $(PROG1)$(NATIVE_EXT) $(MAIN1) $(LDFLAGS)
	$(STRIP) $(PROG1)$(NATIVE_EXT) -o $(PROG1)$(STRIP_EXT)

local_clean:
	$(RM) $(OBJS) $(PLATFORM_OBJS) $(MAINS) $(LIBFILE) $(STRIPPED_PROGS) $(NATIVED_PROGS)
	$(RM) -r $(OBJDIR)

local_install:

test_libdir_chk:
	@if ! [ -d $(TESTLIBDIR) ]; then \
		mkdir -p $(TESTLIBDIR); \
	fi

