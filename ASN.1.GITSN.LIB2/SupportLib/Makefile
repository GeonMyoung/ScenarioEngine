ROOT	= ..
include $(ROOT)/ASN.1.GITSN.mk

local_build:
	for ccc in $(SRC_DIR); do \
		$(MAKE) -C $$ccc; \
	done

clean:
	for ccc in $(SRC_DIR); do \
		$(MAKE) -C $$ccc clean; \
	done
