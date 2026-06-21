CROSS_COMPILE	?= arm-linux-gnueabihf-
TARGET			?= int

CC				:= $(CROSS_COMPILE)gcc
LD				:= $(CROSS_COMPILE)ld
OBJCOPY			:= $(CROSS_COMPILE)objcopy
OBJDUMP			:= $(CROSS_COMPILE)objdump

INCUDIRS		:= 	imx6u \
					bsp/clk \
					bsp/led \
					bsp/delay \
					bsp/beep \
					bsp/key \
					bsp/gpio \
					bsp/int \
					bsp/exti \
					bsp/epit

SRCDIRS			:= 	project \
					bsp/clk \
					bsp/led \
					bsp/delay \
					bsp/beep \
					bsp/key \
					bsp/gpio \
					bsp/int \
					bsp/exti \
					bsp/epit

INCLUDE			:= $(patsubst %, -I %, $(INCUDIRS))

SFILES_S		:= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.S))
SFILES_s		:= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.s))
CFILES			:= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))

SOBJS_S			:= $(patsubst %.S, obj/%.o, $(notdir $(SFILES_S)))
SOBJS_s			:= $(patsubst %.s, obj/%.o, $(notdir $(SFILES_s)))
COBJS			:= $(patsubst %.c, obj/%.o, $(notdir $(CFILES)))

SOBJS			:= $(SOBJS_S) $(SOBJS_s)
OBJS			:= $(SOBJS) $(COBJS)

VPATH			:= $(SRCDIRS)

.PHONY: clean print

$(TARGET).bin : $(OBJS)
	$(LD) -Timx6u.lds -o $(TARGET).elf $^
	$(OBJCOPY) -O binary -S $(TARGET).elf $@
	$(OBJDUMP) -D -m arm $(TARGET).elf > $(TARGET).dis
	~/linux-alpha/tool/imxdownload_make_load -512m  $@
	dd if=/dev/zero of=sd.img bs=1M count=64
	dd if=load.imx of=sd.img bs=512 seek=2

$(SOBJS_S) : obj/%.o : %.S | obj
	$(CC) -Wall -nostdlib -c -O2 $(INCLUDE) -o $@ $<

$(SOBJS_s) : obj/%.o : %.s | obj
	$(CC) -Wall -nostdlib -c -O2 $(INCLUDE) -o $@ $<

$(COBJS) : obj/%.o : %.c | obj
	$(CC) -Wall -nostdlib -c -O2 $(INCLUDE) -o $@ $<

obj:
	mkdir -p obj

clean:
	rm -rf $(TARGET).elf $(TARGET).bin $(TARGET).dis obj

print:
	@echo INCLUDE = $(INCLUDE)
	@echo CFILES  = $(CFILES)
	@echo SFILES  = $(SFILES_S) $(SFILES_s)
	@echo OBJS    = $(OBJS)
