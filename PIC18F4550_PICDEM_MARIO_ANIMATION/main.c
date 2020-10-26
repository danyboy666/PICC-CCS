///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************/
/*                                                                           */
/* Super Mario Bros animation heavily based on Jan Stapler's Arduino project */
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
#EXPORT (FILE=.\rls\MARIO_ANIMATION_v1_0.HEX)
//Bibliothèques utilisés
#include <main.h> //Header pour le programme.
#include <.\lib\mario_animation.c>

void setup();

///////////////////////////Programme principale.////////////////////////////////

void main()
   {  
    setup(); 
    setup_mario();
      while(TRUE) //Boucle infinie.
      {
         mario_loop();
      }  
} //Fin du programme principal.

void setup()                     
   {   
      lcd_init(); //Initialisation de l'afficheur.
      lcd_gotoxy(1,1); //Mettre le curseur à la position.    
      lcd_send_byte(0,1); //Commande pour éffacer l'afficheur.    
   }
   

 
   

