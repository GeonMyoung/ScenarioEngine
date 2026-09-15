ROOT		 = ..
include $(ROOT)/ASN.1.GITSN.mk

TARGET		= libasn1gitsn.a
local_build:
	./mergelib $(TARGET) $(LIBD) $(AR)

clean:
	$(RM) -r $(LIBD)
