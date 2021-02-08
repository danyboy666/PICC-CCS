#include <18F2550.h>
#device PASS_STRINGS = IN_RAM
//Fuses
#device adc=10
#fuses HSPLL, NOWDT, PLL3, CPUDIV1, USBDIV, NOVREGEN, PUT, NOMCLR, NOLVP
#use delay(clock=48000000)
//R�server les 800 premi�res case m�moire pour le bootloader. (PICDEM)
#build(reset=0x800, interrupt=0x808) 
#org 0, 0x7ff { }




