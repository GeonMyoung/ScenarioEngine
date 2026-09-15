ROOT		= ..
include $(ROOT)/dz1_inet.mk

EXCLUDESRC	= 
EXCLUDE		= $(EXCLUDESRC:%.c=%.o) $(MAINS)

CFLAGS		+= -I.
#####################################################
### Defines for buileing TestProgram or Execution ###
#####################################################

SUB_LDFLAGS	= $(SHELL_LIBS) -l$(LIBNAME)

MAIN		=	dz1_ftp_client.o
MAINS		+= 	$(MAIN)

PROG		=	dz1_ftp_client
PROGS		+= 	$(PROG)

MAIN_MSG	= dz1_inet_ftp_control_pi_msg_test.o
MAINS		+= $(MAIN_MSG)

PROG_MSG	= dz1_inet_ftp_control_pi_msg_test
PROGS		+= $(PROG_MSG)

MAIN_TELNET	= dz1_telnet.o
MAINS		+= $(MAIN_TELNET)

PROGS_TELNET	= dz1_telnet
PROGS			+= $(PROGS_TELNET)

MAIN_TELNETD	= dz1_telnetd.o
MAINS			+= $(MAIN_TELNETD)

PROGS_TELNETD	= dz1_telnetd
PROGS			+= $(PROGS_TELNETD)

#####################################################
###           Define Building Rules               ###  
#####################################################

local_build:objdir_chk libdir_chk lib

lib: $(OBJS) $(PLATFORM_OBJS)
	$(AR) rc $(LIBFILE) $(ROBJS) $(PLATFORM_OBJS)
	$(MV) $(LIBFILE) $(LIBDIR)

local_test:lib $(MAINS)
	$(CC) -o $(PROG)$(NATIVE_EXT) $(MAIN) $(LDFLAGS)
	$(STRIP) $(PROG)$(NATIVE_EXT) -o $(PROG)$(STRIP_EXT)

local_clean:
#	$(RM) $(ROBJS) $(PLATFORM_OBJS) $(MAINS) $(LIBFILE) $(STRIPPED_PROGS) $(NATIVED_PROGS)
	$(RM) -r $(OBJDIR)
	$(RM) -r $(LIBDIR)/$(LIBFILE)

local_install:
