include ../dz1build.mk

local_build: kerneld structd socketd utild taskd parserd streamd shelld termiod fsmd asn1d crcd cryptd

#config: chk_ssl_lib
#chk_ssl_lib:
#	@if [ "$(SSL_SDK_ROOT)" == "" ]; then\
	else \
	fi
kerneld:
	$(MAKE) -C kernel OS_TYPE=`uname`
structd:
	$(MAKE) -C struct OS_TYPE=`uname`
socketd:
	$(MAKE) -C socket OS_TYPE=`uname`
utild:
	$(MAKE) -C util OS_TYPE=`uname`
taskd:
	$(MAKE) -C task OS_TYPE=`uname`
parserd:
	$(MAKE) -C parser OS_TYPE=`uname`
shelld:
	$(MAKE) -C shell OS_TYPE=`uname`
streamd:
	$(MAKE) -C stream OS_TYPE=`uname`
termiod:
	$(MAKE) -C termio OS_TYPE=`uname`
fsmd:
	$(MAKE) -C fsm OS_TYPE=`uname`
asn1d:
	$(MAKE) -C asn1 OS_TYPE=`uname`
crcd:
	$(MAKE) -C crc OS_TYPE=`uname`
cryptd:
	$(MAKE) -C crypt OS_TYPE=`uname`
local_clean:
	$(MAKE) -C kernel OS_TYPE=`uname` clean
	$(MAKE) -C struct OS_TYPE=`uname` clean
	$(MAKE) -C socket OS_TYPE=`uname` clean
	$(MAKE) -C util OS_TYPE=`uname` clean
	$(MAKE) -C task OS_TYPE=`uname` clean
	$(MAKE) -C parser OS_TYPE=`uname` clean
	$(MAKE) -C shell OS_TYPE=`uname` clean
	$(MAKE) -C stream OS_TYPE=`uname` clean
	$(MAKE) -C termio OS_TYPE=`uname` clean
	$(MAKE) -C fsm OS_TYPE=`uname` clean
	$(MAKE) -C asn1 OS_TYPE=`uname` clean
	$(MAKE) -C crc OS_TYPE=`uname` clean
	$(MAKE) -C crypt OS_TYPE=`uname` clean
local_test:
	$(MAKE) -C kernel OS_TYPE=`uname` test
	$(MAKE) -C struct OS_TYPE=`uname` test
	$(MAKE) -C socket OS_TYPE=`uname` test
#	$(MAKE) -C util OS_TYPE=`uname` test
	$(MAKE) -C task OS_TYPE=`uname` test
	$(MAKE) -C parser OS_TYPE=`uname` test
	$(MAKE) -C shell OS_TYPE=`uname` test
#	$(MAKE) -C termio OS_TYPE=`uname` test
#	$(MAKE) -C fsm OS_TYPE=`uname` test
