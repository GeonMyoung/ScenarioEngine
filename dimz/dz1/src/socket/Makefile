ROOT		= ../..
include $(ROOT)/dz1build.mk

EXCLUDESRC	= $(wildcard hae*.c) dz1_sock_addr_mainb.c
EXCLUDE		= $(EXCLUDESRC:%.c=%.o) $(MAINS)

#CFLAGS		+= -DMATCH_ERROR_PRINT
#CFLAGS		+= -DMATCH_TRACE
#CFLAGS		+= -DSYNTAX_DEBUG
#CFLAGS		+= -DLEXER_DEBUG
#####################################################
### Defines for buileing TestProgram or Execution ###
#####################################################

LIBNAME		= dz1socket
LIBFILE		= lib$(LIBNAME).a

SUB_LDFLAGS	= -l$(LIBNAME) -ldz1shell -ldz1struct -ldz1termio -ldz1kernel

AMAIN		=	dz1_sock_addr_main.o
MAINS		+= 	$(AMAIN)

APROG		=	dz1_tcp_sock_addr_main
PROGS		+= 	$(APROG)

SMAIN		=	dz1_tcp_socket_server.o
MAINS		+= 	$(SMAIN)

SPROG		=	dz1_tcp_socket_server
PROGS		+= 	$(SPROG)

CMAIN		=	dz1_tcp_socket_client.o
MAINS		+= 	$(CMAIN)

CPROG		=	dz1_tcp_socket_client
PROGS		+= 	$(CPROG)

UDMAIN		=	dz1_udp_sock_server_test.o
MAINS		+=	$(UDMAIN)

UDPROG		=	dz1_udp_sock_server_test
PROGS		+=	$(UDPROG)

UCMAIN		=	dz1_udp_sock_client_test.o
MAINS		+=	$(UCMAIN)

UCPROG		=	dz1_udp_sock_client_test
PROGS		+=	$(UCPROG)
#####################################################
###           Define Building Rules               ###  
#####################################################

local_build:objdir_chk libdir_chk lib

lib: $(OBJS) $(PLATFORM_OBJS)
	$(AR) rc $(LIBFILE) $(ROBJS) $(PLATFORM_OBJS)
	$(MV) $(LIBFILE) $(LIBDIR)

local_test:lib $(MAINS)
	$(CC) -o $(APROG)$(NATIVE_EXT) $(AMAIN) $(LDFLAGS)
	$(STRIP) $(APROG)$(NATIVE_EXT) -o $(APROG)$(STRIP_EXT)

	$(CC) -o $(SPROG)$(NATIVE_EXT) $(SMAIN) $(LDFLAGS)
	$(STRIP) $(SPROG)$(NATIVE_EXT) -o $(SPROG)$(STRIP_EXT)

	$(CC) -o $(CPROG)$(NATIVE_EXT) $(CMAIN) $(LDFLAGS)
	$(STRIP) $(CPROG)$(NATIVE_EXT) -o $(CPROG)$(STRIP_EXT)

	$(CC) -o $(UDPROG)$(NATIVE_EXT) $(UDMAIN) $(LDFLAGS)
	$(STRIP) $(UDPROG)$(NATIVE_EXT) -o $(UDPROG)$(STRIP_EXT)

	$(CC) -o $(UCPROG)$(NATIVE_EXT) $(UCMAIN) $(LDFLAGS)
	$(STRIP) $(UCPROG)$(NATIVE_EXT) -o $(UCPROG)$(STRIP_EXT)

local_clean:
	$(RM) $(ROBJS) $(PLATFORM_OBJS) $(MAINS) $(LIBFILE) $(STRIPPED_PROGS) $(NATIVED_PROGS)
	$(RM) -r $(OBJDIR)

local_install:
