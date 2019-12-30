CROSS_COMPLIE ?= arm-linux-gnueabihf-
TARGET				?= printf

CC 						:= $(CROSS_COMPLIE)gcc
LD						:= $(CROSS_COMPLIE)ld
OBJCOPY				:= $(CROSS_COMPLIE)objcopy
OBJDUMP				:= $(CROSS_COMPLIE)objdump

LIBPATH				:= -lgcc -L /usr/local/arm/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/lib/gcc/arm-linux-gnueabihf/4.9.4

INCDIRS				:= imx6u \
								 bsp/clk \
								 bsp/led \
								 bsp/beep \
								 bsp/delay\
								 bsp/gpio\
								 bsp/key\
								 bsp/exti\
								 bsp/epit\
								 bsp/key_filter\
								 bsp/int \
								 bsp/uart\
								 stdio/include

SRCDIRS				:= project\
								 bsp/clk \
								 bsp/led \
								 bsp/beep\
								 bsp/delay\
								 bsp/gpio\
								 bsp/key\
								 bsp/exti\
								 bsp/epit\
								 bsp/key_filter\
								 bsp/int \
								 bsp/uart\
								 stdio/lib

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
	$(LD) -Timx6ull.lds -o $(TARGET).elf $^ $(LIBPATH)
	$(OBJCOPY) -O binary -S $(TARGET).elf $@
	$(OBJDUMP) -D -m arm $(TARGET).elf > $(TARGET).dis

$(SOBJS) : obj/%.o : %.s
	$(CC) -Wall -nostdlib -fno-builtin -c -O2 $(INCLUDE) -o $@ $<

$(COBJS) : obj/%.o : %.c
	$(CC) -Wall -Wa,-mimplicit-it=thumb -nostdlib -fno-builtin -c -O2 $(INCLUDE) -o $@ $<

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
