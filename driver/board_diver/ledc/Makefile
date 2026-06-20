objs = start.o main.o

ledc.bin : $(objs)
	arm-linux-gnueabihf-ld -T imx6u.lds $^ -o ledc.elf
	arm-linux-gnueabihf-objcopy -O binary ledc.elf $@
	arm-linux-gnueabihf-objdump -D -m arm ledc.elf > ledc.dis
	~/linux-alpha/tool/imxdownload_make_load -512m  $@
	dd if=/dev/zero of=sd.img bs=1M count=64
	dd if=load.imx of=sd.img bs=512 seek=2

%.o : %.c
	arm-linux-gnueabihf-gcc -Wall -nostdlib -c  -O2 -o $@ $<

%.o : %.s
	arm-linux-gnueabihf-gcc -Wall -nostdlib -c  -O2 -o $@ $<

clean:
	rm -rf *.o ledc.bin ledc.elf ledc.dis sd.img load.im