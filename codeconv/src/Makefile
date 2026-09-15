#####################################################
## Basic Setting
#####################################################
CC		= $(CROSS_COMPILE)gcc
AR		= $(CROSS_COMPILE)ar
MV		= mv

# define EXT. if M$'s OS
EXT		= .exe
#####################################################

#####################################################
## Variable Setting
#####################################################
ifeq (,$(CROSS_COMPILE))
TARGET_TYPE			= host-
else
TARGET_TYPE			= $(CROSS_COMPILE)
endif

TARGET_LIB			= $(TARGET_TYPE)lib
#####################################################

#####################################################
## Output Setting
#####################################################
LIBNAME				= codeconv
LIBFILE				= lib$(LIBNAME).a
LIBDIR				= ../lib/$(TARGET_LIB)
OBJDIR				= $(TARGET_TYPE)obj

#####################################################
## cflag Setting 
#####################################################
CFLAGS	= -I../include

#####################################################
## LD Setting 
#####################################################
LDLIBS				= -l$(LIBNAME)

#####################################################
## File Setting
#####################################################
.SUFFIXES:			.c .o
vpath				%.o $(OBJDIR)

OBJS				= codeconv.o
ROBJS				= $(OBJS:%.o=$(OBJDIR)/%.o)

#####################################################
## Test Program
#####################################################
MAIN	= main.o
MAINS	+= $(MAIN)

PROG	= prog$(EXT)
PROGS	+= $(PROG)

#####################################################
## Dependancy
#####################################################
all: lib

objdir_chk:
	if ! [ -d $(OBJDIR) ]; then mkdir -p $(OBJDIR); fi

libdir_chk:
	if ! [ -d $(LIBDIR) ]; then mkdir -p $(LIBDIR); fi

.c.o:
	$(CC) $(CFLAGS) $^ -c -o $(OBJDIR)/$@

lib: objdir_chk libdir_chk $(OBJS)
	$(AR) rc $(LIBFILE) $(ROBJS)
	$(MV) $(LIBFILE) $(LIBDIR)

test: lib $(MAINS)
	$(CC) -o $(PROG) $(MAIN) -L$(LIBDIR) $(LIBS)

clean:
	$(RM) $(ROBJS) $(LIBNAME) $(MAINS) $(PROGS)
	$(RM) -r $(OBJDIR)
	$(RM) -r $(LIBDIR)
