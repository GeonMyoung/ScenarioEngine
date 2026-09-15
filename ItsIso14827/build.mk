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
PLATFORM_LD		= -lm -lrt -lpthread
else #Linux
ifeq (SunOS,$(OS_TYPE))
PLATFORM 		= SUN
PLATFORM_LD		= -lm -lrt -lpthread
else #SunOS
PLATFORM 		= NONE
endif #SunOS
endif #Linux

TARGET_TYPE		= host-
OUTPUT_PREFIX	=

else # CROSS_COMPILE
PLATFORM		= LINUX
CROSS_CFLAGS	= -msoft-float
PLATFORM_LD		= -lm -lrt -lpthread

TARGET_TYPE		= $(CROSS_COMPILE)
OUTPUT_PREFIX	= $(CROSS_COMPILE)

endif #CROSS_COMPILE

###############################################################################
###     GitsnLicenseChk                                                     ###
###############################################################################
GLCROOT		 = $(ROOT)/../GitsnLicenseChk
GLCINC		 = $(GLCROOT)/include
GLCLIB		 = $(GLCROOT)/lib/$(TARGET_TYPE)lib

EXT_CFLAGS	+= -I$(GLCINC)
EXT_LDFLAGS	+= -L$(GLCLIB) -lGitsnLicenseChk

###############################################################################
###     Iso14827Dz1                                                         ###
###############################################################################
ISO14827D	 = $(ROOT)/../Iso14827dz1
I14827DINC	 = $(ISO14827D)/include
I14827DLIB	 = $(ISO14827D)/lib/$(TARGET_TYPE)lib

EXT_CFLAGS	+= -I$(I14827DINC)
EXT_LDFLAGS	+= -L$(I14827DLIB) -liso14827dz1

###############################################################################
###     Iso14827NewAsn                                                      ###
###############################################################################
ISO14827A	 = $(ROOT)/../Iso14827NewAsn
I14827AINC	 = $(ISO14827A)
I14827ALIB	 = $(ISO14827A)/lib/$(TARGET_TYPE)lib

EXT_CFLAGS	+= -I$(I14827AINC)
EXT_LDFLAGS	+= -L$(I14827ALIB) -liso14827asn

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
EXT_LDFLAGS	+= -L$(ASN1LIB) -lasn1gitsn

###############################################################################
###     dimz:dz1                                                            ###
###############################################################################
DZ1DIR		 = $(ROOT)/../dimz/dz1
DZ1INC		 = $(DZ1DIR)/include
DZ1LIB		 = $(DZ1DIR)/lib/$(TARGET_TYPE)lib
DZ1LIBs		 =	dz1shell \
				dz1termio \
				dz1asn \
				dz1fsm \
				dz1task \
				dz1parser \
				dz1stream \
				dz1socket \
				dz1crypt \
				dz1struct \
			  	dz1kernel
DZ1LIBS		 = $(DZ1LIBs:%=-l%)
EXT_CFLAGS	+= -I$(DZ1INC)
EXT_LDFLAGS	+= -L$(DZ1LIB) $(DZ1LIBS)

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
LIBNAME		 = itsiso14827
LIBFILE		 = lib$(LIBNAME).a
INCDIR		 = $(ROOT)/include
LIBDIR  	 = $(ROOT)/lib/$(TARGET_TYPE)lib
OBJDIR		 = $(TARGET_TYPE)obj

###############################################################################
###     CFLAGS Setting                                                     ###
###############################################################################
CFLAGS		 = -g -D_REENTRANT -DGITSN_NEW_ASN_TOOL -D$(PLATFORM) \
			   -D__SYSTEM_ENDIAN_LITTLE__\
			   $(CROSS_CFLAGS)
CFLAGS		+= -I$(INCDIR) $(EXT_CFLAGS)

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

