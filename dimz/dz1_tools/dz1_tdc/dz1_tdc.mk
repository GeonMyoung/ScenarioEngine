###############################################################################
###             Basic Setting                                               ###
###############################################################################
SHELL	=	/bin/bash
HOSTCC	=	gcc
CC      =   $(CROSS_COMPILE)$(HOSTCC)
C++		=	$(CROSS_COMPILE)g++
AR      =   $(CROSS_COMPILE)ar
STRIP	=	$(CROSS_COMPILE)strip
RM      =   rm -f
MV      =   mv
CP      =   cp
MAKE    =   make

###############################################################################
###      Macro Script For Some Compile Variable                             ###
###############################################################################
ifeq (,$(CROSS_COMPILE))

ifeq (Linux,$(OS_TYPE))
PLATFORM 		= LINUX
else #Linux
ifeq (SunOS,$(OS_TYPE))
PLATFORM 		= SUN
else #SunOS
PLATFORM 		= NONE
endif #SunOS
endif #Linux

TARGET_TYPE		= host-

else # CROSS_COMPILE
PLATFORM		= LINUX
CROSS_CFLAGS	= -msoft-float

TARGET_TYPE		= $(CROSS_COMPILE)
endif #CROSS_COMPILE

TARGET_LIB		= $(TARGET_TYPE)lib
TARGET_OBJ		= $(TARGET_TYPE)obj

###############################################################################
###     Path Definition                                                     ###
###############################################################################
INCDIR		 = $(ROOT)/include
LIBDIR  	 = $(ROOT)/

COPT_INC	 = $(INCDIR)

###############################################################################
### DZ1 Path
###############################################################################
DZ1DIR		= $(ROOT)/../../dz1
DZ1INC		= $(DZ1DIR)/include
DZ1LIB		= $(DZ1DIR)/lib/$(TARGET_LIB)

COPT_INC	+= $(DZ1INC)
LDPATH		+= -L$(DZ1LIB)
LDLIB_DZ1	= -ldz1tdcinfo -ldz1util -ldz1parser -ldz1stream -ldz1struct -ldz1kernel

###############################################################################
### TDC Info Path
###############################################################################
INFODIR		= $(ROOT)/../dz1_tdc_info
INFOINC		= $(INFODIR)/include
INFOLIB		= $(INFODIR)/lib/$(TARGET_LIB)

COPT_INC	+= $(INFOINC)
LDPATH		+= -L$(INFOLIB)
LDLIB_INFO	= -ldz1tdcinfo

###############################################################################
### Codeconv Path
###############################################################################
CNVDIR		= $(ROOT)/../../../codeconv
CNVINC		= $(CNVDIR)/include
CNVLIB		= $(CNVDIR)/lib/$(TARGET_LIB)

COPT_INC	+= $(CNVINC)
LDPATH		+= -L$(CNVLIB)/aaaaa
LDLIB_CNV	= -lcodeconv

###############################################################################
###     CFLAGS Setting                                                     ###
###############################################################################
CFLAGS		 = -g -D_REENTRANT -D_GNU_SOURCE -D$(PLATFORM) -Wall \
			   -D__SYSTEM_ENDIAN_LITTLE__\
			   $(CROSS_CFLAGS) $(COPT_INC)

###############################################################################
###     LDFLAGS Setting                                                     ###
###############################################################################
LDLIB_OS	 = -lrt -lpthread
ifeq ($(OS_TYPE),SunOS)
LDLIB_OS	+= -lsocket -lnsl 
endif

LDFLAGS		 = $(LDPATH) \
			   $(SUB_LDFLAGS) \
			   $(LDLIB_DZ1) \
			   $(LDLIB_CNV) \
			   $(LDLIB_OS)

SHELL_LIBS	= -ldz1shell -ldz1termio

###############################################################################
###      SURFFIXES Setting                                                  ###
###############################################################################
.SUFFIXES: .c .cpp
.ccp.o:
	$(C++) $(CFLAGS) -Wno-deprecated $^ -c -o $@
.c.o:
	$(CC) $(CFLAGS) $^ -c -o $@

#STRIP_EXT	= _stripped
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


###############################################################################
###        Set Default Depentancy                                           ###
###############################################################################
all:os_check local_build

clean:os_check local_clean

clobber:os_check local_clobber

test:os_check local_test

install:os_check local_install

uninstall:os_check local_uninstall

os_check:
	@if [ "$(CROSS_COMPILE)" == "" ] && [ "$(PLATFORM)" = "NONE" ]; \
		then echo "OS_TYPE must set as like \"make OS_TYPE=\`uname\`\""; \
		exit 1; \
	fi

