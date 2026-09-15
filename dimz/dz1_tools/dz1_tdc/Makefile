ROOT		= .
include $(ROOT)/build.mk

EXCLUDESRC	= 
EXCLUDE		= $(EXCLUDESRC:%.c=%.o) $(MAINS) xtest.o ytest.o

CFLAGS		+= -I.
#####################################################
### Defines for buileing TestProgram or Execution ###
#####################################################

LIBNAME		= dz1tdc
LIBFILE		= lib$(LIBNAME).a

SUB_LDFLAGS	= $(SHELL_LIBS) -l$(LIBNAME)

ZMAIN		=	ztest.o
MAINS		+= 	$(ZMAIN)

ZPROG		=	ztest
PROGS		+= 	$(ZPROG)

QMAIN		=	qtest.o
MAINS		+= 	$(QMAIN)

QPROG		=	qtest
PROGS		+= 	$(QPROG)

MAIN		=	main.o
PROG		=	tdc

#####################################################
###           Define Building Rules               ###  
#####################################################

local_build:objdir_chk libdir_chk lib main.o
	$(CC) -o $(OUTPUT_PREFIX)$(PROG)$(NATIVE_EXT) $(OBJDIR)/$(MAIN) $(LDFLAGS)
	$(STRIP) $(OUTPUT_PREFIX)$(PROG)$(NATIVE_EXT) -o $(OUTPUT_PREFIX)$(PROG)$(STRIP_EXT)
	cp $(OUTPUT_PREFIX)$(PROG)$(STRIP_EXT) $(ROOT)/..

lib: $(OBJS) $(PLATFORM_OBJS)
	$(AR) rc $(LIBFILE) $(ROBJS) $(PLATFORM_OBJS)
	$(MV) $(LIBFILE) $(LIBDIR)

local_test:lib $(MAINS)
	$(CC) -o $(ZPROG)$(NATIVE_EXT) $(ZMAIN) $(LDFLAGS)
	$(STRIP) $(ZPROG)$(NATIVE_EXT) -o $(ZPROG)$(STRIP_EXT)

	$(CC) -o $(QPROG)$(NATIVE_EXT) $(QMAIN) $(LDFLAGS)
	$(STRIP) $(QPROG)$(NATIVE_EXT) -o $(QPROG)$(STRIP_EXT)

rem:
	$(RM) sample_module*.[cho]
	$(RM) subdef.[cho]
	$(RM) Dz1TdcObject.[cho]

local_clean:
	$(RM) $(ROBJS) $(PLATFORM_OBJS) $(MAINS) $(LIBFILE) $(STRIPPED_PROGS) $(NATIVED_PROGS) $(OUTPUT_PREFIX)tdc*
	$(RM) -r $(OBJDIR)
	$(RM) -r $(LIBDIR)

local_install:
