ROOT		= ../..
TESTROOT	= .
include build.mk

MAIN		=	Dz1TcpCallbackServerTest.o
PROG		=	Dz1TcpCallbackServerTest

SUB_LDFLAGS	= 	-L$(MSGLIBDIR) -L$(TESTLIBDIR) -l$(LIBNAME) -l$(MSGLIBNAME)\
				-ldz1shell -ldz1termio\
				-ldz1task\
				-ldz1socket\
				-ldz1stream\
				-ldz1struct -ldz1kernel

local_build:
	$(MAKE) -C src OS_TYPE=`uname`

local_clean:
	$(MAKE) -C src OS_TYPE=`uname` clean
	$(RM) -r $(TESTLIBDIR) $(OBJDIR)
	$(RM) $(PROG)$(NATIVE_EXT) $(PROG)$(STRIP_EXT)

local_test: objdir_chk local_build $(MAIN)
	$(CC) -o $(PROG)$(NATIVE_EXT) $(OBJDIR)/$(MAIN) $(LDFLAGS) $(PLATFORM_OBJS)
	$(STRIP) $(PROG)$(NATIVE_EXT) -o $(PROG)$(STRIP_EXT)

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
