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

LIBNAME		= dz1crc
LIBFILE		= lib$(LIBNAME).a

SUB_LDFLAGS	= -l$(LIBNAME)

THMAIN		=	main.o
MAINS		+= 	$(THMAIN)

THPROG		=	main
PROGS		+= 	$(THPROG)

#####################################################
###           Define Building Rules               ###  
#####################################################

local_build:objdir_chk libdir_chk lib

lib: $(OBJS) $(PLATFORM_OBJS)
	$(AR) rc $(LIBFILE) $(ROBJS) $(PLATFORM_OBJS)
	$(MV) $(LIBFILE) $(LIBDIR)

local_test:lib $(MAINS)
	$(CC) -o $(THPROG)$(NATIVE_EXT) $(THMAIN) $(LDFLAGS)
	$(STRIP) $(THPROG)$(NATIVE_EXT) -o $(THPROG)$(STRIP_EXT)

local_clean:
	$(RM) $(ROBJS) $(PLATFORM_OBJS) $(MAINS) $(LIBFILE) $(STRIPPED_PROGS) $(NATIVED_PROGS)
	$(RM) -r $(OBJDIR)

local_install:
