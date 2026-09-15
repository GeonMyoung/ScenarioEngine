include ../dz1build.mk

local_build:  kerneld socketd structd taskd Dz1TcpCallbackMsgd Dz1TcpCallbackClientd Dz1TcpCallbackServerd

kerneld:
	$(MAKE) -C kernel OS_TYPE=`uname`
structd:
	$(MAKE) -C struct OS_TYPE=`uname`
socketd:
	$(MAKE) -C socket OS_TYPE=`uname`
taskd:
	$(MAKE) -C task OS_TYPE=`uname`
parserd:
	$(MAKE) -C parser OS_TYPE=`uname`
shelld:
	$(MAKE) -C shell OS_TYPE=`uname`
termiod:
	$(MAKE) -C termio OS_TYPE=`uname`
fsmd:
	$(MAKE) -C fsm OS_TYPE=`uname`
asn1d:
	$(MAKE) -C asn1 OS_TYPE=`uname`
crcd:
	$(MAKE) -C crc OS_TYPE=`uname`
Dz1TcpCallbackMsgd:
	$(MAKE) -C Dz1TcpCallbackMsg OS_TYPE=`uname`
Dz1TcpCallbackClientd:
	$(MAKE) -C Dz1TcpCallbackClient OS_TYPE=`uname`
Dz1TcpCallbackServerd:
	$(MAKE) -C Dz1TcpCallbackServer OS_TYPE=`uname`
local_clean:
	$(MAKE) -C kernel OS_TYPE=`uname` clean
	$(MAKE) -C struct OS_TYPE=`uname` clean
	$(MAKE) -C socket OS_TYPE=`uname` clean
#	$(MAKE) -C util OS_TYPE=`uname` clean
	$(MAKE) -C task OS_TYPE=`uname` clean
#	$(MAKE) -C parser OS_TYPE=`uname` clean
#	$(MAKE) -C shell OS_TYPE=`uname` clean
#	$(MAKE) -C termio OS_TYPE=`uname` clean
#	$(MAKE) -C fsm OS_TYPE=`uname` clean
	$(MAKE) -C Dz1TcpCallbackMsg OS_TYPE=`uname` clean
	$(MAKE) -C Dz1TcpCallbackClient OS_TYPE=`uname` clean
	$(MAKE) -C Dz1TcpCallbackServer OS_TYPE=`uname` clean
local_test:
