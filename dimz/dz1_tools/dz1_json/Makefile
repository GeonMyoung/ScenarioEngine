ROOT	= .
include $(ROOT)/dz1_json.mk

SUB_LDFLAGS	= $(SHELL_LIBS) -l$(LIBNAME)

TEST_SRCS	 = $(wildcard dz1_jsonTest*.c)
TEST		 = $(TEST_SRCS:%.c=%.o)
TEST_OBJS	 = $(TEST:%=$(OBJDIR)/%)

COMP_SRCS	 = $(wildcard dz1_tjsonc*.c)
COMP		 = $(COMP_SRCS:%.c=%.o)
COMP_OBJS	 = $(COMP:%=$(OBJDIR)/%)

PROG_TEST	=	dz1_jsonTest
PROGS		+= 	$(PROG_TEST)

PROG_COMP	=	tjsonc
PROGS		+= 	$(PROG_COMP)

PROGS_NTV	=	$(PROGS:%=%$(NATIVE_EXT))
PROGS_STP	=	$(PROGS:%=%$(STRIP_EXT))

local_build:
	$(MAKE) -C src OS_TYPE=`uname`

local_clean:
	$(MAKE) -C src OS_TYPE=`uname` clean
	$(RM) -r $(LIBDIR)
	$(RM) -r $(OBJDIR)
	$(RM) $(PROGS_NTV) $(PROGS_STP)

local_test: objdir_chk local_build $(TEST) $(COMP)
	$(CC) -o $(PROG_TEST)$(NATIVE_EXT) $(TEST_OBJS) $(LDFLAGS)
	$(STRIP) $(PROG_TEST)$(NATIVE_EXT) -o $(PROG_TEST)$(STRIP_EXT)
	$(CC) -o $(PROG_COMP)$(NATIVE_EXT) $(COMP_OBJS) $(LDFLAGS)
	$(STRIP) $(PROG_COMP)$(NATIVE_EXT) -o $(PROG_COMP)$(STRIP_EXT)

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
