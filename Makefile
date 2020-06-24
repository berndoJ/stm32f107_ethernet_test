## MAKEFILE

FW_NAME        = stm32f107_ethernet_test

Q              = @

BINDIR         = ./bin
LIBDIR_OPENCM3 = ./lib/libopencm3
LIBDIR_LWIP    = ./lib/liblwip

DEFS		+= -DSTM32F1

INC          = -I $(LIBDIR_OPENCM3)/include
INC         += -I $(LIBDIR_LWIP)/include
INC         += -I ./include

LIBDIRS      = -L $(LIBDIR_OPENCM3)
LIBDIRS     += -L $(LIBDIR_LWIP)

SOURCEDIR    = ./source
OBJS         = $(SOURCEDIR)/main.o
OBJS        += $(SOURCEDIR)/gpio.o
OBJS        += $(SOURCEDIR)/uart.o
OBJS        += $(SOURCEDIR)/tick.o
OBJS        += $(SOURCEDIR)/syscalls.o
OBJS        += $(SOURCEDIR)/ethmac.o


CFLAGS       = -Os -ggdb3
CPPFLAGS     = -MD $(DEFS) $(INC)
LDFLAGS      = -static -nostartfiles $(LIBDIRS)
LDLIBS       = -Wl,--start-group -lc -lgcc -lnosys -lopencm3_stm32f1 -llwiparm32 -Wl,--end-group
LDSCRIPT     = ./ld/stm32f103xe.ld
FP_FLAGS	?= -msoft-float
ARCH_FLAGS	 = -mthumb -mcpu=cortex-m3 $(FP_FLAGS) -mfix-cortex-m3-ldrd

include mk/gcc-config.mk

.PHONY: all clean rebuild rebuild-flash flash size __endsplash
.PRECIOUS: %.o

all: $(BINDIR) $(BINDIR)/$(FW_NAME).elf $(BINDIR)/$(FW_NAME).hex size __endsplash

clean:
	$(Q)find $(SOURCEDIR) -name "*.o" -type f -delete
	$(Q)find $(SOURCEDIR) -name "*.d" -type f -delete
	$(Q)find $(BINDIR) -name "*.elf" -type f -delete
	$(Q)find $(BINDIR) -name "*.hex" -type f -delete
	$(Q)find $(BINDIR) -name "*.bin" -type f -delete
	$(Q)find $(BINDIR) -name "*.srec" -type f -delete
	$(Q)find $(BINDIR) -name "*.list" -type f -delete

rebuild: clean all

size:
	$(Q)printf "\n  SIZE:\n"
	$(Q)$(SIZE) $(BINDIR)/$(FW_NAME).elf

__endsplash:
	$(Q)printf "\n\033[1;32m  --[ BUILD FINISHED ]--  \033[0m\n"

rebuild-flash: clean flash

flash: all
	$(Q)printf "\n  FLASH   $(BINDIR)/$(FW_NAME).hex\n\n"
	$(Q)st-flash --format ihex write $(BINDIR)/$(FW_NAME).hex
	$(Q)printf "\n \033[1;35m --[ FLASH COMPLETE ]--  \033[0m\n"

$(SOURCEDIR):
	$(Q)printf "  MKDIR   $(SOURCEDIR)\n"
	$(Q)mkdir -p $(SOURCEDIR)

$(BINDIR):
	$(Q)printf "  MKDIR   $(BINDIR)\n"
	$(Q)mkdir -p $(BINDIR)

include mk/gcc-rules.mk