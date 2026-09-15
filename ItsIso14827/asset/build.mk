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

SDK_ROOT		 = $(ROOT)/..
SDK_INC			 = $(SDK_ROOT)/include
SDK_LIB			 = $(SDK_ROOT)/lib/$(TARGET_TYPE)lib

EXT_CFLAGS		+= -I$(SDK_INC)
EXT_LDFLAGS		+= -L$(SDK_LIB)

###############################################################################
###     ItsIso14827                                                         ###
###############################################################################
EXT_LDFLAGS	+= -litsiso14827

###############################################################################
###     Iso14827Dz1                                                         ###
###############################################################################
EXT_LDFLAGS	+= -liso14827dz1

###############################################################################
###     Iso14827NewAsn                                                      ###
###############################################################################
EXT_LDFLAGS	+= -liso14827asn

###############################################################################
###     dz1_gasn_support                                                    ###
###############################################################################
EXT_LDFLAGS	+= -ldz1gasnsupport

###############################################################################
###     ASN.1.GITSN                                                         ###
###############################################################################
ASN1ROOT	 =	$(SDK_ROOT)/ASN.1.GITSN.LIB
ASN1INC		 =	$(ASN1ROOT)/include
ASN1LIB		 =	$(ASN1ROOT)/lib/$(TARGET_TYPE)lib

EXT_CFLAGS	+=	-I$(ASN1INC)
EXT_LDFLAGS	+= -L$(ASN1LIB) -lasn1gitsn

###############################################################################
###     dimz:dz1                                                            ###
###############################################################################
EXT_LDFLAGS	+= 	-ldz1shell \
				-ldz1termio \
				-ldz1asn \
				-ldz1fsm \
				-ldz1task \
				-ldz1parser \
				-ldz1stream \
				-ldz1socket \
				-ldz1struct \
			  	-ldz1kernel

###############################################################################
###     Codeconv                                                            ###
###############################################################################
EXT_LDFLAGS	+= -lcodeconv

###############################################################################
###     Conditional Setting                                                 ###
###############################################################################
ifeq ($(OS_TYPE),SunOS)
EXT_LDFLAGS	+= -lsocket -lnsl 
endif

###############################################################################
###     Target Setting                                                      ###
###############################################################################
OBJDIR		 = $(TARGET_TYPE)obj

###############################################################################
###     CFLAGS Setting                                                     ###
###############################################################################
CFLAGS		 = -g -D_REENTRANT -DGITSN_NEW_ASN_TOOL -D$(PLATFORM) -Wall -Werror \
			   -D__SYSTEM_ENDIAN_LITTLE__\
			   $(CROSS_CFLAGS)
CFLAGS		+= $(EXT_CFLAGS)

###############################################################################
###     LDFLAGS Setting                                                     ###
###############################################################################
LDFLAGS		 = 	-L$(LIBDIR) -l$(LIBNAME) $(EXT_LDFLAGS) \
				-lm -lrt -lpthread

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

