ROOT		= .
include $(ROOT)/dz1_bin2src.mk

EXCLUDESRC	= 
EXCLUDE		= $(EXCLUDESRC:%.c=%.o) $(MAINS)

CFLAGS		+= -I.

LIBNAME		=
LIBFILE		= lib$(LIBNAME).a

SUB_LDFLAGS	= $(SHELL_LIBS)

BMAIN		= dz1_bin2src_main.o
MAINS		+= $(BMAIN)

BPROG		= dz1_bin2src
PROGS		+= $(BPROG)

FMAIN		= dz1_bin2src_main.o
MAINS		+= $(FMAIN)

FPROG		= dz1_bin2src
PROGS		+= $(FPROG)

local_build: $(MAINS)
	$(CC) -o $(BPROG)$(NATIVE_EXT) $(BMAIN) $(LDFLAGS)
	$(STRIP) $(BPROG)$(NATIVE_EXT) -o $(BPROG)$(STRIP_EXT)

	$(CC) -o $(FPROG)$(NATIVE_EXT) $(FMAIN) $(LDFLAGS)
	$(STRIP) $(FPROG)$(NATIVE_EXT) -o $(FPROG)$(STRIP_EXT)

local_clean:
	$(RM) $(OBJS) $(PLATFORM_OBJS) $(MAINS) $(LIBFILE) $(STRIPPED_PROGS) $(NATIVED_PROGS)

local_test: local_build

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
