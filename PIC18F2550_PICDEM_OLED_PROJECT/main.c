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
#EXPORT (FILE=OLED_PROJECT_v1_0.HEX)
//Bibliothèques utilisés

#include <main.h> //Header pour le programme.

//sda=PIN_B0,scl=PIN_B1,force_hw
//#use I2C(MASTER, I2C1, FAST = 400000, stream = SSD1306_STREAM)
#use I2C(MASTER, sda=PIN_B0,scl=PIN_B1, FAST = 400000, stream = SSD1306_STREAM, SMBUS,force_hw)

//#define SSD1306_RST PIN_D0


//#define SSD1306_128_64
#define SSD1306_128_32
//#define SSD1306_96_16


#include <SSD1306OLED.c>

#define LEDB pin_C2 //Active sur niveau bas.

void setup();


void testdrawcircle(void) {
  for (int8 i = 0; i < SSD1306_LCDHEIGHT; i += 2) {
    SSD1306_DrawCircle(SSD1306_LCDWIDTH/2, SSD1306_LCDHEIGHT/2, i);
    SSD1306_Display();
    delay_ms(1);
  }
}
 
void testfillrect(void) {
  int1 color = TRUE;
  for (int8 i = 0; i < SSD1306_LCDHEIGHT/2; i += 3) {
    // alternate colors
    SSD1306_FillRect(i, i, SSD1306_LCDWIDTH - i*2, SSD1306_LCDHEIGHT - i*2, color);
    SSD1306_Display();
    delay_ms(1);
    if(color)  color = FALSE;
    else       color = TRUE;
  }
}
 
void testdrawtriangle(void) {
  for (int8 i = 0; i < SSD1306_LCDHEIGHT/2; i += 5) {
    SSD1306_DrawTriangle(SSD1306_LCDWIDTH/2,     SSD1306_LCDHEIGHT/2 - i,
                         SSD1306_LCDWIDTH/2 - i, SSD1306_LCDHEIGHT/2 + i,
                         SSD1306_LCDWIDTH/2 + i, SSD1306_LCDHEIGHT/2 + i);
    SSD1306_Display();
    delay_ms(1);
  }
}
 
void testfilltriangle(void) {
  int1 color = TRUE;
  for (signed int16 i = SSD1306_LCDHEIGHT/2; i > 0; i -= 5) {
    SSD1306_FillTriangle(SSD1306_LCDWIDTH/2,     SSD1306_LCDHEIGHT/2 - i,
                         SSD1306_LCDWIDTH/2 - i, SSD1306_LCDHEIGHT/2 + i,
                         SSD1306_LCDWIDTH/2 + i, SSD1306_LCDHEIGHT/2 + i, color);
    if(color)  color = FALSE;
    else       color = TRUE;
    SSD1306_Display();
    delay_ms(1);
  }
}
 
void testdrawroundrect(void) {
  for (int8 i = 0; i < SSD1306_LCDHEIGHT/2 - 2; i += 2) {
    SSD1306_DrawRoundRect(i, i, SSD1306_LCDWIDTH - 2*i, SSD1306_LCDHEIGHT - 2*i, SSD1306_LCDHEIGHT/4 - i/2);
    SSD1306_Display();
    delay_ms(1);
  }
}
 
void testfillroundrect(void) {
  int1 color = TRUE;
  for (int8 i = 0; i < SSD1306_LCDHEIGHT/2 - 2; i += 2) {
    SSD1306_FillRoundRect(i, i, SSD1306_LCDWIDTH - 2*i, SSD1306_LCDHEIGHT - 2*i, SSD1306_LCDHEIGHT/4 - i/2, color);
    if(color)  color = FALSE;
    else       color = TRUE;
    SSD1306_Display();
    delay_ms(1);
  }
}
   
void testdrawrect(void) {
  for (int8 i = 0; i < SSD1306_LCDHEIGHT/2; i += 2) {
    SSD1306_DrawRect(i, i, SSD1306_LCDWIDTH - 2*i, SSD1306_LCDHEIGHT - 2*i);
    SSD1306_Display();
    delay_ms(1);
  }
}
 
void testdrawline() {  
  signed int16 i;
  for (i = 0; i < SSD1306_LCDWIDTH; i += 4) {
    SSD1306_DrawLine(0, 0, i, SSD1306_LCDHEIGHT - 1);
    SSD1306_Display();
    delay_ms(1);
  }
  for (i = 0; i < SSD1306_LCDHEIGHT; i += 4) {
    SSD1306_DrawLine(0, 0, SSD1306_LCDWIDTH - 1, i);
    SSD1306_Display();
    delay_ms(1);
  }
  delay_ms(250);
  
  SSD1306_ClearDisplay();
  for (i = 0; i < SSD1306_LCDWIDTH; i += 4) {
    SSD1306_DrawLine(0, SSD1306_LCDHEIGHT - 1, i, 0);
    SSD1306_Display();
    delay_ms(1);
  }
  for (i = SSD1306_LCDHEIGHT - 1; i >= 0; i -= 4) {
    SSD1306_DrawLine(0, SSD1306_LCDHEIGHT - 1, SSD1306_LCDWIDTH - 1, i);
    SSD1306_Display();
    delay_ms(1);
  }
  delay_ms(250);
  
  SSD1306_ClearDisplay();
  for (i = SSD1306_LCDWIDTH - 1; i >= 0; i -= 4) {
    SSD1306_DrawLine(SSD1306_LCDWIDTH - 1, SSD1306_LCDHEIGHT - 1, i, 0);
    SSD1306_Display();
    delay_ms(1);
  }
  for (i = SSD1306_LCDHEIGHT - 1; i >= 0; i -= 4) {
    SSD1306_DrawLine(SSD1306_LCDWIDTH - 1, SSD1306_LCDHEIGHT - 1, 0, i);
    SSD1306_Display();
    delay_ms(1);
  }
  delay_ms(250);
 
  SSD1306_ClearDisplay();
  for (i = 0; i < SSD1306_LCDHEIGHT; i += 4) {
    SSD1306_DrawLine(SSD1306_LCDWIDTH - 1, 0, 0, i);
    SSD1306_Display();
    delay_ms(1);
  }
  for (i = 0; i < SSD1306_LCDWIDTH; i += 4) {
    SSD1306_DrawLine(SSD1306_LCDWIDTH - 1, 0, i, SSD1306_LCDHEIGHT - 1); 
    SSD1306_Display();
    delay_ms(1);
  }
  delay_ms(250);
}
 
void testscrolltext(void) {
  SSD1306_ClearDisplay();
  SSD1306_DrawText(58, 8, "scroll", 2);
  SSD1306_Display();
  delay_ms(1);
 
  SSD1306_StartScrollRight(0x00, 0x0F);
  delay_ms(2000);
  SSD1306_StopScroll();
  delay_ms(1000);
  SSD1306_StartScrollLeft(0x00, 0x0F);
  delay_ms(2000);
  SSD1306_StopScroll();
  delay_ms(1000);    
  SSD1306_StartScrollDiagRight(0x00, 0x07);
  delay_ms(2000);
  SSD1306_StartScrollDiagLeft(0x00, 0x07);
  delay_ms(2000);
  SSD1306_StopScroll();
}
 
 
 
/////////////////////////// Main program begin ///////////////////////////////

void main()
   {  

    delay_ms(1000);
    output_high (LEDB);
    // Initialize the SSD1306 OLED with an I2C addr = 0x7A (default address)
  SSD1306_Begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);
 
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  SSD1306_Display();
  delay_ms(2000);
 
  // Clear the buffer.
  SSD1306_ClearDisplay();
 
  // draw a single pixel
  SSD1306_DrawPixel(10, 10);
  // Show the display buffer on the hardware.
  // NOTE: You _must_ call SSD1306_Display() after making any drawing commands
  // to make them visible on the display hardware!
  SSD1306_Display();
  delay_ms(2000);
  SSD1306_ClearDisplay();
 
  // draw many lines
  testdrawline();
  SSD1306_Display();
  delay_ms(2000);
  SSD1306_ClearDisplay();
 
  // draw rectangles
  testdrawrect();
  SSD1306_Display();
  delay_ms(2000);
  SSD1306_ClearDisplay();
 
  // draw multiple rectangles
  testfillrect();
  SSD1306_Display();
  delay_ms(2000);
  SSD1306_ClearDisplay();
 
  // draw mulitple circles
  testdrawcircle();
  SSD1306_Display();
  delay_ms(2000);
  SSD1306_ClearDisplay();
 
  // draw a white circle, 10 pixel radius
  SSD1306_FillCircle(SSD1306_LCDWIDTH/2, SSD1306_LCDHEIGHT/2, 10);
  SSD1306_Display();
  delay_ms(2000);
  SSD1306_ClearDisplay();
 
  testdrawroundrect();
  SSD1306_Display();
  delay_ms(2000);
  SSD1306_ClearDisplay();
 
  testfillroundrect();
  SSD1306_Display();
  delay_ms(2000);
  SSD1306_ClearDisplay();
 
  testdrawtriangle();
  SSD1306_Display();
  delay_ms(2000);
  SSD1306_ClearDisplay();
 
  testfilltriangle();
  SSD1306_Display();
  delay_ms(2000);
  SSD1306_ClearDisplay();
 
  // draw scrolling text
  testscrolltext();
  SSD1306_Display();
  delay_ms(2000);
  SSD1306_ClearDisplay();
 
  // text display tests
  char txt[9];
  SSD1306_DrawText(2, 7, "Hello, world!", 1);
  
  sprintf(txt, "%.6f", 3.141592);
  SSD1306_DrawText(2, 16, txt, 1);
  
  SSD1306_DrawText(2, 26, "0x", 2);
  
  sprintf(txt, "%LX", 0xDEADBEEF);
  SSD1306_DrawText(26, 26, txt, 2);
  SSD1306_Display();
  delay_ms(2000);
  
  while(TRUE) {
    // invert the display
    SSD1306_InvertDisplay(TRUE);
    delay_ms(1000);
    SSD1306_InvertDisplay(FALSE);
    delay_ms(1000);
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
   
