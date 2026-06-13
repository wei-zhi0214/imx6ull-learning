led.bin : led.s
	arm-linux-gnueabihf-gcc -g -c led.s -o led.o
	arm-linux-gnueabihf-ld -Ttext 0x87800000 led.o -o led.elf
	arm-linux-gnueabihf-objcopy -O binary -S -g led.elf led.bin
	arm-linux-gnueabihf-objdump -D led.elf > led.dis
	~/linux-alpha/tool/imxdownload_make_load -512m led.bin
	dd if=/dev/zero of=sd.img bs=1M count=64
	dd if=load.imx of=sd.img bs=512 seek=2
clean:
	rm -rf *.o led.bin led.elf led.dis load.imx sd.img

