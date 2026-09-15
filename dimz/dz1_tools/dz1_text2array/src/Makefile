ROOT		= ..
include $(ROOT)/build.mk

EXCLUDESRC	= text2array.c
EXCLUDE		= $(EXCLUDESRC:%.c=%.o) $(MAINS)

CFLAGS		+= -I.
#####################################################
### Defines for buileing TestProgram or Execution ###
#####################################################

LIBNAME		= dz1text2array
LIBFILE		= lib$(LIBNAME).a

SUB_LDFLAGS	= $(SHELL_LIBS) -l$(LIBNAME)

MAIN		=	main.o
MAINS		+= 	$(MAIN)

PROG		=	dz1taskgen
PROGS		+= 	$(PROG)

#####################################################
###           Define Building Rules               ###  
#####################################################

local_build:lib

lib: objdir_chk libdir_chk $(OBJS) $(PLATFORM_OBJS)
	$(AR) rc $(LIBFILE) $(ROBJS) $(PLATFORM_OBJS)
	$(MV) $(LIBFILE) $(LIBDIR)

local_test:lib $(MAINS)
	$(CC) -o $(PROG)$(NATIVE_EXT) $(MAIN) $(LDFLAGS)
	$(STRIP) $(PROG)$(NATIVE_EXT) -o $(PROG)$(STRIP_EXT)

local_clean:
	$(RM) $(ROBJS) $(PLATFORM_OBJS) $(MAINS) $(LIBFILE) $(STRIPPED_PROGS) $(NATIVED_PROGS)
	$(RM) -r $(OBJDIR)
	$(RM) -r $(LIBDIR)

local_install:
