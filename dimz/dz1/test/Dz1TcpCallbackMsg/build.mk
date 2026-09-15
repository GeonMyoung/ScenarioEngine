include $(TESTROOT)/../../dz1build.mk

TESTINC		= $(TESTROOT)/include
TESTLIBDIR	= $(TESTROOT)/lib/$(TARGET_TYPE)lib

CFLAGS		+= -I$(TESTINC)
