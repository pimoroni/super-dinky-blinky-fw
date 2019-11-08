SDCC_PATH = ~/Downloads/sdcc/sdcc-3.6.0/bin/

all:
	$(SDCC_PATH)sdcc -c Delay.c
	$(SDCC_PATH)sdcc -c Common.c

	#the chip has 18k of flash, but 4k can be allocated for boot rom -> only 14k = 14336 is allocated here.
	$(SDCC_PATH)sdcc blinky.c Common.rel Delay.rel --data-loc 0x20 --code-size 14336 --iram-size 128 --idata-loc 0x80 --xram-size 768

	mv blinky.ihx blinky.hex

clean:
	rm *.lst *.rel *.sym *.asm *.map *.mem *.rst *.lk



# Compiler arguments:
# --data-loc <Value> The start location of the internal ram data segment, the default value is 0x30
# --idata-loc <Value> The start location of the indirectly addressable internal ram, default value is 0x80
# --stack-loc <Value> The initial value of the stack pointer. The default value of the stack pointer is 0x07 
# if only register bank 0 is used, if other register banks are used then the stack pointer is initialized to the location above the highest register bank used. 
# --iram-size <Value> Causes the linker to check if the interal ram usage is within limits of the given value.
# DEFAULT --xram-loc <Value> The start location of the external ram, default value is 0
# DEFAULT --code-loc <Value> The start location of the code segment , default value 0

