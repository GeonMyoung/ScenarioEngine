###############################################################################
### Foundation Setting
###############################################################################
CC		= $(CROSS_COMPILE)gcc
AR		= $(CROSS_COMPILE)ar
RM		= rm -f

ifeq (,$(CROSS_COMPILE))
TARGET_TYPE		 = host-
else
TARGET_TYPE		 = $(CROSS_COMPILE)
endif

###############################################################################
### Target Setting
###############################################################################
LIBNAME			 = iso14827asn
LIBFILE			 = lib$(LIBNAME).a

OBJS			 = ISO14827_1.o ISO14827_2.o
ROBJS			 = $(OBJS:%.o=$(OBJDIR)/%.o)

###############################################################################
### Path Setting
###############################################################################
ROOT			 = .
ASN1DIR			 = $(ROOT)/../ASN.1.GITSN.LIB
OBJDIR			 = $(TARGET_TYPE)obj
LIBDIR			 = $(ROOT)/lib/$(TARGET_TYPE)lib

###############################################################################
### Flags Setting
###############################################################################
CFLAGS	= -g -D_REENTRANT -I$(ASN1DIR)/SupportLib

###############################################################################
###      SURFFIXES Setting                                                  ###
###############################################################################
.SUFFIXES: .c .cpp .o
vpath		%.o $(OBJDIR)
.ccp.o:
	$(C++) $(CFLAGS) -Wno-deprecated $^ -c -o $(OBJDIR)/$@
.c.o:
	$(CC) $(CFLAGS) $^ -c -o $(OBJDIR)/$@


all:libdir_chk lib

objdir_chk:
	@if ! [ -d $(OBJDIR) ]; then mkdir $(OBJDIR); fi

libdir_chk:
	@if ! [ -d $(LIBDIR) ]; then mkdir -p $(LIBDIR); fi

lib:libdir_chk objdir_chk $(OBJS)
	$(AR) -rc $(LIBDIR)/$(LIBFILE) $(ROBJS)

clean:
	$(RM) -r $(LIBDIR)
	$(RM) -r $(OBJDIR)

