SHELL		 = 	/bin/bash
HOSTCC		 =	gcc
CC			 = 	$(CROSS_COMPILE)gcc
C++			 = 	$(CROSS_COMPILE)g++
AR			 = 	$(CROSS_COMPILE)ar
RM			 = 	rm -f
MV			 = 	mv
CP			 = 	cp
MAKE		 = 	make

ifeq (,$(CROSS_COMPILE))
TARGET_TYPE	 =	host-
else
TARGET_TYPE	 = 	$(CROSS_COMPILE)
endif

OBJDIR	 	 =	$(TARGET_TYPE)obj
LIBD		 =	$(TARGET_TYPE)lib
LIBPATH		 =	$(ROOT)/lib
LIBDIR	 	 =	$(LIBPATH)/$(LIBD)

CFLAGS		+= 	-g -I$(ROOT)/SupportLib

.SUFFIXES: .c .cpp
vpath		%.o $(OBJDIR)
.ccp.o:
	$(C++) $(CFLAGS) -Wno-deprecated $^ -c -o $(OBJDIR)/$@
.c.o:
	$(CC) $(CFLAGS) $^ -c -o $(OBJDIR)/$@

#OS_DIR	= OS #just header
TYPE_DIR= TYPE
MEM_DIR = MEM
PER_DIR = PER
BER_DIR = BER
XER_DIR = XER
Tool_DIR = TOOL
IO_DIR = IO

SRC_DIR = $(MEM_DIR) $(PER_DIR) $(BER_DIR) $(TYPE_DIR)

ifeq ($(XER),1)
SRC_DIR += $(XER_DIR)
endif

SRC_DIR += $(Tool_DIR) $(IO_DIR)

CSRCS		 =	$(wildcard *.c)
CPPSRCS		 =	$(wildcard *.cpp)
OBJS		 =	$(filter-out $(MAINS) $(EXCLUDE),$(CSRCS:%.c=%.o) $(CPPSRCS:%.cpp=%.o))
ROBJS		 =	$(OBJS:%.o=$(OBJDIR)/%.o)

all: local_build

objdir_chk:
	@if ! [ -d $(OBJDIR) ]; then mkdir $(OBJDIR); fi

libdir_chk:
	@if ! [ -d $(LIBDIR) ]; then mkdir $(LIBDIR); fi

install: chk_install_dir
	@$(ROOT)/install.sh $(INSTALL_DEST)

chk_install_dir:
	@if [ "$(INSTALL_DEST)" == "" ]; then \
		echo "make install INSTALL_DEST={install_path}"; \
		exit 1; \
	elif ! [ -d $(INSTALL_DEST) ]; then \
		echo "$(INSTALL_DEST) must exist"; \
		exit 1; \
	fi
