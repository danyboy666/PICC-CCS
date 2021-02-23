///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************/
/*                                                                           */
/* This code is heavily based on PIC CCS ex.serial.c and ex.serial2.c.       */
/*                                                                           */
/* The pic will put data coming from the rs_232 stream (ESP)                 */
/* in usb_cdc_putc() and vice-versa whenever usb_cdc_kbhit() has data it     */
/* will be dumped in the rs_232 stream (ESP) via fputc().                    */
/*                                                                           */
/* 2021-02-22 - Added USB connection sense pin                               */
/* Copyright Dany Ferron                                                     */
/*****************************************************************************/
/*                                                                           */ 
/*                                                                           */
/*                                                                           */
/* le 22 février 2021                                                        */
/*                                                                           */
/*****************************************************************************/
///////////////////////////////////////////////////////////////////////////////

// compiled with PCW CCS v 4.104
#include <main.h> //Header file for this program.


int1 usb_cdc_oldconnected=FALSE;

void setup();


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
  //             if (your_button_is_pressed())
  //             {
                  //Obviously you need to work out how this function is done...
   //               printf(usb_cdc_putc,"Button is pressed\n\r");
   //            }
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

