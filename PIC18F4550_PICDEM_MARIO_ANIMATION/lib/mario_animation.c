int f=4;                  //set frames per second (fps)
int s;

const int mario_char_set_1[7][8]={ // first frame
          {
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00001,
            0b00001,
            0b00001,
            0b00000
          },
            {
            0b00001,
            0b00001,
            0b00001,
            0b00001,
            0b00000,
            0b00000,
            0b00000,
            0b00000
            },
            {
            0b00000,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11111
            },
            {
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11110
            },
            {
            0b00000,
            0b00000,
            0b11000,
            0b00000,
            0b11000,
            0b11100,
            0b11000,
            0b10000
            },
            {
            0b00000,
            0b10000,
            0b10000,
            0b10000,
            0b00000,
            0b00000,
            0b10000,
            0b00000
            },
            {
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000
            },

   };


const int mario_char_set_2[6][8]={
          {
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000
            },
            {
            0b00111,
            0b00111,
            0b00111,
            0b00000,
            0b00001,
            0b00011,
            0b00011,
            0b00001
            },
            {
            0b00000,
            0b01111,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b01111
            },
            {
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11001,
            0b00000,
            0b10000
            },
            {
            0b00000,
            0b00000,
            0b11100,
            0b10000,
            0b11100,
            0b11110,
            0b11100,
            0b11000
            }
            {
            0b11111,
            0b11111,
            0b10110,
            0b11110,
            0b11110,
            0b11110,
            0b00000,
            0b00000
            },
           
   };
   
   
const int mario_char_set_3[6][8]={
          {
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000
            },
            {
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00011,
            0b00011,
            0b00111,
            0b00000
            },
            {
            0b00000,
            0b00000,
            0b00111,
            0b01111,
            0b01111,
            0b11111,
            0b11111,
            0b11111
            },
            {
            0b01111,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b00111,
            0b00111
            },
            {
            0b00000,
            0b00000,
            0b10000,
            0b11110,
            0b11000,
            0b11110,
            0b11111,
            0b11110
            }
            {
            0b11100,
            0b11110,
            0b11100,
            0b11000,
            0b11000,
            0b10000,
            0b00000,
            0b10000
            },
           
   };   
   
const int mario_char_set_4[5][8]={
          {
            0b00000,
            0b00011,
            0b00111,
            0b00111,
            0b01111,
            0b01111,
            0b01111,
            0b00011
                        },
            {
            0b01111,
            0b01111,
            0b01111,
            0b01111,
            0b00111,
            0b00011,
            0b00011,
            0b00011
            },
            {
            0b00000,
            0b11000,
            0b11111,
            0b11100,
            0b11111,
            0b11111,
            0b11111,
            0b11110
                        },
            {
            0b11100,
            0b11110,
            0b11110,
            0b11110,
            0b11100,
            0b11100,
            0b11110,
            0b10000
            }, 
            {
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000
            },
   };    

const int mario_char_set_5[7][8]={
          {
            0b00000,
            0b00001,
            0b00011,
            0b00011,
            0b00111,
            0b00111,
            0b00111,
            0b00001
            },
            {
            0b11111,
            0b11111,
            0b11011,
            0b00111,
            0b01111,
            0b11111,
            0b11100,
            0b01110
            },
            {
            0b00000,
            0b11100,
            0b11111,
            0b11110,
            0b11111,
            0b11111,
            0b11111,
            0b11111
                        },
            {
            0b11111,
            0b11111,
            0b11110,
            0b11111,
            0b11111,
            0b01111,
            0b00000,
            0b00000
                        },
            {
            0b00000,
            0b00000,
            0b10000,
            0b00000,
            0b00000,
            0b10000,
            0b00000,
            0b00000
            }
            {
            0b11000,
            0b11000,
            0b10000,
            0b10000,
            0b10000,
            0b10000,
            0b00000,
            0b00000
            },
            {
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000
            },
           
   };
const int mario_char_set_6[6][8]={
          {
            0b00000,
            0b00000,
            0b00000,
            0b00001,
            0b00001,
            0b00011,
            0b00011,
            0b00011
            },
            {
            0b00001,
            0b00011,
            0b00111,
            0b01111,
            0b01111,
            0b11111,
            0b11000,
            0b00000
            },
            {
            0b00000,
            0b00000,
            0b11110,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11111
            },
            {
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11111,
            0b11110,
            0b11100,
            0b11110
            },
            {
            0b00000,
            0b00000,
            0b00000,
            0b10000,
            0b00000,
            0b10000,
            0b11000,
            0b10000
            }
            {
            0b00000,
            0b10000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000
            },
           
   };    

void assemble_mario_char_set_1() {      //Set CGRAM (8 chracters made by user)
   
   int cmd,i,j;
   
   for (i=0;i<7;i++)
      {
         cmd=(i<<3) + 0b1000000;
         lcd_send_byte(0,cmd);
         for (j=0;j<8;j++)
            {
               lcd_send_byte(1,mario_char_set_1[i][j]);
            }
   }
}

void assemble_mario_char_set_2() {      //Set CGRAM (8 chracters made by user)
   
   int cmd,i,j;
   
   for (i=0;i<6;i++)
      {
         cmd=(i<<3) + 0b1000000;
         lcd_send_byte(0,cmd);
         for (j=0;j<8;j++)
            {
               lcd_send_byte(1,mario_char_set_2[i][j]);
            }
   }
}

void assemble_mario_char_set_3() {      //Set CGRAM (8 chracters made by user)
   
   int cmd,i,j;
   
   for (i=0;i<6;i++)
      {
         cmd=(i<<3) + 0b1000000;
         lcd_send_byte(0,cmd);
         for (j=0;j<8;j++)
            {
               lcd_send_byte(1,mario_char_set_3[i][j]);
            }
   }
}

void assemble_mario_char_set_4() {      //Set CGRAM (8 chracters made by user)
  
  int cmd,i,j;
   
   for (i=0;i<5;i++)
      {
         cmd=(i<<3) + 0b1000000;
         lcd_send_byte(0,cmd);
         for (j=0;j<8;j++)
            {
               lcd_send_byte(1,mario_char_set_4[i][j]);
            }
   }
}


void assemble_mario_char_set_5() {      //Set CGRAM (8 chracters made by user)
   
   int cmd,i,j;
   
   for (i=0;i<7;i++)
      {
         cmd=(i<<3) + 0b1000000;
         lcd_send_byte(0,cmd);
         for (j=0;j<8;j++)
            {
               lcd_send_byte(1,mario_char_set_5[i][j]);
            }
   }
}

void assemble_mario_char_set_6() {      //Set CGRAM (8 chracters made by user)
   
   int cmd,i,j;
   
   for (i=0;i<6;i++)
      {
         cmd=(i<<3) + 0b1000000;
         lcd_send_byte(0,cmd);
         for (j=0;j<8;j++)
            {
               lcd_send_byte(1,mario_char_set_6[i][j]);
            }
   }
}

void setup_mario()
   {
      s=1000/f;            //fps to ms
   }
   
void mario_loop() 
   {
   
   int a=0;
   
   lcd_send_byte(0,1);
   for (a=0; a<20;a++)     //for loop to repeat marios animation until the end of the display
      {
         int b=a+1;
         int c=a+2;
         int d=a+3;

         assemble_mario_char_set_1();
         
         lcd_gotoxy(a,1);  // draw first frame
         lcd_send_byte(1,0);
         lcd_gotoxy(a,2);
         lcd_send_byte(1,1);
         lcd_gotoxy(b,1); 
         lcd_send_byte(1,2);
         lcd_gotoxy(b,2);
         lcd_send_byte(1,3);
         lcd_gotoxy(c,1); 
         lcd_send_byte(1,4);
         lcd_gotoxy(c,2);
         lcd_send_byte(1,5);
         delay_ms(s);
         
         
         assemble_mario_char_set_2();
         
         lcd_gotoxy(a,1);  // draw 2nd frame
         lcd_send_byte(1,0);
         lcd_gotoxy(a,2);
         lcd_send_byte(1,1);
         lcd_gotoxy(b,1); 
         lcd_send_byte(1,2);
         lcd_gotoxy(b,2);
         lcd_send_byte(1,3);
         lcd_gotoxy(c,1); 
         lcd_send_byte(1,4);
         lcd_gotoxy(c,2);
         lcd_send_byte(1,5);
         delay_ms(s);
         
         assemble_mario_char_set_3();
         
         lcd_gotoxy(a,1);  // draw 3rd frame
         lcd_send_byte(1,0);
         lcd_gotoxy(a,2);
         lcd_send_byte(1,1);
         lcd_gotoxy(b,1); 
         lcd_send_byte(1,2);
         lcd_gotoxy(b,2);
         lcd_send_byte(1,3);
         lcd_gotoxy(c,1); 
         lcd_send_byte(1,4);
         lcd_gotoxy(c,2);
         lcd_send_byte(1,5);
         delay_ms(s);
         
         assemble_mario_char_set_4();
         
         lcd_gotoxy(a,1);  // draw 4th frame
         lcd_send_byte(1,6);
         lcd_gotoxy(a,2);
         lcd_send_byte(1,6);
         lcd_gotoxy(b,1); 
         lcd_send_byte(1,0);
         lcd_gotoxy(b,2);
         lcd_send_byte(1,1);
         lcd_gotoxy(c,1); 
         lcd_send_byte(1,2);
         lcd_gotoxy(c,2);
         lcd_send_byte(1,3);
         delay_ms(s);
         
         assemble_mario_char_set_5();
         
         lcd_gotoxy(a,1);  // draw 5th frame
         lcd_send_byte(1,6);
         lcd_gotoxy(a,2);
         lcd_send_byte(1,6);
         lcd_gotoxy(b,1); 
         lcd_send_byte(1,0);
         lcd_gotoxy(b,2);
         lcd_send_byte(1,1);
         lcd_gotoxy(c,1); 
         lcd_send_byte(1,2);
         lcd_gotoxy(c,2);
         lcd_send_byte(1,3);
         lcd_gotoxy(d,1); 
         lcd_send_byte(1,4);
         lcd_gotoxy(d,2);
         lcd_send_byte(1,5);
         delay_ms(s);
         
         assemble_mario_char_set_6();
         
         lcd_gotoxy(b,1);  // draw 6th frame
         lcd_send_byte(1,0);
         lcd_gotoxy(b,2);
         lcd_send_byte(1,1);
         lcd_gotoxy(c,1); 
         lcd_send_byte(1,2);
         lcd_gotoxy(c,2);
         lcd_send_byte(1,3);
         lcd_gotoxy(d,1); 
         lcd_send_byte(1,4);
         lcd_gotoxy(d,2);
         lcd_send_byte(1,5);
         delay_ms(s);           
      } 
   }
