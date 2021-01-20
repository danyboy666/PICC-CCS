///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************/
/*                                                                           */
/*                                                                           */ 
/* Copyright Dany Ferron                                                     */
/*****************************************************************************/
/*                                                                           */ 
/*                                                                           */
/*                                                                           */
/* le 21 décembre 2020                                                        */
/*                                                                           */
/*****************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#include <18F2550.h>
// compiled with PCW CCS v 4.104
// PIDCDEM hex output note: prepend :020000040000FA for PIDCDEM software
#EXPORT (FILE=.\rls\PIC18F2550_PICDEM_USB_UART_BRIDGE_v1_0.HEX)
//Bibliothèques utilisés
#include <main.h> //Header pour le programme.

//#include <.\lib\example.c>


#device adc=10
#fuses HSPLL, NOWDT, PLL3, CPUDIV1, USBDIV, NOVREGEN, PUT, NOMCLR, NOLVP
//#FUSES BROWNOUT, PUT, STVREN, NODEBUG, NOLVP, NOWRT, NOWRTD, NOWRTB, NOWRTC, NOCPD, NOCPB, NOEBTR, NOEBTRB, NOXINST
#use delay(clock=48000000)
//#use rs232(baud=115200,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8,stream=ESP,errors)
#use rs232(uart1, baud=115200, parity=N, bits=8, stream=ESP,errors)
//This assumes a 8MHz crystal. Chance 'PLLx' to suit your crystal.
//Can be 4,8, 12, 16, 20 or 24Mhz.
//Beyond this other changes are needed.....

//bootloader space
#build(reset=0x800, interrupt=0x808) 
#org 0, 0x7ff { }

#include <stdlib.h>

// Includes all USB code and interrupts, as well as the CDC API
#include <usb_cdc.h>

void main(void)
{
   setup_adc_ports(NO_ANALOGS);
   setup_comparator(NC_NC_NC_NC);
   usb_init_cs();
   usb_cdc_init();
   
   char c;
   
    while (true)
      {
         usb_task();   
         if (kbhit()) 
         {
            
            c=fgetc(ESP);
            usb_cdc_putc(c);
         }
         if (usb_cdc_kbhit()) // The same as kbhit(), returns TRUE if there is 1 or more character in the receive buffer.
         {
            c=usb_cdc_getc();
            fputc(c);
         }
      }      
}
