OBJS := start.o main.o
LD := arm-linux-gnueabihf-ld
CC := arm-linux-gnueabihf-gcc
OBJDUMP := arm-linux-gnueabihf-objdump
OBJCOPY := arm-linux-gnueabihf-objcopy

led.bin : $(OBJS)
	$(LD) -Timx6u.lds -o led.elf $^
	$(OBJCOPY) -O binary -S led.elf $@
	$(OBJDUMP) -D -m arm led.elf > led.dis

%.o : %.c
	$(CC) -Wall -nostdlib -c  -o $@ $<

%.o : %.s
	$(CC) -Wall -nostdlib -c  -o $@ $<

clean:
	rm -f *.o *.bin *.elf *.dis
