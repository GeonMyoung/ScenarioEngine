ROOT	= ../..
include $(ROOT)/ASN.1.GITSN.mk

EXCLUDE		 =	

TARGET = libmem.a

local_build: objdir_chk libdir_chk $(OBJS)
	$(AR) -r $(TARGET) $(ROBJS)
	mv $(TARGET) $(LIBDIR)

clean:
	$(RM) -r $(OBJDIR)
	$(RM) $(LIBDIR)/$(TARGET)
