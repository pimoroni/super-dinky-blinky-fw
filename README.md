# Super Dinky Blinky Firmware

## Operation

With power applied to the 3V and GND terminals, the SDB will periodically turn the LED outputs on and off in a pattern. This pattern can be changed by pressing the dome switch. Power can be toggled by holding the dome switch for a couple of seconds.

The terminals are designed for a wide variety of connections. Copper tape, crocodile clips (alligator also supported), conductive thread, or even soldering. Connect the positive anode (+) of the LED to the LED terminal, and the cathode (−) to GND.

## Brains

The circuit is driven by the Nuvoton N76E003AQ20 MCU, a low-cost, 8-bit 8501-based microcontroller.

The N76E003 can be reprogrammed with an In-Circuit Programmer. While Nuvoton only officially supports the Keil and IAR compilers, you can find the source code to the SDB and a port of the BSP to the open source SDCC compiler here.

On the base of the board are headers for firmware deployment using the Nu-Link programmer: https://direct.nuvoton.com/en/nu-link 

The programming software is Windows-only.

N76E003 Datasheet: http://www.nuvoton.com/resource-files/DS_N76E003_EN_Rev1.08.pdf
