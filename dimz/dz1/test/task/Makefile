ROOT		= ../..
include $(ROOT)/dz1build.mk

EXCLUDESRC	= $(wildcard hae*.c)

EXCLUDE		= $(EXCLUDESRC:%.c=%.o)

ifeq (LINUX,$(PLATFORM))
PLATFORM_OBJS	=
endif

#####################################################
### Defines for buileing TestProgram or Execution ###
#####################################################

LIBNAME		= dz1tasktest
LIBFILE		= lib$(LIBNAME).a

SUB_LDFLAGS	=	-ldz1shell \
				-ldz1termio \
				-ldz1socket \
				-ldz1task \
				-ldz1struct \
				-ldz1kernel

#############################
### Test 1
#############################
MAIN1		=	dz1_task_main.o
MAINS		+= 	$(MAIN1)

PROG1		=	dz1_task_main
PROGS		+= 	$(PROG1)

#####################################################
###           Define Building Rules               ###  
#####################################################

local_build:test

#lib: $(OBJS) $(PLATFORM_OBJS)
#	$(AR) rcu $(LIBFILE) $(OBJS) $(PLATFORM_OBJS)
#	$(MV) $(LIBFILE) $(LIBDIR)

local_test: objdir_chk $(MAINS)
	$(CC) -o $(PROG1)$(NATIVE_EXT) $(OBJDIR)/$(MAIN1) $(LDFLAGS) $(PLATFORM_OBJS)
	$(STRIP) $(PROG1)$(NATIVE_EXT) -o $(PROG1)$(STRIP_EXT)

local_clean:
	$(RM) $(OBJS) $(PLATFORM_OBJS) $(MAINS) $(LIBFILE) $(STRIPPED_PROGS) $(NATIVED_PROGS)
	$(RM) -r $(OBJDIR)

local_install:
