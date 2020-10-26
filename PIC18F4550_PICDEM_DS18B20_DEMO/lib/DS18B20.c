///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************/
/*                                                                           */
/* Mini driver pour le capteur de température intelligent Dallas DS18S20     */
/*                                                                           */
/*                                                                           */
/*                                                                           */ 
/* Copyright Dany Ferron                                                     */
/*****************************************************************************/
////////////////////////////////////////////////////////////////////////////////
//#include <18F4550.h>
/////////////////////////////////Constantes/////////////////////////////////////
#define PIN_DQ       PIN_C1
#define THERMOSTAT   PIN_A2
#define ALARME       PIN_A3
#define DS_LENGHT
//////////////////////////declaration des fonctions.////////////////////////////
short ds_reset();
void ds_write_bit(int1 bit_to_send);
void ds_write_byte(int8 byte_to_send);
short ds_read_bit();
char ds_read_byte();
/////////////////////////////Variable globales./////////////////////////////////
int8 receive_bytes[DS_LENGHT]={0,0,0,0,0,0,0,0,0};
/////////////////////////////Fonction principale.///////////////////////////////
float ds1820_read()
{
   int8 i,temp_var;
   float result;
   
   ds_reset();
   ds_write_byte(0xCC);
   ds_write_byte(0x44);
   ds_reset();
   ds_write_byte(0xCC);
   ds_write_byte(0xBE);
   
   for(i=0;i<9;i++)
   {
      receive_bytes[i]=ds_read_byte();
   }
   
   //put in temp all the 8 bits of MSB
   temp_var = receive_bytes[1];
   if (receive_bytes[1] > 0x80)
   {
      temp_var=!temp_var + 1; //two’s complement adjustment
      temp_var=temp_var * -1; //flip value negative.
   }
   result=((temp_var*256)+(receive_bytes[0]));
   result=result*0.0625;
   
   return(result);
}
short ds_reset()
{
   int8 response;
   output_low(PIN_DQ);
   delay_us(500);
   output_float(PIN_DQ);
   delay_us(80);
   delay_us(500);
   response=input(PIN_DQ);
   return(response);
}
void ds_write_bit(int1 bit_to_send)
{
   output_low(PIN_DQ);
   delay_us(2);
   output_bit(PIN_DQ,bit_to_send);
   delay_us(80);
   output_float(PIN_DQ);
}
void ds_write_byte(int8 byte_to_send)
{
   int8 i;
   
   for(i=0;i<8;i++)
   {
      ds_write_bit(bit_test(byte_to_send,i));
   }
}
short ds_read_bit()
{
   int1 bit_value=0;
   
   output_low(PIN_DQ);
   delay_us(2);
   output_float(PIN_DQ);
   delay_us(5);
   
   bit_value=input(PIN_DQ);
   
   delay_us(120);//Time slot
   
   
   return(bit_value);
}
char ds_read_byte()
{
   int8 i,byte_value=0,bit_read;
   
   for(i=0;i<8;i++)
   {
      bit_read=ds_read_bit();
      
      if(bit_read==1)byte_value=byte_value|(0x01<<i);
   }
   
   return(byte_value);
}
