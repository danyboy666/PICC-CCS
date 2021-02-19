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
/* *** Add pull ups in i2C lines                                             */
/*                                                                           */
/* le 25 octobre 2020                                                        */
/*                                                                           */
/*****************************************************************************/
///////////////////////////////////////////////////////////////////////////////

// compiled with PCW CCS v 4.104
// PIDCDEM hex output note: prepend :020000040000FA for PIDCDEM software
#EXPORT (FILE=VolmeterOled_PROJECT_v1_0.HEX)
//Bibliothèques utilisés

#include <main.h> //Header pour le programme.

//sda=PIN_B0,scl=PIN_B1,force_hw
#use I2C(MASTER, I2C1, FAST = 400000, stream = SSD1306_STREAM)
//#use I2C(MASTER, sda=PIN_B0,scl=PIN_B1, FAST = 400000, stream = SSD1306_STREAM, SMBUS,force_hw)

//#define SSD1306_RST PIN_D0
//Vref(3);

//#define SSD1306_128_64
//#define SSD1306_128_32
//#define SSD1306_96_16


#include <SSD1306OLED.c>

#define LEDB pin_C2 //Active sur niveau bas.

void setup();
 
//long int value;   
//double Vfinal;  
 
/////////////////////////// Main program begin ///////////////////////////////

void main()
   {  
   // Initialize the SSD1306 OLED with an I2C addr = 0x7A (default address) // ==>  0x78 for my display
   SSD1306_Begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);
   //setup_adc_ports(AN0|VSS_VDD);
   setup_adc_ports(AN0);
   //setup_adc(ADC_CLOCK_INTERNAL);
   setup_adc(ADC_CLOCK_DIV_8);
   set_adc_channel(0);
   //setup_vref(FALSE);
   delay_us(20);
   
   int16 adc_value;
   float volts;

   //setup_oscillator(False);
   //set_tris_c(0b10000000); //rc7 en entree, rx1.
//   unsigned int blinkc = 0       ; // state/count of blink.
   
    delay_ms(1000);
    output_high (LEDB);
    
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  SSD1306_Display();
  //delay_ms(2000);
  
  
  
  // Clear the buffer.
  SSD1306_ClearDisplay();
 
  
 // char txt[];
  
  
  while(TRUE) {
  delay_ms(400);
  SSD1306_ClearDisplay();
  adc_value = read_adc(); // Lecture du port et conversion de la valeure 
                          // recue sur le port et la met en variable int16(mot).
  //Vfinal = value * 0.01953125; // Conversion en variable à virgule flottante.
  //voltage = (voltage * 5 * 10)/ (1024);
  volts = (float)(adc_value * 3.3) / 1023.0;  
  
  //sprintf(volt, "%4.3f", voltage);
  //printf(volt);
  //inttostr(voltage,volt); // it converts integer value into string
  
  printf("%c%c",0xfe,0x84);      
  printf("%s","Voltmetre C.C");
  printf("%c%c",0xfe,0xc0);
  printf("%s","(precision 10 bits)");
  printf("%c%c",0xfe,0xd8);
  printf("%4.3f Volts",volts);    
  
  SSD1306_DrawText(2, 7, "Voltmetre CC", 1);
  SSD1306_GotoXY(2, 16);
  SSD1306_TextSize(2);
  //printf(SSD1306_Print, "%4.3f Volts", voltage);
  //printf(lcd_putc, "\f%3.2f", volts);
  printf(SSD1306_Print, "%4.3f Volts", volts);
  //SSD1306_DrawText(2, 16, voltage, 1);
  SSD1306_Display();
  
  }
 
}
// End of code.
   


void setup()                     
   {    
//    lcd_init(); //Initialisation de l'afficheur.
//    lcd_gotoxy(1,1); //Mettre le curseur à la position.    
//    lcd_send_byte(0,1); //Commande pour éffacer l'afficheur.
   output_low (LEDB);
   }
   
