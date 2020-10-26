///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************/
/*                                                                           */
/* Programme de thermostat interfac� avec un capteur de temp�rature          */
/* intelligent Dallas DS18S20, alarmes pour indiquer les temperatures trop   */
/* basses et trop �lev�es et d�clanchement de plainte �lectrique.            */
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
//Biblioth�ques utilis�s
#include <main.h> //Header pour le programme.
#include <.\lib\DS18B20.c> //Mini driver pour le capteur.

void setup();
void display_temperature();

// global variable declaration
float temperature; //Variable flotante pour stocker les donn�es provenant du capteur.

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
    lcd_gotoxy(1,1); //Mettre le curseur � la position.    
    lcd_send_byte(0,1); //Commande pour �ffacer l'afficheur.   
   }
   
void display_temperature()   
   {          
      lcd_gotoxy(10,1); //Mettre le curseur � la position.
      temperature=ds1820_read(); //Stocker les donn�es provenant du capteur.
      printf(lcd_putc,"%3.1f",temperature); //Afficher � l'�cran.    
      lcd_putc(223); //Afficher � l'�cran le symbole pour les degr�s.
      lcd_putc("C");
   }
