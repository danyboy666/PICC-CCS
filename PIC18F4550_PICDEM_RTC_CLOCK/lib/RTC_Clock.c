//////////////////////////////////////////////////////////////////////////////// 
///                           RTC_Clock.C                                    /// 
///                     Driver for Real Time Clock                           /// 
///                        DS1307 and PCF8583                                /// 
/// init_I2C_Clock() - Enable oscillator without clearing the seconds        ///
///                    register used when PIC loses power and DS1307 run     ///
///                    from 3V BAT                                           ///
///                  (Must be called at the start of the program)            ///
/// write_I2C_Clock() - Writes adress and data to the RTC Clock              ///
/// read_I2C_Clock()  - Reads the data from adress location                  ///
///                                                                          ///
//////////////////////////////////////////////////////////////////////////////// 
///                                                                          ///
/// Auteur: Francois-Joseph Hug                                              ///
/// Modification: Dany Ferron                                                ///
///                                                                          ///
////////////////////////////////////////////////////////////////////////////////


 
#define I2C_Clock 0xA2 // <-------- à faire ATTENTION!!! La broche A0 est mise
                       // au +5v pour changer l'addresse sur le BUS I2C à 0xA2.
                       // Ceci évite d'éventuels problèmes avec d'autres 
                       // périphériques qui empruntent le BUS I2C comme les
                       // mémoires EEPROMs qui sont sur l'addresse 0xA0.
#define I2C_Clock2 0xD0

#ifndef _I2C_Clock_LIB
  #define _I2C_Clock_LIB
  #ifndef I2C_Clock_Chip // set chip used if not defined
    #define I2C_Clock_Chip 2 // 1 for PCF8583, 2 for DS1307
  #endif
  
  struct rtc_var // Functions prototypes
  { 
  BYTE second; BYTE minute; BYTE hour; BYTE day; BYTE month; BYTE year; BYTE weekday; 
  }
  rtc_value;
  
  void config_I2C_Clock(BYTE cfg);
  BYTE read_I2C_Clock(BYTE rtcreg);
  void write_I2C_Clock(BYTE rtcreg, BYTE rtc_data);
  void init_I2C_Clock(void);
  void get_I2C_Clock(void);
  void set_I2C_Clock(BYTE hour, BYTE minut, BYTE second, BYTE day, BYTE month, BYTE year, BYTE weekday);

  void config_I2C_Clock(BYTE cfg) // Write cfg to config register
  { 
    i2c_start();
    #if (I2C_Clock_Chip == 1 )
      i2c_write(I2C_clock);
      i2c_write(0x00); // point to config register
    #else
      i2c_write(I2C_clock2);
      i2c_write(0x07); // point to config register
    #endif
    i2c_write(cfg);
    i2c_stop();
  }

  BYTE read_I2C_Clock(BYTE rtcreg) // rtc read subroutine
  { 
    BYTE datain;
    i2c_start();
    #if (I2C_Clock_Chip == 1 )
      i2c_write(I2C_clock); // Device address
    #else
      i2c_write(I2C_clock2);
    #endif
    i2c_write(rtcreg); // Send address of register to read
    i2c_start(); // Restart
    #if (I2C_Clock_Chip == 1 ) // Change data direction
      i2c_write(I2C_clock+1);
    #else
      i2c_write(I2C_clock2+1);
    #endif
    datain=i2c_read(0); // Now read from slave
    i2c_stop();
    return(datain);
  }

  void write_I2C_Clock(BYTE rtcreg, BYTE rtc_data) // Writes rtc_data at address rtcreg
  { 
    i2c_start();
    #if (I2C_Clock_Chip == 1 )
      i2c_write(I2C_clock); // Device address
    #else
      i2c_write(I2C_clock2); // Device address
    #endif
    i2c_write(rtcreg);
    i2c_write(rtc_data);
    i2c_stop();
  }

  void init_I2C_Clock() 
  {
    #if (I2C_Clock_Chip == 1 )
      config_I2C_Clock(0x00); // Setup config
    #else
      BYTE tmp;
    //  config_I2C_Clock(0x90); // Setup config, with 1Hz output on int
      tmp = read_I2C_Clock(0x02); // Set in 24h mode
      bit_clear(tmp,6);
      write_I2C_Clock(0x02, tmp);
      tmp = read_I2C_Clock(0x00); // Make sure oscillator is running (bit 7 reg0 = 0)
      bit_clear(tmp,7);
      write_I2C_Clock(0x00, tmp);
    #endif
  }

  void get_I2C_Clock() 
  {
    #if (I2C_Clock_Chip == 1 )
    
      BYTE tmp;
      rtc_value.second=read_I2C_Clock(0x02) & 0x7f;
      rtc_value.minute=read_I2C_Clock(0x03) & 0x7f;
      rtc_value.hour=read_I2C_Clock(0x04) & 0x3f;
      tmp=read_I2C_Clock(0x05);
      rtc_value.day = tmp & 0x3f; // day is 6 lower bits
      rtc_value.year = (tmp & 0xc0) >> 6; // year is 2 upper bits
      tmp=read_I2C_Clock(0x06);
      rtc_value.month = tmp & 0x1f; // month is 5 lower bits
      rtc_value.weekday = (tmp & 0xe0) >> 5; // weekday is 3 upper bits
    #else
      rtc_value.second=read_I2C_Clock(0x00) & 0x7f;
      rtc_value.minute=read_I2C_Clock(0x01) & 0x7f;
      rtc_value.hour=read_I2C_Clock(0x02) & 0x7f;
      rtc_value.weekday=read_I2C_Clock(0x03) & 0x07;
      rtc_value.day=read_I2C_Clock(0x04) & 0x3f;
      rtc_value.month=read_I2C_Clock(0x05) & 0x1f;
      rtc_value.year=read_I2C_Clock(0x06);
    #endif
  }

  void set_I2C_Clock(BYTE hour, BYTE minut, BYTE second, BYTE day, BYTE month, BYTE year, BYTE weekday) 
  {
    #if (I2C_Clock_Chip == 1 )
      BYTE tmp;
      write_I2C_Clock(0x02, second & 0x7f);
      write_I2C_Clock(0x03, minut & 0x7f);
      write_I2C_Clock(0x04, hour);
      tmp = day & 0x3f;
      tmp = tmp | ((year % 4) << 6); // year is 2 upper bits of byte
      write_I2C_Clock(0x05, tmp);
      tmp = month & 0x1f;
      tmp = tmp | (weekday << 5); // weekday is 3 upper bits of byte
      write_I2C_Clock(0x06, tmp);
    #else
      write_I2C_Clock(0x00, second & 0x7f);
      write_I2C_Clock(0x01, minut & 0x7f);
      write_I2C_Clock(0x02, hour & 0x7f);
      write_I2C_Clock(0x03, weekday & 0x07);
      write_I2C_Clock(0x04, day & 0x3f);
      write_I2C_Clock(0x05, month & 0x1f);
      write_I2C_Clock(0x06, year);
    #endif
  }
#endif
