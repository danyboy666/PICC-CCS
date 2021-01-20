///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************/
/*                                                                           */
/* This code is heavily based on PIC CCS ex.serial.c and ex.serial2.c.       */
/*                                                                           */
/* The pic will put data coming from the rs_232 stream (ESP)                 */
/* in usb_cdc_putc() and vice-versa whenever usb_cdc_kbhit() has data it     */
/* will be dumped in the rs_232 stream (ESP) via fputc().                    */
/*                                                                             */
/* Copyright Dany Ferron                                                     */
/*****************************************************************************/
/*                                                                           */ 
/*                                                                           */
/*                                                                           */
/* le 20 janvier 2021                                                        */
/*                                                                           */
/*****************************************************************************/
///////////////////////////////////////////////////////////////////////////////

// compiled with PCW CCS v 4.104
#include <main.h> //Header file for this program.

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
