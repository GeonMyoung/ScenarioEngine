include $(ROOT)/dz1build.mk

MSGDIR		= $(TESTROOT)/../Dz1TcpCallbackMsg
MSGINC		= $(MSGDIR)/include
MSGLIBDIR	= $(MSGDIR)/lib/$(TARGET_TYPE)lib
MSGLIBNAME	= Dz1TcpCallbackMsg

TESTINC		= $(TESTROOT)/include
TESTLIBDIR	= $(TESTROOT)/lib/$(TARGET_TYPE)lib

CFLAGS		+= -I$(MSGINC) -I$(TESTINC)
