ROOT		= ../..
include $(ROOT)/dz1build.mk

EXCLUDE	=	

#####################################################
### Defines for buileing TestProgram or Execution ###
#####################################################

LIBNAME		= dz1util
LIBFILE		= lib$(LIBNAME).a

SUB_LDFLAGS	= -l$(LIBNAME)

MAIN	=	dz1_arg_test.o
MAINS	+= 	$(MAIN)

PROG	=	dz1_arg_test
PROGS	+= 	$(PROG)

#####################################################
###           Define Building Rules               ###  
#####################################################

local_build:objdir_chk libdir_chk lib

lib: $(OBJS)
	$(AR) rc $(LIBFILE) $(ROBJS)
	$(MV) $(LIBFILE) $(LIBDIR)

local_test:lib $(MAINS)
	$(CC) -o $(PROG)$(NATIVE_EXT) $(MAIN) $(LDFLAGS)
	$(STRIP) $(PROG)$(NATIVE_EXT) -o $(PROG)$(STRIPP_EXT)

local_clean:
	$(RM) $(ROBJS) $(MAINS) $(LIBFILE) $(STRIPPED_PROGS) $(NATIVED_PROGS)
	$(RM) -r $(OBJDIR)

local_install:
