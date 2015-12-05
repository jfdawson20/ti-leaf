/* Start Of File */
#include <string.h>

//main API header incluide 
#include "driverlib.h"


//board specific hardware settings and mappings 
#include "hal.h"
#include "usbserial.h"
                  

/*----------------------------------------------------------------------------+
 | Main Routine                                                                |
 +----------------------------------------------------------------------------*/
void main (void)
{
   
    uint16_t ret;
    char buf[BUFFER_SIZE] = "hello\n\r";

    TILEAF_BoardInit(24000000);
    	       
    while (1)
    {
	SendBuffer(buf,7);
	__delay_cycles(24000000);      

    }  
}


