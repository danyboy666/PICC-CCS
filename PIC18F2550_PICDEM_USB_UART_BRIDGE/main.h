/* main.h */

#include <18F2550.h> // Include pic device header file

#device adc=10
#fuses HSPLL, NOWDT, PLL3, CPUDIV1, USBDIV, NOVREGEN, PUT, NOMCLR, NOLVP // 12Mhz resonator
#use delay(clock=48000000)

// PIDCDEM hex output note: prepend :020000040000FA for PIDCDEM software
#EXPORT (FILE=.\rls\PIC18F2550_PICDEM_USB_UART_BRIDGE_v1_0.HEX)

// setup rs232
#use rs232(uart1, baud=115200, parity=N, bits=8, stream=ESP,errors)

//bootloader space for PICDEM FS USB. Comment this is you're flashing directly.
#build(reset=0x800, interrupt=0x808) 
#org 0, 0x7ff { }

//include some libraries
#include <stdlib.h>

// PIC CCS firmware not provided in this code you need to copy them from the driver folder if this is not compiling.
// Includes all USB code and interrupts, as well as the CDC API
#include <usb_cdc.h>



