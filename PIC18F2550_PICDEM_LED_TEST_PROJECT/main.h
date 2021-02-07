#include <18F2550.h>

//Fuses
#fuses HSPLL,NOWDT,NOPROTECT,NODEBUG,NOBROWNOUT,USBDIV,PLL5,CPUDIV1,VREGEN,PUT,NOMCLR,NOLVP
#use delay(clock=48000000)
//Réserver les 800 premières case mémoire pour le bootloader. (PICDEM)
#build(reset=0x800, interrupt=0x808) 
#org 0, 0x7ff { }

//#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)
//#use i2c(Master,Fast,sda=PIN_B0,scl=PIN_B1,force_hw)




