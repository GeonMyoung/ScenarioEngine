ROOT	= .
include $(ROOT)/build.mk

MAIN_OBJS	 = generator.o ItsIso14827TestEam.o ItsIso14827Test_client.o ItsIso14827Test_server.o ItsIso14827Test_msg.o
MAIN_ROBJS	 = $(MAIN_OBJS:%.o=$(OBJDIR)/%.o)

SUB_LDFLAGS	 = $(SHELL_LIBS) -l$(LIBNAME)

MAIN		 = ItsIso14827Test.o
MAINS		+= $(MAIN)

PROG		 = ItsIso14827Test
PROGS		+= $(PROG)

PROGS_NTV	 = $(PROGS:%=%$(NATIVE_EXT))
PROGS_STP	 = $(PROGS:%=%$(STRIP_EXT))


local_build: libdir_chk
	$(MAKE) -C src OS_TYPE=`uname`

local_clean:
	$(MAKE) -C src OS_TYPE=`uname` clean
	$(RM) -r $(LIBDIR)
	$(RM) -r $(OBJDIR)
	$(RM) $(PROGS_NTV) $(PROGS_STP)

local_test: objdir_chk local_build $(MAINS) $(MAIN_OBJS)
	$(CC) -o $(OUTPUT_PREFIX)$(PROG)$(NATIVE_EXT) $(OBJDIR)/$(MAIN) $(MAIN_ROBJS) $(LDFLAGS)
	$(STRIP) $(OUTPUT_PREFIX)$(PROG)$(NATIVE_EXT) -o $(OUTPUT_PREFIX)$(PROG)$(STRIP_EXT)
	$(GLCROOT)/trial $(OUTPUT_PREFIX)$(PROG)$(NATIVE_EXT) 0x0FF7938A0FD5B43A 0x52D57E0A70008C42
	$(GLCROOT)/trial $(OUTPUT_PREFIX)$(PROG)$(STRIP_EXT) 0x0FF7938A0FD5B43A 0x52D57E0A70008C42

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
	@cp -r lib/* $(INSTALL_ROOT)/lib

package: pkg_lib_path pkg_codeconv pkg_dimz_dz1 pkg_dimz_gasn pkg_14827_asn pkg_14827_dz1 local_build pkg_asn1
	@cp $(ROOT)/include/*.h $(ROOT)/pkg_root/include;
	@cp $(ROOT)/lib/$(TARGET_TYPE)lib/*.a $(ROOT)/pkg_root/lib/$(TARGET_TYPE)lib;
	@cp $(ROOT)/asset/* $(ROOT)/pkg_root/test;

pkgclean:
	@rm -rf pkg_root;

pkg_lib_path:
	@if ! [ -d $(ROOT)/pkg_root/lib/$(TARGET_TYPE)lib ]; then \
		mkdir -p $(ROOT)/pkg_root/lib/$(TARGET_TYPE)lib; \
	fi
	@if ! [ -d $(ROOT)/pkg_root/include ]; then \
		mkdir -p $(ROOT)/pkg_root/include; \
	fi
	@if ! [ -d $(ROOT)/pkg_root/test ]; then \
		mkdir -p $(ROOT)/pkg_root/test; \
	fi
	@if ! [ -d $(ROOT)/pkg_root/ASN.1.GITSN.LIB ]; then \
		mkdir -p $(ROOT)/pkg_root/ASN.1.GITSN.LIB; \
	fi

pkg_codeconv: pkg_lib_path
	$(MAKE) -C $(ROOT)/../codeconv OS_TYPE=`uname`
	@cp -r $(ROOT)/../codeconv/lib/$(TARGET_TYPE)lib pkg_root/lib

DZ1_HDRS	 =	dz1.h\
				dz1_aatree.h\
				dz1_asn1.h\
				dz1_asn1_support.h\
				dz1_bin.h\
				dz1_bits.h\
				dz1_cleanup.h\
				dz1_codec.h\
				dz1_conf.h\
				dz1_elastic_buf.h\
				dz1_error.h\
				dz1_gasn_support.h\
				dz1_int.h\
				dz1_io_stream.h\
				dz1_malloc.h\
				dz1_mutex.h\
				dz1_real.h\
				dz1_shell.h\
				dz1_sock_addr.h\
				dz1_socket.h\
				dz1_socket_buf.h\
				dz1_socket_fifo.h\
				dz1_stdio.h\
				dz1_str.h\
				dz1_task.h\
				dz1_thread.h\
				dz1_thread_log.h\
				dz1_thread_stack.h\
				dz1_thread_status.h\
				dz1_thread_stdio.h\
				dz1_time.h\
				dz1_timeval.h\
				dz1_unix.h\
				libdz1_support.h

DZ1_LIBS	 = $(DZ1LIBs:%=lib%.a)

pkg_dimz_dz1: pkg_lib_path
	$(MAKE) -C $(ROOT)/../dimz/dz1 OS_TYPE=`uname`
	@for ccc in $(DZ1_HDRS); do \
		cp $(ROOT)/../dimz/dz1/include/$$ccc $(ROOT)/pkg_root/include;\
	done
	@for ccc in $(DZ1_LIBS); do \
		echo $$ccc; \
		cp $(ROOT)/../dimz/dz1/lib/$(TARGET_TYPE)lib/$$ccc $(ROOT)/pkg_root/lib/$(TARGET_TYPE)lib; \
	done

pkg_dimz_gasn: pkg_lib_path
	$(MAKE) -C $(ROOT)/../dimz/dz1_tools/dz1_gasn_support OS_TYPE=`uname`
	@cp $(ROOT)/../dimz/dz1_tools/dz1_gasn_support/include/*.h $(ROOT)/pkg_root/include;
	@cp $(ROOT)/../dimz/dz1_tools/dz1_gasn_support/lib/$(TARGET_TYPE)lib/*.a $(ROOT)/pkg_root/lib/$(TARGET_TYPE)lib;

pkg_14827_asn: pkg_lib_path
	$(MAKE) -C $(ROOT)/../Iso14827NewAsn OS_TYPE=`uname`
	@cp $(ROOT)/../Iso14827NewAsn/ISO14827*.h $(ROOT)/pkg_root/include;
	@cp $(ROOT)/../Iso14827NewAsn/lib/$(TARGET_TYPE)lib/*.a $(ROOT)/pkg_root/lib/$(TARGET_TYPE)lib;
	
pkg_14827_dz1: pkg_lib_path
	$(MAKE) -C $(ROOT)/../Iso14827dz1 OS_TYPE=`uname`
	@cp $(ROOT)/../Iso14827dz1/include/*.h $(ROOT)/pkg_root/include;
	@cp $(ROOT)/../Iso14827dz1/lib/$(TARGET_TYPE)lib/*.a $(ROOT)/pkg_root/lib/$(TARGET_TYPE)lib;

pkg_asn1:
	$(MAKE) -C $(ROOT)/../ASN.1.GITSN.LIB install INSTALL_DEST=../ItsIso14827/pkg_root/ASN.1.GITSN.LIB
