###############################################################################
###             Basic Setting                                               ###
###############################################################################
HOSTCC	=	gcc
CC      =   $(CROSS_COMPILE)$(HOSTCC)
C++		=	$(CROSS_COMPILE)g++
AR      =   $(CROSS_COMPILE)ar
STRIP	=	$(CROSS_COMPILE)strip
RM      =   rm -f
MV      =   mv
CP      =   cp
MAKE    =   make
SHELL	=	/bin/bash

###############################################################################
###      Macro Script For Some Compile Variable                             ###
###############################################################################
PLATFORM 		= NONE

ifeq (,$(CROSS_COMPILE))
#------------------------------------------------------------------------------
# Host Build mode
#------------------------------------------------------------------------------

TARGET_TYPE		= host-

##########################################
# Codeconv
##########################################
CCVDIR = $(ROOT)/../../codeconv
CCVINC = $(CCVDIR)/include
PLATFORM_CFLAGS	+= -I$(CCVINC)

PF_BASE_LD_FLAG	+= -L$(CCVDIR)/lib/$(TARGET_TYPE)lib
PF_BASE_LIB		+= -lcodeconv

##########################################
# PTHREAD
##########################################
##############
# Linux
##############
ifeq (Linux,$(OS_TYPE))
PLATFORM 		= LINUX
PLATFORM_CFLAGS	+= -D__WORDSIZE=64

PF_BASE_LD_FLAG	+=
PF_BASE_LIB		+= -lssl -lrt -lpthread
endif #Linux

##############
# SUN
##############
ifeq (SunOS,$(OS_TYPE))
PLATFORM 		= SUN
PLATFORM_CFLAGS	+= 

PF_BASE_LD_FLAG	+=
PF_BASE_LIB		+= -lrt -lpthread
endif #SunOS

##############
# OSX
##############
ifeq (Darwin,$(OS_TYPE))
PLATFORM 		= MAC_OS_X
PLATFORM_CFLAGS	+= -D__WORDSIZE=64

PF_BASE_LD_FLAG	+=
PF_BASE_LIB		+= -lpthread
endif #Darwin

else # CROSS_COMPILE
#------------------------------------------------------------------------------
# Cross Build mode
#------------------------------------------------------------------------------
TARGET_TYPE		= $(CROSS_COMPILE)
CROSS_CFLAGS	= -msoft-float

##########################################
# Codeconv
##########################################
CCVDIR = $(ROOT)/../../codeconv
CCVINC = $(CCVDIR)/include
PLATFORM_CFLAGS	+= -I$(CCVINC)

PF_BASE_LD_FLAG	+= -L$(CCVDIR)/lib/$(TARGET_TYPE)lib
PF_BASE_LIB		+= -lcodeconv

##########################################
# PTHREAD
##########################################
PLATFORM		= LINUX
PLATFORM_CFLAGS	+= 

PF_BASE_LD_FLAG	+=
PF_BASE_LIB		+= -lrt -lpthread

endif #CROSS_COMPILE


#------------------------------------------------------------------------------
# Common Configure
#------------------------------------------------------------------------------

###############################################################################
###     Path Definition                                                     ###
###############################################################################
INCDIR		 = $(ROOT)/include
LIBDIR  	 = $(ROOT)/lib/$(TARGET_TYPE)lib
OBJDIR		 = $(TARGET_TYPE)objs

###############################################################################
###     CFLAGS Setting                                                     ###
###############################################################################
CFLAGS		 = -g -D_REENTRANT -D$(PLATFORM) -D_GNU_SOURCE -DDZ1_BUILD -Wall  \
			   -D__SYSTEM_ENDIAN_LITTLE__\
			   $(PLATFORM_CFLAGS) -I$(CCVDIR) $(CROSS_CFLAGS)
CFLAGS		+= -I$(INCDIR)

###############################################################################
###     LDFLAGS Setting                                                     ###
###############################################################################
LDFLAGS		 = -L$(LIBDIR) $(PF_BASE_LD_FLAG) $(SUB_LDFLAGS) $(PF_BASE_LIB)

ifeq ($(OS_TYPE),SunOS)
LDFLAGS		+= -lsocket -lnsl 
endif

SHELL_LIBS	= -ldz1shell -ldz1termio

###############################################################################
###      SURFFIXES Setting                                                  ###
###############################################################################
.SUFFIXES: .c .cpp .o
vpath		%.o $(OBJDIR)

.ccp.o:
	$(C++) $(CFLAGS) -Wno-deprecated $^ -c -o $(OBJDIR)/$@
.c.o:
	$(CC) $(CFLAGS) $^ -c -o $(OBJDIR)/$@

STRIP_EXT	= 
NATIVE_EXT	= _unstrpped

STRIPPED_PROGS	= $(PROGS:%=%$(STRIP_EXT))
NATIVED_PROGS	= $(PROGS:%=%$(NATIVE_EXT))

###############################################################################
### Object List
###############################################################################
CSRCS   =   $(wildcard *.c)
CPPSRCS =   $(wildcard *.cpp)
OBJS    =   $(filter-out $(MAINS) $(EXCLUDE),$(CSRCS:%.c=%.o) $(CPPSRCS:%.cpp=%.o))
ROBJS	=	$(OBJS:%.o=$(OBJDIR)/%.o)

###############################################################################
###        Set Default Depentancy                                           ###
###############################################################################
all:os_check local_build

clean:os_check local_clean

clobber:os_check local_clobber

test:os_check local_test

install:os_check local_install

uninstall:os_check local_uninstall

objdir_chk:
	@if ! [ -d $(OBJDIR) ]; then \
		mkdir $(OBJDIR); \
	fi

libdir_chk:
	@if ! [ -d $(LIBDIR) ]; then \
		mkdir -p $(LIBDIR); \
	fi

os_check:
	@if [ "$(CROSS_COMPILE)" == "" ] && [ "$(PLATFORM)" = "NONE" ]; \
		then echo "OS_TYPE must set as like \"make OS_TYPE=\`uname\`\""; \
		exit 1; \
	fi
#	@if ! [ -f $(ROOT)/include/dz1_conf.h ]; then \
		echo "Configuration first";\
		exit 1; \
	fi

