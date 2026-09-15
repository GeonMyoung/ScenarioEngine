ROOT		= ../..
include $(ROOT)/dz1build.mk

EXCLUDESRC	= $(wildcard hae*.c)
EXCLUDE		= $(EXCLUDESRC:%.c=%.o)

#####################################################
### Defines for buileing TestProgram or Execution ###
#####################################################

LIBNAME		= dz1task
LIBFILE		= lib$(LIBNAME).a

SUB_LDFLAGS	= $(SHELL_LIBS) -l$(LIBNAME) -ldz1struct -ldz1kernel

QMAIN		=	dz1_sigmsg_queue_main.o
MAINS		+= 	$(QMAIN)

QPROG		=	dz1_sigmsg_queue_main
PROGS		+= 	$(QPROG)

CTMAIN		=	dz1_task_timer_main.o
MAINS		+= 	$(CTMAIN)

CTPROG		=	dz1_task_timer_main
PROGS		+= 	$(CTPROG)

MAIN		=	dz1_task_main.o
MAINS		+= 	$(MAIN)

PROG		=	dz1_task_main
PROGS		+= 	$(PROG)

#####################################################
###           Define Building Rules               ###  
#####################################################

local_build:objdir_chk libdir_chk lib

lib: $(OBJS) $(PLATFORM_OBJS)
	$(AR) rc $(LIBFILE) $(ROBJS) $(PLATFORM_OBJS)
	$(MV) $(LIBFILE) $(LIBDIR)

local_test:lib $(MAINS)
	$(CC) -o $(QPROG)$(NATIVE_EXT) $(QMAIN) $(LDFLAGS)
	$(STRIP) $(QPROG)$(NATIVE_EXT) -o $(QPROG)$(STRIP_EXT)

	$(CC) -o $(CTPROG)$(NATIVE_EXT) $(CTMAIN) $(LDFLAGS)
	$(STRIP) $(CTPROG)$(NATIVE_EXT) -o $(CTPROG)$(STRIP_EXT)

	$(CC) -o $(PROG)$(NATIVE_EXT) $(MAIN) $(LDFLAGS)
	$(STRIP) $(PROG)$(NATIVE_EXT) -o $(PROG)$(STRIP_EXT)

local_clean:
	$(RM) $(ROBJS) $(PLATFORM_OBJS) $(MAINS) $(LIBFILE) $(STRIPPED_PROGS) $(NATIVED_PROGS)
	$(RM) -r $(OBJDIR)

local_install:
