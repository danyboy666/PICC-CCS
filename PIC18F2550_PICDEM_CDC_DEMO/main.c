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
#EXPORT (FILE=.\rls\PIC18F2550_PICDEM_CDC_DEMO_v1_0.HEX)
//Bibliothèques utilisés
#include <main.h> //Header pour le programme.

//#include <.\lib\exemple.c>


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

//#define USB_CON_SENSE_PIN PIN_B2
//#define PIN_USB_SENSE USB_CON_SENSE_PIN
//#define USB_CABLE_IS_ATTACHED() input(PIN_USB_SENSE)
int1 usb_cdc_oldconnected=FALSE;
//Now a thing that is commonly 'missed', is that if your unit has it's own
//5v power, the connection sense pin is _required_ by the USB specs.
//Disconnection/reconnection will not be handled properly without it.

#include <stdlib.h>
#define __USB_PIC_PERIF__ 1
// Includes all USB code and interrupts, as well as the CDC API
#include <usb_cdc.h>

/*
// RS232 Buffer
#define  BUFFER_SIZE  32
char buffer[BUFFER_SIZE];
char next_in  = 0;
char next_out = 0;
char char_received = ' ';


#int_rda // Interrupt fires when the receive data available
void serial_isr()
{
int t;
buffer[next_in] = fgetc(ESP);
t = next_in;
next_in = (next_in + 1) % BUFFER_SIZE;
if(next_in == next_out)
 next_in = t; //buffer full!!
}
*/

// INT_TBE Interrupt fires when the transmit data empty
// RS232 Buffer
#define  BUFFER_SIZE  32
char buffer[BUFFER_SIZE];
char next_in  = 0;
char next_out = 0;
char char_received = ' ';

#int_rda
void serial_isr() {
   int t;

//   buffer[next_in]=getc();
   buffer[next_in]=fgetc(ESP);
   t=next_in;
   next_in=(next_in+1) % BUFFER_SIZE;
   if(next_in==next_out)
     next_in=t;           // Buffer full !!
}

#define bkbhit (next_in!=next_out)

BYTE bgetc() {
   BYTE c;

   while(!bkbhit) ;
   c=buffer[next_out];
   next_out=(next_out+1) % BUFFER_SIZE;
   return(c);
}
/*
void main(void)
{
//   enable_interrupts(int_rda);
//   enable_interrupts(global);
   setup_adc_ports(NO_ANALOGS);
   setup_comparator(NC_NC_NC_NC);
   usb_init_cs();
   usb_cdc_init();
   
   char c;
//   char buffer[16];
   do 
   {
      if (usb_attached())
      {
         usb_task();   
         if (kbhit()) 
         {
            c=fgetc(ESP);
            usb_cdc_putc(c);
         }
         if (usb_cdc_kbhit()) 
         {
//            c=usb_cdc_getc();
//            usb_get_string(buffer, 16);
            fputc(c);
         }
      }      
   } while (true);
}
   
*/

void main(void)
{
   enable_interrupts(int_rda);
   enable_interrupts(global);
   setup_adc_ports(NO_ANALOGS);
   setup_comparator(NC_NC_NC_NC);
   usb_init_cs();
   usb_cdc_init();
   
   char c;
//   char buffer[16];
   while (true) 
   {
      if (usb_attached())
      {
         usb_task();   
         delay_ms(500);
         if (bkbhit) char_received = bgetc();
         char_received = ' ';
      }      
   } while (true);
}
