ROOT		= ..
include $(ROOT)/dz1_json.mk

EXCLUDESRC	= 
EXCLUDE		= $(EXCLUDESRC:%.c=%.o) $(MAINS)

#####################################################
###           Define Building Rules               ###  
#####################################################

local_build:objdir_chk libdir_chk lib

lib: $(OBJS) $(PLATFORM_OBJS)
	$(AR) rc $(LIBFILE) $(ROBJS) $(PLATFORM_OBJS)
	$(MV) $(LIBFILE) $(LIBDIR)

local_test:lib

local_clean:
	$(RM) $(ROBJS) $(PLATFORM_OBJS) $(MAINS) $(STRIPPED_PROGS) $(NATIVED_PROGS)
	$(RM) -r $(OBJDIR)
	$(RM) $(LIBDIR)/$(LIBFILE)

local_install:
