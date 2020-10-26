///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************/
/*                                                                           */
/* Programme de thermostat interfacé avec un capteur de température          */
/* intelligent Dallas DS18S20, alarmes pour indiquer les temperatures trop   */
/* basses et trop élevées et déclanchement de plainte électrique.            */
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
#EXPORT (FILE=.\rls\DS18S20_v1_0.HEX)
//Bibliothèques utilisés
#include <main.h> //Header pour le programme.
#include <.\lib\DS18B20.c> //Mini driver pour le capteur.

void setup();
void display_temperature();

// global variable declaration
float temperature; //Variable flotante pour stocker les données provenant du capteur.

/////////////////////////// Main Program begin ///////////////////

void main()
   {  
    setup(); 
      while(TRUE) //Boucle infinie.
         {
            display_temperature();
         }
   } // while loop end
   
/////////////////////////// Main Program end /////////////////////

void setup()                     
   {  
    lcd_init(); //Initialisation de l'afficheur.
    lcd_gotoxy(1,1); //Mettre le curseur à la position.    
    lcd_send_byte(0,1); //Commande pour éffacer l'afficheur.   
   }
   
void display_temperature()   
   {          
      lcd_gotoxy(10,1); //Mettre le curseur à la position.
      temperature=ds1820_read(); //Stocker les données provenant du capteur.
      printf(lcd_putc,"%3.1f",temperature); //Afficher à l'écran.    
      lcd_putc(223); //Afficher à l'écran le symbole pour les degrés.
      lcd_putc("C");
   }
