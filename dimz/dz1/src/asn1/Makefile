ROOT		= ../..
include $(ROOT)/dz1build.mk

EXCLUDE		= 

#####################################################
### Defines for buileing TestProgram or Execution ###
#####################################################

LIBNAME		= dz1asn
LIBFILE		= lib$(LIBNAME).a

SUB_LDFLAGS	= -ldz1shell -ldz1termio -l$(LIBNAME) -ldz1kernel

ATMAIN		=	dz1_aatree_main.o
MAINS		+= 	$(ATMAIN)

ATPROG		=	dz1_aatree_main
PROGS		+= 	$(ATPROG)

#####################################################
###           Define Building Rules               ###  
#####################################################

local_build:objdir_chk libdir_chk lib

lib: $(OBJS) $(PLATFORM_OBJS)
	$(AR) rc $(LIBFILE) $(ROBJS) $(PLATFORM_OBJS)
	$(MV) $(LIBFILE) $(LIBDIR)

local_test:lib $(MAINS)
	$(CC) -o $(ATPROG)$(NATIVE_EXT) $(ATMAIN) $(LDFLAGS)
	$(STRIP) $(ATPROG)$(NATIVE_EXT) -o $(ATPROG)$(STRIP_EXT)

local_clean:
	$(RM) $(OBJS) $(PLATFORM_OBJS) $(MAINS) $(LIBFILE) $(STRIPPED_PROGS) $(NATIVED_PROGS)
	$(RM) -r $(OBJDIR)

local_install:
