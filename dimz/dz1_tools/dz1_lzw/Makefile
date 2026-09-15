ROOT		= .
include dz1_lzw.mk

SUB_LDFLAGS	= $(SHELL_LIBS) -l$(LIBNAME)

MAIN		=	dz1_lzwTest.o
MAINS		+= 	$(MAIN)

PROG		=	dz1_lzwTest
PROGS		+= 	$(PROG)

PROGS_UTP	 = $(PROGS:%=%$(NATIVE_EXT))
PROGS_STP	 = $(PROGS:%=%$(STRIP_EXT))

local_build:
	$(MAKE) -C src OS_TYPE=`uname`

local_clean:
	$(MAKE) -C src OS_TYPE=`uname` clean
	$(RM) -r $(LIBDIR)
	$(RM) -r $(OBJDIR)
	$(RM) $(PROGS_UTP) $(PROGS_STP)

local_test: objdir_chk local_build $(MAINS)
	$(CC) -o $(PROG)$(NATIVE_EXT) $(OBJDIR)/$(MAIN) $(LDFLAGS)
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
