/* Start Of File */
#include <string.h>

//main API header incluide 
#include "driverlib.h"


//board specific hardware settings and mappings 
#include "hal.h"
#include "usbserial.h"
#include "transport.h"                  

/*----------------------------------------------------------------------------+
 | Main Routine                                                                |
 +----------------------------------------------------------------------------*/
void main (void)
{
   
	uint16_t ret = 0;
	uint8_t retbuf[BUFFER_SIZE];
    	struct CommandStruct receive;
	struct CommandStruct transmit;
	char strbuf[256];
	char wrbuf[16] = "write";
	char wrbuf2[16] = "defau";
	TILEAF_BoardInit(24000000);

/*	while(1)
	{
		ret = ReceiveBuffer(strbuf);
		if (ret > 0)
		{
			SendBuffer(wrbuf,5);
		}
	}*/
  	  	
       
	while (1)
	{	
		receive.command = 0x00;
		ret = 0;
		ret = WaitForCommand(&receive);	
	        if (ret > 0)
		{
			switch(receive.command)
			{
				case READ:
					//transmit.command = READ;
					//transmit.address = receive.address;
					//bufCopy((uint16_t*)receive.address, transmit.data,receive.length);
					///transmit.data[0] = 0xFF;
					//transmit.length = receive.length;
					break;

				case WRITE:
					SendBuffer(wrbuf,5);
					//transmit.command = WRITE;
					//transmit.address = receive.address;
					//bufCopy(receive.data,(uint16_t*)receive.address,receive.length);
					//transmit.data[0] = 0;
					break;
				default:
					SendBuffer(wrbuf2,5);
					break;
			}
			
			//TransmitCommand(&transmit);
		}

	}  
}


