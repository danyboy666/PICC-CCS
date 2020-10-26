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
#EXPORT (FILE=.\rls\NEW_PROJECT_v1_0.HEX)
//Bibliothèques utilisés
#include <main.h> //Header pour le programme.

#include <.\lib\exemple.c>

void setup();

/////////////////////////// Main program begin ///////////////////////////////

void main()
   {  
    setup(); 
      while(TRUE) //Boucle infinie.
      {
        display_temperature();
      } // En while loop
     
} //Fin du programme principal.

void setup()                     
   {    
    lcd_init(); //Initialisation de l'afficheur.
    lcd_gotoxy(1,1); //Mettre le curseur à la position.    
    lcd_send_byte(0,1); //Commande pour éffacer l'afficheur.
   }
   

   
   

