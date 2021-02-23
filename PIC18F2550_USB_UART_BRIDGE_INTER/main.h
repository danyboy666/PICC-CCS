/* main.h */

// PIDCDEM hex output note: prepend :020000040000FA for PIDCDEM software
#EXPORT (FILE=.\rls\PIC18F2550_USB_UART_BRIDGE_INTER_v1_0.HEX)

#include <18F2550.h> // Include pic device header file
#device PASS_STRINGS = IN_RAM
#device adc=10
#fuses HSPLL, NOWDT, PLL3, CPUDIV1, USBDIV, NOVREGEN, PUT, NOMCLR, NOLVP // 12Mhz resonator
#use delay(clock=48000000)



// setup rs232
#use rs232(uart1, baud=115200, parity=N, bits=8, stream=ESP,errors)

//bootloader space for PICDEM FS USB. Comment this is you're flashing directly.
//#build(reset=0x800, interrupt=0x808) 
//#org 0, 0x7ff { }

//include some libraries
//#include <stdlib.h>


/////////////////////////////////////////////////////////////////////////////
//
// If you are using a USB connection sense pin, define it here.  If you are
// not using connection sense, comment out this line.  Without connection
// sense you will not know if the device gets disconnected.
//       (connection sense should look like this:
//                             100k
//            VBUS-----+----/\/\/\/\/\----- (I/O PIN ON PIC)
//                     |
//                     +----/\/\/\/\/\-----GND
//                             100k
//        (where VBUS is pin1 of the USB connector)
//
/////////////////////////////////////////////////////////////////////////////
///only the 18F4550 development kit has this pin
#include <stdlib.h>

/////////////////////////////////////////////////////////////////////////

//set to 1 to use a PIC's internal USB Peripheral
//set to 0 to use a National USBN960x peripheral
#define __USB_PIC_PERIF__ 1

//#if __USB_PIC_PERIF__ && defined(__PCH__)
 #define USB_CON_SENSE_PIN PIN_B2
//#endif


// PIC CCS firmware not provided in this code you need to copy them from the driver folder if this is not compiling.
// Includes all USB code and interrupts, as well as the CDC API
#include <usb_cdc.h>



