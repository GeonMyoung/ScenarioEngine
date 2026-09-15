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

###############################################################################
###     Iso14827NewAsn                                                      ###
###############################################################################
ISO14827	 = $(ROOT)/../Iso14827NewAsn
I14827INC	 = $(ISO14827)
I14827LIB	 = $(ISO14827)/lib/$(TARGET_TYPE)lib

EXT_CFLAGS	+= -I$(I14827INC)
EXT_LDFLAGS	+= -L$(I14827LIB) -liso14826asn

###############################################################################
###     dz1_gasn_support                                                    ###
###############################################################################
DZ1TOOL		 = $(ROOT)/../dimz/dz1_tools
DZ1GASN		 = $(DZ1TOOL)/dz1_gasn_support
DZ1GAINC	 = $(DZ1GASN)/include
DZ1GALIB	 = $(DZ1GASN)/lib/$(TARGET_TYPE)lib

EXT_CFLAGS	+= -I$(DZ1GAINC)
EXT_LDFLAGS	+= -L$(DZ1GALIB) -ldz1gasnsupport

###############################################################################
###     ASN.1.GITSN                                                         ###
###############################################################################
ASN1DIR		 = $(ROOT)/../ASN.1.GITSN.LIB
ASN1INC		 = $(ASN1DIR)/SupportLib
ASN1LIB		 = $(ASN1DIR)/lib/$(TARGET_TYPE)lib

EXT_CFLAGS	+= -I$(ASN1INC)
EXT_LDFLAGS	+= -L$(ASN1LIB) \
				-lber \
				-lper \
				-ltool \
				-lio \
				-lmem

###############################################################################
###     dimz:dz1                                                            ###
###############################################################################
DZ1DIR		 = $(ROOT)/../dimz/dz1
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
CCVDIR		 = $(ROOT)/../codeconv
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
LIBNAME		 = iso14827dz1
LIBFILE		 = lib$(LIBNAME).a
INCDIR		 = $(ROOT)/include
LIBDIR  	 = $(ROOT)/lib/$(TARGET_TYPE)lib
OBJDIR		 = $(TARGET_TYPE)obj

###############################################################################
###     CFLAGS Setting                                                     ###
###############################################################################
CFLAGS		 = -g -D_REENTRANT -DGITSN_NEW_ASN_TOOL -D$(PLATFORM) -Wall -Werror \
			   -D__SYSTEM_ENDIAN_LITTLE__\
			   $(CROSS_CFLAGS)
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

