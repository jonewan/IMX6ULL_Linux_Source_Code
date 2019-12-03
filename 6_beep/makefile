CROSS_COMPLIE ?= arm-linux-gnueabihf-
TARGET				?= beep

CC 						:= $(CROSS_COMPLIE)gcc
LD						:= $(CROSS_COMPLIE)ld
OBJCOPY				:= $(CROSS_COMPLIE)objcopy
OBJDUMP				:= $(CROSS_COMPLIE)objdump

INCDIRS				:= imx6u \
								 bsp/clk \
								 bsp/led \
								 bsp/beep \
								 bsp/delay
SRCDIRS				:= project\
								 bsp/clk \
								 bsp/led \
								 bsp/beep\
								 bsp/delay
INCLUDE				:= $(patsubst %, -I %, $(INCDIRS))
SFILES				:= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.s))
CFILES				:= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))

SFILENODIR		:= $(notdir $(SFILES))
CFILENODIR		:= $(notdir $(CFILES))

SOBJS					:= $(patsubst %, obj/%, $(SFILENODIR:.s=.o))
COBJS					:= $(patsubst %, obj/%, $(CFILENODIR:.c=.o))
OBJS 					:= $(SOBJS)$(COBJS)

VPATH					:= $(SRCDIRS)

$(TARGET).bin : $(OBJS)
	$(LD) -Timx6ull.lds -o $(TARGET).elf $^
	$(OBJCOPY) -O binary -S $(TARGET).elf $@
	$(OBJDUMP) -D -m arm $(TARGET).elf > $(TARGET).dis

$(SOBJS) : obj/%.o : %.s
	$(CC) -Wall -nostdlib -c -O2 $(INCLUDE) -o $@ $<

$(COBJS) : obj/%.o : %.c
	$(CC) -Wall -nostdlib -c -O2 $(INCLUDE) -o $@ $<

print:
	@echo INCDIRS = $(INCDIRS)
	@echo INCLUDE = $(INCLUDE)
	@echo SFILES = $(SFILES)
	@echo CFILES = $(CFILES)
	@echo SFILENODIR = $(SFILENODIR)
	@echo CFILENODIR = $(CFILENODIR)
	@echo SOBJS = $(SOBJS)
	@echo COBJS = $(COBJS)
	@echo OBJS = $(OBJS)

.PHONY:clean

clean :
	rm -rf $(TARGET).elf $(TARGET).bin $(TARGET).dis $(OBJS)
