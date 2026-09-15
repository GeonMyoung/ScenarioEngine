ROOT		= ../..
include $(ROOT)/dz1build.mk


#####################################################
### Defines for buileing TestProgram or Execution ###
#####################################################

LIBNAME		= dz1struct
LIBFILE		= lib$(LIBNAME).a

SUB_LDFLAGS	=	-ldz1shell \
				-ldz1termio \
				-ldz1struct \
				-ldz1kernel

ATMAIN		=	dz1_aatree_main.o
MAINS		+= 	$(ATMAIN)

ATPROG		=	dz1_aatree_main
PROGS		+= 	$(ATPROG)

EXCLUDE		= $(MAINS)

#####################################################
###           Define Building Rules               ###  
#####################################################

local_build:test

#lib: objdir_chk
#	$(AR) rc $(LIBFILE) $(ROBJS) $(PLATFORM_OBJS)
#	$(MV) $(LIBFILE) $(LIBDIR)

local_test: objdir_chk $(MAINS)
	$(CC) -o $(ATPROG)$(NATIVE_EXT) $(OBJDIR)/$(ATMAIN) $(LDFLAGS)
	$(STRIP) $(ATPROG)$(NATIVE_EXT) -o $(ATPROG)$(STRIP_EXT)

local_clean:
	$(RM) $(OBJS) $(PLATFORM_OBJS) $(MAINS) $(LIBFILE) $(STRIPPED_PROGS) $(NATIVED_PROGS)
	$(RM) -r $(OBJDIR)

local_install:
