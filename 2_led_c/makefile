CC = arm-linux-gnueabihf-gcc
LD = arm-linux-gnueabihf-ld
OBJDUMP = arm-linux-gnueabihf-objdump
OBJCOPY = arm-linux-gnueabihf-objcopy
OBJS = start.o main.o

led.bin : $(OBJS)
	$(LD) -Timx6u.lds -o led.elf $^
	$(OBJCOPY) -O binary -S led.elf $@
	$(OBJDUMP) -D -m arm led.elf > led.dis

%.o : %.c
	$(CC) -Wall -nostdlib -c -O2 -o $@ $<

%.o : %.s
	$(CC) -Wall -nostdlib -c -O2 -o $@ $<
	
clean :
	rm -f *.o *.elf *.bin
