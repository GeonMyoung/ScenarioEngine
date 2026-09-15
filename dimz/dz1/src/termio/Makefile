ROOT		= ../..
include $(ROOT)/dz1build.mk

EXCLUDESRC	= $(wildcard hae*.c)
EXCLUDE		= $(EXCLUDESRC:%.c=%.o)

#CFLAGS		+= -DMATCH_ERROR_PRINT
#CFLAGS		+= -DMATCH_TRACE
#CFLAGS		+= -DSYNTAX_DEBUG
#CFLAGS		+= -DLEXER_DEBUG
#####################################################
### Defines for buileing TestProgram or Execution ###
#####################################################

LIBNAME		= dz1termio
LIBFILE		= lib$(LIBNAME).a

SUB_LDFLAGS	= -l$(LIBNAME) -ldz1shell -ldz1struct -ldz1kernel

MAIN		=	
MAINS		+= 	$(MAIN)

PROG		=	
PROGS		+= 	$(PROG)

#####################################################
###           Define Building Rules               ###  
#####################################################

local_build:objdir_chk libdir_chk lib

lib: $(OBJS) $(PLATFORM_OBJS)
	$(AR) rc $(LIBFILE) $(ROBJS) $(PLATFORM_OBJS)
	$(MV) $(LIBFILE) $(LIBDIR)

local_test:lib $(MAINS)
	$(CC) -o $(PROG)$(NATIVE_EXT) $(MAIN) $(LDFLAGS)
	$(STRIP) $(PROG)$(NATIVE_EXT) -o $(PROG)$(STRIP_EXT)

local_clean:
	$(RM) $(ROBJS) $(PLATFORM_OBJS) $(MAINS) $(LIBFILE) $(STRIPPED_PROGS) $(NATIVED_PROGS)
	$(RM) -r $(OBJDIR)

local_install:
