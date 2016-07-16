# DC801_DC24PartyBadge
Party badge and BLE hardware board

# Hardware
Board design is in Eagle

Board consists of:

Rigado BMD-200 Bluetooth low energy based on a Nordic nRF51822
 - 16MHz ARM® Cortex™ M0 CPU, 256kB of flash memory, 32kB RAM
 - https://www.rigado.com/product/bmd-200/

2 RGB LEDs
10 red LEDs addressable in pairs
Single button
A MCP73831 LiPo battery charger
Spare pins
JTAG interface
Micro USB - for charging only
Kickass silkscreen

# Software
Environment is the nRFgo Studio and Keil
need a segger j-link programmer
custom_board.h goes in the C:\Keil_v5\ARM\Pack\NordicSemiconductor\nRF_Examples\11.0.0-2.alpha\bsp
Uses the soft device s130v1 firmware

Device is programmed with the softdevice first, then the application is loaded
