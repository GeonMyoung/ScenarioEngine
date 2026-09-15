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
PLATFORM_CFLAGS	= -D__WORDSIZE=64
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

###############################################################################
###     Path Definition                                                     ###
###############################################################################
INCDIR			 = $(ROOT)/include
LIBDIR  		 = $(ROOT)/lib/$(TARGET_TYPE)lib
OBJDIR			 = $(TARGET_TYPE)obj

CINC_GLOBAL		 = -I$(INCDIR)
LDPATH_GLOBAL	 = -L$(LIBDIR)

###############################################################################
###     DZ1 Path Definition                                                 ###
###############################################################################
DZ1DIR			= $(ROOT)/../../dz1
DZ1INC			= $(DZ1DIR)/include
DZ1LIB			= $(DZ1DIR)/lib/$(TARGET_TYPE)lib

CINC_GLOBAL		+= -I$(DZ1INC)
LDPATH_GLOBAL	+= -L$(DZ1LIB)
LDLIB_DZ1		= -ldz1util -ldz1parser -ldz1struct -ldz1kernel

###############################################################################
###     BMP Definition
###############################################################################
BMPDIR			= $(ROOT)/../dz1_bmp
BMPINC			= $(BMPDIR)/include
BMPLIB			= $(BMPDIR)/lib/$(TARGET_TYPE)lib

CINC_GLOBAL		+= -I$(BMPINC)
LDPATH_GLOBAL	+= -L$(BMPLIB)
LDLIB_BMP		= -ldz1bmp

###############################################################################
###     CFLAGS Setting                                                     ###
###############################################################################
COPT_GLOBAL		= -g -Wall  $(CROSS_CFLAGS) $(PLATFORM_CFLAGS)

CDEF_GLOBAL		= -D_REENTRANT
CDEF_GLOBAL		+= -D$(PLATFORM)
CDEF_GLOBAL		+= -D__SYSTEM_ENDIAN_LITTLE__

CFLAGS			= $(COPT_GLOBAL) $(CDEF_GLOBAL) $(CINC_GLOBAL)
###############################################################################
###     LDFLAGS Setting                                                     ###
###############################################################################
LDLIB_OS		= -lrt -lpthread -lssl -lcrypto
ifeq ($(OS_TYPE),SunOS)
LDLIB_OS		+= -lsocket -lnsl 
endif
LDLIB_SHELL		= -ldz1shell -ldz1termio

LDLIB_GLOBAL	+= $(LDLIB_BMP)
LDLIB_GLOBAL	+= $(LDLIB_DZ1)
LDLIB_GLOBAL	+= $(LDLIB_OS)

LDFLAGS		 = $(LDPATH_GLOBAL) $(SUB_LDFLAGS) $(LDLIB_GLOBAL)
###############################################################################
###      SURFFIXES Setting                                                  ###
###############################################################################
.SUFFIXES: .c .cpp .o
vpath		%.o $(OBJDIR)
.ccp.o:
	$(C++) $(CFLAGS) -Wno-deprecated $^ -c -o $(OBJDIR)/$@
.c.o:
	$(CC) $(CFLAGS) $^ -c -o $(OBJDIR)/$@

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
	@if ! [ -d $(OBJDIR) ]; then mkdir $(OBJDIR); fi

libdir_chk:
	@if ! [ -d $(LIBDIR) ]; then mkdir -p $(LIBDIR); fi

os_check:
	@if [ "$(CROSS_COMPILE)" == "" ] && [ "$(PLATFORM)" = "NONE" ]; \
		then echo "OS_TYPE must set as like \"make OS_TYPE=\`uname\`\""; \
		exit 1; \
	fi

