ROOT		= ..
include $(ROOT)/build.mk

#####################################################
### Set Exclude Source Files here
#####################################################
#EXCLUDESRC	= $(wildcard hae*.c) dz1_thread_mainb.c
#EXCLUDE		= $(EXCLUDESRC:%.c=%.o)

#####################################################
### Defines for buileing TestProgram or Execution ###
#####################################################
APP_CFLAGS	= -DGITSN_NEW_ASN_TOOL
APP_LDFLAGS	= -l$(LIBNAME)

MAIN		=	#set test main object
MAINS		+= 	$(MAIN)

PROG		=	#set test program name
PROGS		+= 	$(PROG)

#####################################################
###           Define Building Rules               ###  
#####################################################

local_build:lib

lib: objdir_chk $(OBJS)
	$(AR) rc $(LIBFILE) $(ROBJS)
	$(MV) $(LIBFILE) $(LIBDIR)

local_test:lib $(MAINS)
	$(CC) -o $(PROG)$(NATIVE_EXT) $(MAIN) $(LDFLAGS)
	$(STRIP) $(PROG)$(NATIVE_EXT) -o $(PROG)$(STRIP_EXT)

local_clean:
	$(RM) -r $(OBJDIR)
	$(RM) $(LIBDIR)/$(LIBFILE)

local_install:
#write install scripti here
