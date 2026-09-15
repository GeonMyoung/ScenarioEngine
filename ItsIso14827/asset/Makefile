ROOT	= .
include $(ROOT)/build.mk

MAIN_OBJS	 = generator.o
MAIN_ROBJS	 = $(MAIN_OBJS:%.o=$(OBJDIR)/%.o)

SUB_LDFLAGS	 = $(SHELL_LIBS) -l$(LIBNAME)

MAIN		 = ItsIso14827Test.o
MAINS		+= $(MAIN)

PROG		 = ItsIso14827Test
PROGS		+= $(PROG)

PROGS_NTV	 = $(PROGS:%=%$(NATIVE_EXT))
PROGS_STP	 = $(PROGS:%=%$(STRIP_EXT))

local_clean:
	$(RM) -r $(OBJDIR)
	$(RM) $(PROGS_NTV) $(PROGS_STP)

local_build: objdir_chk $(MAINS) $(MAIN_OBJS)
	$(CC) -o $(PROG)$(NATIVE_EXT) $(OBJDIR)/$(MAIN) $(MAIN_ROBJS) $(LDFLAGS)
	$(STRIP) $(PROG)$(NATIVE_EXT) -o $(PROG)$(STRIP_EXT)
