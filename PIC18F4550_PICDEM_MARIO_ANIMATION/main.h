////////////////////////////////Header LCD_Therm.h//////////////////////////////

//Incure la bibliothèque du microcontrolleur
#include <18F4550.h>

//Fuses
#fuses HSPLL,NOWDT,NOPROTECT,NODEBUG,NOBROWNOUT,USBDIV,PLL5,CPUDIV1,VREGEN,PUT,NOMCLR,NOLVP
#use delay(clock=48000000)
//Réserver les 800 premières case mémoire pour le bootloader.
#build(reset=0x800, interrupt=0x808) 
#org 0, 0x7ff { }

//#define LCD_TYPE 2

#define LCD_ENABLE_PIN PIN_E2
#define LCD_RS_PIN PIN_E0
#define LCD_RW_PIN PIN_E1
#define LCD_DATA4 PIN_D4
#define LCD_DATA5 PIN_D5
#define LCD_DATA6 PIN_D6
#define LCD_DATA7 PIN_D7
#define LCD_TYPE 2

#include <lcd.c>


