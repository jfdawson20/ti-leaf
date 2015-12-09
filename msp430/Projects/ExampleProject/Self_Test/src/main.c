/* Start Of File */
#include <string.h>

//main API header incluide 
#include "driverlib.h"


//board specific hardware settings and mappings 
#include "hal.h"
#include "usbserial.h"

//generic api 
#include <leaf-i2c.h>                  

//device drivers 
#include <sx1502.h>

/*----------------------------------------------------------------------------+
 | Main Routine                                                                |
 +----------------------------------------------------------------------------*/
void main (void)
{
   
	uint16_t ret;
    	char buf[BUFFER_SIZE] = "";

    	TILEAF_BoardInit(24000000);
    
	//init I2C bus 
	struct Leaf_I2C_Bus i2c_bus;
	ret = Leaf_I2C_Init(&i2c_bus,MODE_SLAVE,SPEED_100K,0x00);
	
	struct Leaf_I2C_Device io_expander;
	io_expander = sx1502_init(&i2c_bus,0x20);

	
	       
   	while (1)
    	{
		ret = sx1502_ReadGPIO(&io_expander,buf);
		SendBuffer(buf,1);
		__delay_cycles(24000000);      
	
   	}	  
}


