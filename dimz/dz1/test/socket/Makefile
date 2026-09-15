ROOT		= ../..
include $(ROOT)/dz1build.mk

EXCLUDESRC	= $(wildcard hae*.c) TestEnv.c \
			  dz1_sock_addr_main.c \
			  dz1_tcp_socket_client.c \
			  dz1_tcp_socket_server.c \
			  dz1_udp_sock_client_test.c \
			  dz1_udp_sock_server_test.c

EXCLUDE		= $(EXCLUDESRC:%.c=%.o)

ifeq (LINUX,$(PLATFORM))
PLATFORM_OBJS	=
endif

#####################################################
### Defines for buileing TestProgram or Execution ###
#####################################################

LIBNAME		= dz1sockettest
LIBFILE		= lib$(LIBNAME).a

SUB_LDFLAGS	=	-l$(LIBNAME) \
				-ldz1shell \
				-ldz1termio \
				-ldz1socket \
				-ldz1stream \
				-ldz1task \
				-ldz1struct \
				-ldz1kernel

#############################
### Test 1
#############################
MAIN1		=	dz1_sock_addr_main.o
MAINS		+= 	$(MAIN1)

PROG1		=	dz1_sock_addr_main
PROGS		+= 	$(PROG1)

#############################
### Test 2
#############################
MAIN2		=	dz1_tcp_socket_client.o
MAINS		+= 	$(MAIN2)

PROG2		=	dz1_tcp_socket_client
PROGS		+= 	$(PROG2)

#############################
### Test 3
#############################
MAIN3		=	dz1_tcp_socket_server.o
MAINS		+= 	$(MAIN3)

PROG3		=	dz1_tcp_socket_server
PROGS		+= 	$(PROG3)

#############################
### Test 4
#############################
MAIN4		=	dz1_udp_sock_client_test.o
MAINS		+= 	$(MAIN4)

PROG4		=	dz1_udp_sock_client_test
PROGS		+= 	$(PROG4)

#############################
### Test 5
#############################
MAIN5		=	dz1_udp_sock_server_test.o
MAINS		+= 	$(MAIN5)

PROG5		=	dz1_udp_sock_server_test
PROGS		+= 	$(PROG5)

#####################################################
###           Define Building Rules               ###  
#####################################################

local_build:test

lib: objdir_chk $(OBJS) $(PLATFORM_OBJS)
	$(AR) rc $(LIBFILE) $(ROBJS) $(PLATFORM_OBJS)
	$(MV) $(LIBFILE) $(LIBDIR)

local_test:lib $(MAINS)
	$(CC) -o $(PROG1)$(NATIVE_EXT) $(OBJDIR)/$(MAIN1) $(LDFLAGS) $(PLATFORM_OBJS)
	$(STRIP) $(PROG1)$(NATIVE_EXT) -o $(PROG1)$(STRIP_EXT)

	$(CC) -o $(PROG2)$(NATIVE_EXT) $(OBJDIR)/$(MAIN2) $(LDFLAGS) $(PLATFORM_OBJS)
	$(STRIP) $(PROG2)$(NATIVE_EXT) -o $(PROG2)$(STRIP_EXT)

	$(CC) -o $(PROG3)$(NATIVE_EXT) $(OBJDIR)/$(MAIN3) $(LDFLAGS) $(PLATFORM_OBJS)
	$(STRIP) $(PROG3)$(NATIVE_EXT) -o $(PROG3)$(STRIP_EXT)

	$(CC) -o $(PROG4)$(NATIVE_EXT) $(OBJDIR)/$(MAIN4) $(LDFLAGS) $(PLATFORM_OBJS)
	$(STRIP) $(PROG4)$(NATIVE_EXT) -o $(PROG4)$(STRIP_EXT)

	$(CC) -o $(PROG5)$(NATIVE_EXT) $(OBJDIR)/$(MAIN5) $(LDFLAGS) $(PLATFORM_OBJS)
	$(STRIP) $(PROG5)$(NATIVE_EXT) -o $(PROG5)$(STRIP_EXT)

local_clean:
	$(RM) $(OBJS) $(PLATFORM_OBJS) $(MAINS) $(LIBFILE) $(STRIPPED_PROGS) $(NATIVED_PROGS)
	$(RM) -r $(OBJDIR)

local_install:
