ROOT	= ../..
include $(ROOT)/ASN.1.GITSN.mk

EXCLUDE		 =	ASN1_BER_ObjectDescriptor.o

TARGET = libber.a

local_build: objdir_chk libdir_chk $(OBJS)
	$(AR) -r $(TARGET) $(ROBJS)
	mv $(TARGET) $(LIBDIR)

clean:
	$(RM) -r $(OBJDIR)
	$(RM) $(LIBDIR)/$(TARGET)
