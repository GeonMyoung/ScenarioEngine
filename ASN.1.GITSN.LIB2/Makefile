ROOT	 =	.
include $(ROOT)/ASN.1.GITSN.mk

local_build:libd

libd:libdir_chk
	$(MAKE) -C SupportLib
	$(MAKE) -C lib

package:lib
	./mkpackage

clean:
	$(MAKE) -C SupportLib clean
	$(MAKE) -C lib clean
	$(RM) SupportLib.*.tar.gz

