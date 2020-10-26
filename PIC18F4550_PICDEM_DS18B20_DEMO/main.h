#include <18F4550.h> // pic we use

//Fuses
#fuses HSPLL,NOWDT,NOPROTECT,NODEBUG,NOBROWNOUT,USBDIV,PLL5,CPUDIV1,VREGEN,PUT,NOMCLR,NOLVP
#use delay(clock=48000000)
//Réserver les 800 premières case mémoire pour le bootloader. (PICDEM)
#build(reset=0x800, interrupt=0x808) 
#org 0, 0x7ff { }

// LCD defines

#define LCD_ENABLE_PIN  PIN_E2
#define LCD_RW_PIN      PIN_E1
#define LCD_RS_PIN      PIN_E0
#define LCD_DATA4       PIN_D4
#define LCD_DATA5       PIN_D5
#define LCD_DATA6       PIN_D6
#define LCD_DATA7       PIN_D7
#define LCD_TYPE 2  

// Include CCS lcd driver
#include <lcd.c> //Pilote LCD.
//#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)
//#use i2c(Master,Fast,sda=PIN_B0,scl=PIN_B1,force_hw)
#use i2c(Master,Fast,sda=PIN_C2,scl=PIN_D0) //software



