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
###     dimz:dz1_tools:dz1_parser_util                                      ###
###############################################################################
PSUDIR		 =	$(ROOT)/../dz1_parser_util
PSUINC		 =	$(PSUDIR)/include
PSULIB		 =	$(PSUDIR)/lib/$(TARGET_TYPE)lib

EXT_CFLAGS	+=	-I$(PSUINC)
EXT_LDFLAGS	+=	-L$(PSULIB) \
				-ldz1parserutil
###############################################################################
###     dimz:dz1_tools:dz1_tdcInfo                                          ###
###############################################################################
TDIDIR		 =	$(ROOT)/../dz1_tdc_info
TDIINC		 =	$(TDIDIR)/include
TDILIB		 =	$(TDIDIR)/lib/$(TARGET_TYPE)lib

EXT_CFLAGS	+=	-I$(TDIINC)
EXT_LDFLAGS	+=	-L$(TDILIB)\
				-ldz1tdcinfo
###############################################################################
###     dimz:dz1                                                            ###
###############################################################################
DZ1DIR		 = $(ROOT)/../../dz1
DZ1INC		 = $(DZ1DIR)/include
DZ1LIB		 = $(DZ1DIR)/lib/$(TARGET_TYPE)lib

EXT_CFLAGS	+= -I$(DZ1INC)
EXT_LDFLAGS	+= -L$(DZ1LIB) \
				-ldz1shell \
				-ldz1termio \
				-ldz1parser \
				-ldz1stream \
				-ldz1socket \
				-ldz1struct \
			  	-ldz1kernel

###############################################################################
###     Codeconv                                                            ###
###############################################################################
CCVDIR		 = $(ROOT)/../../../codeconv
CCVINC		 = $(CCVDIR)/include
CCVLIB		 = $(CCVDIR)/lib/$(TARGET_TYPE)lib

EXT_CFLAGS	+= -I$(CCVINC)
EXT_LDFLAGS	+= -L$(CCVLIB) -lcodeconv

###############################################################################
###     Conditional Setting                                                 ###
###############################################################################
ifeq ($(OS_TYPE),SunOS)
EXT_LDFLAGS	+= -lsocket -lnsl 
endif

###############################################################################
###     Target Setting                                                      ###
###############################################################################
LIBNAME		 = dz1json
LIBFILE		 = lib$(LIBNAME).a
INCDIR		 = $(ROOT)/include
LIBDIR  	 = $(ROOT)/lib/$(TARGET_TYPE)lib
OBJDIR		 = $(TARGET_TYPE)obj

###############################################################################
###     CFLAGS Setting                                                     ###
###############################################################################
CFLAGS		 = -g -D_REENTRANT -DGITSN_NEW_ASN_TOOL -D$(PLATFORM) -Wall  \
			   -D__SYSTEM_ENDIAN_LITTLE__\
			   $(CROSS_CFLAGS) $(PLATFORM_CFLAGS)
CFLAGS		+= -I$(INCDIR) $(EXT_CFLAGS)

###############################################################################
###     LDFLAGS Setting                                                     ###
###############################################################################
LDFLAGS		 = -L$(LIBDIR) -l$(LIBNAME) $(EXT_LDFLAGS) \
				-lrt -lpthread -lssl -lcrypto

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

