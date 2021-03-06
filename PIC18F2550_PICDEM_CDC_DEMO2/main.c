#include <18F2550.h>
#device adc=10
//#fuses HSPLL, NOWDT, PLL2, CPUDIV1, USBDIV, VREGEN, NOPROTECT, BORV42, NOPBADEN
#fuses HSPLL, NOWDT, PLL2, CPUDIV1, USBDIV, VREGEN, NOPROTECT, NOPBADEN
#FUSES BROWNOUT, PUT, STVREN, NODEBUG, NOLVP, NOWRT, NOWRTD, NOWRTB, NOWRTC, NOCPD, NOCPB, NOEBTR, NOEBTRB, NOXINST, NOMCLR
#use delay(clock=48000000)
//This assumes a 8MHz crystal. Chance 'PLLx' to suit your crystal.
//Can be 4,8, 12, 16, 20 or 24Mhz.
//Beyond this other changes are needed.....

#define USB_CON_SENSE_PIN PIN_B2
#define PIN_USB_SENSE USB_CON_SENSE_PIN
#define USB_CABLE_IS_ATTACHED() input(PIN_USB_SENSE)
int1 usb_cdc_oldconnected=FALSE;
//Now a thing that is commonly 'missed', is that if your unit has it's own
//5v power, the connection sense pin is _required_ by the USB specs.
//Disconnection/reconnection will not be handled properly without it.

#include <stdlib.h>
#define __USB_PIC_PERIF__ 1
// Includes all USB code and interrupts, as well as the CDC API
#include <usb_cdc.h>

void main(void)
{
   setup_adc_ports(NO_ANALOGS);
   setup_comparator(NC_NC_NC_NC);
   usb_init_cs();
   usb_cdc_init();
   
   while (true)
   {
      if (usb_attached())
      {
         usb_task();   
         if (usb_enumerated())
         {
            if (usb_cdc_carrier.dte_present)
            {
               if (usb_cdc_oldconnected==FALSE)
               {
                  printf(usb_cdc_putc,"Hello World\n\r");
                  usb_cdc_oldconnected=TRUE;
               }
               if (usb_cdc_kbhit())
               {
                  //use usb_cdc_getc here to read the character and do what
                  //you want
                  usb_cdc_putc(toupper(usb_cdc_getc()));
                  //as a demo, return the character converted to upper case
               }
   //            if (your_button_is_pressed())
   //            {
                  //Obviously you need to work out how this function is done...
    //              printf(usb_cdc_putc,"Button is pressed\n\r");
    //           }
             }
         }
      }
      else
      {
         usb_cdc_oldconnected=FALSE;
         usb_cdc_init(); //clear buffers if disconnected
      }
   }
}
