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

else # CROSS_COMPILE
PLATFORM		= LINUX
CROSS_CFLAGS	= -msoft-float
endif #CROSS_COMPILE

###############################################################################
###     Path Definition                                                     ###
###############################################################################
INCDIR		 = $(ROOT)/include
LIBDIR  	 = $(ROOT)/lib

DZ1DIR		= $(ROOT)/../../dz1
DZ1INC		= $(DZ1DIR)/include
DZ1LIB		= $(DZ1DIR)/lib

DZ1RIFF		= $(DZ1DIR)/riff
RIFFINC		= $(DZ1RIFF)/include
RIFFLIB		= $(DZ1RIFF)/lib

###############################################################################
###     CFLAGS Setting                                                     ###
###############################################################################
CFLAGS		 = -g -D_REENTRANT -D$(PLATFORM) -Wall  \
			   -D__SYSTEM_ENDIAN_LITTLE__\
			   $(CROSS_CFLAGS)
CFLAGS		+= -I$(INCDIR) -I$(RIFFINC) -I$(DZ1INC)

###############################################################################
###     LDFLAGS Setting                                                     ###
###############################################################################
LDFLAGS		 = -L$(LIBDIR) -L$(KBFLIB) -L$(DZ1LIB) $(SUB_LDFLAGS) \
			    -ldz1util -ldz1parser -ldz1struct -ldz1kernel\
				-lrt -lpthread -lssl -lcrypto
ifeq ($(OS_TYPE),SunOS)
LDFLAGS		+= -lsocket -lnsl 
endif
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

