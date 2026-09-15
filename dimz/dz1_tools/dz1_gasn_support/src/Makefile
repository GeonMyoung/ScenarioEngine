ROOT		= ..
include $(ROOT)/dz1_gasn_support.mk

EXCLUDESRC	= 
EXCLUDE		= $(EXCLUDESRC:%.c=%.o) $(MAINS)

#####################################################
###           Define Building Rules               ###  
#####################################################

local_build:lib

lib: objdir_chk $(OBJS) $(PLATFORM_OBJS)
	$(AR) rc $(LIBFILE) $(ROBJS) $(PLATFORM_OBJS)
	$(MV) $(LIBFILE) $(LIBDIR)

local_test:lib 

local_clean:
	$(RM) -r $(OBJDIR)
	$(RM) $(LIBDIR)/$(LIBFILE)

local_install:
