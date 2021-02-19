#include <18F2550.h>
#device PASS_STRINGS = IN_RAM
//Fuses
#device adc=10
#fuses HSPLL, NOWDT, PLL3, CPUDIV1, USBDIV, NOVREGEN, PUT, NOMCLR, NOLVP
#use delay(clock=48000000)
//Réserver les 800 premières case mémoire pour le bootloader. (PICDEM)
#build(reset=0x800, interrupt=0x808) 
#org 0, 0x7ff { }

// setup rs232
#use rs232(uart1, baud=115200, parity=N, bits=8, stream=ESP, errors)

//include some libraries
#include <stdlib.h>

// PIC CCS firmware not provided in this code you need to copy them from the driver folder if this is not compiling.
// Includes all USB code and interrupts, as well as the CDC API
//#include <usb_cdc.h>

