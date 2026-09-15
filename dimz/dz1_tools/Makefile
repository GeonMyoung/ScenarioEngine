BUILD_LIST	 =	dz1_bmpd \
				dz1_code_gend \
				dz1_gifd \
				dz1_daemond \
				dz1_inetd \
				dz1_jsond \
				dz1_logicsd \
				dz1_lzwd \
				dz1_parser_utild \
				dz1_riffd \
				dz1_serial_sockd \
				dz1_sock_utild \
				dz1_storaged \
				dz1_syslogd \
				dz1_task_gend \
				dz1_tdc_infod \
				dz1_tdcd \
				dz1_text2arrayd \
				dz1_tedecd

ifneq (,$(ASN1GITSN))
BUILD_LIST	+= dz1_gasn_supportd
endif

all: local_build

asn1tool_build:	local_build dz1_gasn_supportd

# dz1_bin2src				: binary data to source code					- TBD
# dz1_bmp					: Bitmap Image File Helper						- O
# dz1_code_gen				: Typical Code Pattern Generator				- O
# dz1_code_gen_gui			: GUI for Windows of dz1_code_gen				- Windows Only
# dz1_daemon				: Daemonizer									- O
# dz1_gasn_support			: GITSN ASN.1 Library Support					- O(need ASN.1 Library)
# dz1_gif					: Graphic Interface File Helper					- O
# dz1_inet					: telnet & ftp Helper							- O
# dz1_json					: JSON codec									- O
# dz1_logics				: Logical Expression Computer					- O
# dz1_lzw					: LZW Compression Algorithm						- O
# dz1_meta_tag				: Data Describer Database						- TBD
# dz1_mfc					: Windows MFC Control Helper					- Windows Only
# dz1_parser_util			: Additional utility functions for dz1_parser	- O
# dz1_riff					: RIFF Source File Helper						- O
# dz1_serial_sock			: Socket wrapper for Serail/UART IO				- O
# dz1_sock_util				: Additional Utility functions for Dz1*Socket	- O
# dz1_storage				: File System over File							- O
# dz1_syslog				: log message writter							- O
# dz1_task_gen				: Project Initializer							- O
# dz1_task_gen_gui			: GUI foe Windows of dz1_task_gen				- Windows Only
# dz1_tcp_serial_client		: Serial over TCP Client						- ?
# dz1_tcp_serial_msg		: Messages of Serial over TCP					- ?
# dz1_tcp_serial_server		: Serial over TCP Server						- ?
# dz1_tdc					: Type Describer for C Script Compiler			- O
# dz1_tdc_info				: Database Module for dz1_tdc					- O
# dz1_tdq					: Type Describer for Query						- Windows Only for now
# dz1_text2array			: Text data to source code						- O
# dz1_text2array_gui		: GUI for Windows of dz1_text2array				- Windows Only
# dz1_todec					: CODEC generator from tdc						- O
# dz1_vfs					: ?												- TBD

local_build:	$(BUILD_LIST)
dz1_bmpd:
	$(MAKE) -C dz1_bmp OS_TYPE=`uname`
dz1_code_gend:
	$(MAKE) -C dz1_code_gen OS_TYPE=`uname`
dz1_gasn_supportd:
	$(MAKE) -C dz1_gasn_support OS_TYPE=`uname`
dz1_gifd:
	$(MAKE) -C dz1_gif OS_TYPE=`uname`
dz1_daemond:
	$(MAKE) -C dz1_daemon OS_TYPE=`uname`
dz1_inetd:
	$(MAKE) -C dz1_inet OS_TYPE=`uname`
dz1_jsond:
	$(MAKE) -C dz1_json OS_TYPE=`uname`
dz1_logicsd:
	$(MAKE) -C dz1_logics OS_TYPE=`uname`
dz1_lzwd:
	$(MAKE) -C dz1_lzw OS_TYPE=`uname`
dz1_parser_utild :
	$(MAKE) -C dz1_parser_util OS_TYPE=`uname`
dz1_riffd:
	$(MAKE) -C dz1_riff OS_TYPE=`uname`
dz1_serial_sockd:
	$(MAKE) -C dz1_serial_sock OS_TYPE=`uname`
dz1_sock_utild:
	$(MAKE) -C dz1_sock_util OS_TYPE=`uname`
dz1_storaged:
	$(MAKE) -C dz1_storage OS_TYPE=`uname`
dz1_syslogd:
	$(MAKE) -C dz1_syslog OS_TYPE=`uname`
dz1_task_gend:
	$(MAKE) -C dz1_task_gen OS_TYPE=`uname`
dz1_tdc_infod:
	$(MAKE) -C dz1_tdc_info OS_TYPE=`uname`
dz1_tdcd:
	$(MAKE) -C dz1_tdc OS_TYPE=`uname`
dz1_text2arrayd:
	$(MAKE) -C dz1_text2array OS_TYPE=`uname`
dz1_tedecd:
	$(MAKE) -C dz1_todec OS_TYPE=`uname`
clean:
	$(MAKE) -C dz1_bmp OS_TYPE=`uname` clean
	$(MAKE) -C dz1_code_gen OS_TYPE=`uname` clean
	$(MAKE) -C dz1_gasn_support OS_TYPE=`uname` clean
	$(MAKE) -C dz1_gif OS_TYPE=`uname` clean
	$(MAKE) -C dz1_daemon OS_TYPE=`uname` clean
	$(MAKE) -C dz1_inet OS_TYPE=`uname` clean
	$(MAKE) -C dz1_json OS_TYPE=`uname` clean
	$(MAKE) -C dz1_logics OS_TYPE=`uname` clean
	$(MAKE) -C dz1_lzw OS_TYPE=`uname` clean
	$(MAKE) -C dz1_parser_util OS_TYPE=`uname` clean
	$(MAKE) -C dz1_riff OS_TYPE=`uname` clean
	$(MAKE) -C dz1_serial_sock OS_TYPE=`uname` clean
	$(MAKE) -C dz1_sock_util OS_TYPE=`uname` clean
	$(MAKE) -C dz1_storage OS_TYPE=`uname` clean
	$(MAKE) -C dz1_syslog OS_TYPE=`uname` clean
	$(MAKE) -C dz1_task_gen OS_TYPE=`uname` clean
	$(MAKE) -C dz1_tdc_info OS_TYPE=`uname` clean
	$(MAKE) -C dz1_tdc OS_TYPE=`uname` clean
	$(MAKE) -C dz1_text2array OS_TYPE=`uname` clean
	$(MAKE) -C dz1_todec OS_TYPE=`uname` clean
	rm -f $(CROSS_COMPILE)tdc
local_test:
	$(MAKE) -C dz1_gasn_support OS_TYPE=`uname` test
	$(MAKE) -C dz1_syslog OS_TYPE=`uname` test
	$(MAKE) -C dz1_inet OS_TYPE=`uname` test
