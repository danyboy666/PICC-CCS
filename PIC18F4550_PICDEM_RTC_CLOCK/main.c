///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************/
/*                                                                           */
/* RTC Clock demo based on Francois-Joseph Hug RTC clock driver              */
/*                                                                           */ 
/* Copyright Dany Ferron                                                     */
/*****************************************************************************/
/*                                                                           */ 
/*                                                                           */
/*                                                                           */
/* le 25 octobre 2020                                                        */
/*                                                                           */
/*****************************************************************************/
///////////////////////////////////////////////////////////////////////////////

// compiled with PCW CCS v 4.104
// PIDCDEM hex output note: prepend :020000040000FA for PIDCDEM software
#EXPORT (FILE=.\rls\RTC_CLOCK_v1_0.HEX)

#include <main.h> // Header
#include <.\lib\RTC_Clock.c> // DS1307 driver

void setup();
void get_time();
void get_date();
void display_time();

/////////////////////////// Main program begin ///////////////////////////////

void main()
   {  
    setup(); 
      while(TRUE) //Boucle infinie.
      {
        display_time();
      } // End while loop
     
} //Fin du programme principal.

void setup()                     
   {    
    lcd_init(); //Initialisation de l'afficheur.
    lcd_gotoxy(1,1); //Mettre le curseur à la position.    
    init_I2C_Clock(); // Initialisation du RTC.
                      // Set time and date:
                      // hh,mm,ss,DD,MM,YY,WD
    lcd_send_byte(0,1); //Commande pour éffacer l'afficheur.
    set_I2C_Clock(0x23,0x56,0x50,0x25,0x10,0x20,0x19);
    get_I2C_Clock();// Reads date and time
   }
   
void display_time()
{
   lcd_gotoxy(1, 1);                
   printf(lcd_putc, "%x:%x:%x", rtc_value.hour, rtc_value.minute, rtc_value.second);
   lcd_gotoxy(1, 2);            
   
     switch(rtc_value.weekday)
      {
         // process weekday and display it
         case 1:printf(lcd_putc, "Dim-");break;
         case 2:printf(lcd_putc, "Lun-");break;
         case 3:printf(lcd_putc, "Mar-");break;
         case 4:printf(lcd_putc, "Mer-");break;
         case 5:printf(lcd_putc, "Jeu-");break;
         case 6:printf(lcd_putc, "Ven-");break;
         case 7:printf(lcd_putc, "Sam-");break;
      }
    printf(lcd_putc, "%x-%x-%x", rtc_value.day, rtc_value.month, rtc_value.year);
}
   
   

