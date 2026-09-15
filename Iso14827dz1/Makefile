ROOT	= .
include $(ROOT)/build.mk

local_build: libdir_chk
	$(MAKE) -C src OS_TYPE=`uname`

local_clean:
	$(MAKE) -C src OS_TYPE=`uname` clean
	$(RM) -r $(LIBDIR)

local_test: local_build
	$(MAKE) -C src OS_TYPE=`uname` test

local_install: local_build
	@if [ -z "$(INSTALL_ROOT)" ]; then \
		echo "=================================================="; \
		echo "set INSTALL_ROOT=<install top dir path>"; \
		echo "or"; \
		echo "make install INSTALL_ROOT=<install top dir path>"; \
		echo "=================================================="; \
		exit 1; \
	fi
	@rm -rf $(INSTALL_ROOT)
	@mkdir -p $(INSTALL_ROOT)/include
	@mkdir -p $(INSTALL_ROOT)/lib
	@mkdir -p $(INSTALL_ROOT)/bin
	@cp include/*.h $(INSTALL_ROOT)/include
	@cp lib/*.a $(INSTALL_ROOT)/lib
	@cp src/tool/dz1_bin2src $(INSTALL_ROOT)/bin
	@cp src/tool/dz1_dump $(INSTALL_ROOT)/bin
	@cp src/mdefc/tdc $(INSTALL_ROOT)/bin
