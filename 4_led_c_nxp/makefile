CROSS_COMPLIE ?= arm-linux-gnueabihf-
NAME					?= led

CC 						:= $(CROSS_COMPLIE)gcc
LD						:= $(CROSS_COMPLIE)ld
OBJCOPY				:= $(CROSS_COMPLIE)objcopy
OBJDUMP				:= $(CROSS_COMPLIE)objdump

OBJS := start.o main.o

$(NAME).bin : $(OBJS)
	$(LD) -Timx6ull.lds -o $(NAME).elf $^
	$(OBJCOPY) -O binary -S $(NAME).elf $@
	$(OBJDUMP) -D -m arm $(NAME).elf > $(NAME).dis

%.o : %.c
	$(CC) -Wall -nostdlib -c -O2 -o $@ $<

%.o : %.s
	$(CC) -Wall -nostdlib -c -O2 -o $@ $<

clean :
	rm -rf *.o $(NAME).elf $(NAME).bin $(NAME).dis
