#include <stdlib.h>
#include "driverlib.h"
#include "hal.h"
#include "transport.h"
#include "usbserial.h"  



#define VALID_SIZE 64

//256 Byte working buffer
static char buffer[64];


int16_t WaitForCommand(struct CommandStruct *c)
{
	uint16_t count = 0;
	
	count = ReceiveBuffer(buffer);
	
	if((count > 0 ) && (buffer[0] == "f"))
	{
		c->command = 0x02;//buffer[0];
		//c->address = ((buffer[1]<<8) | (buffer[2]));
		//c->length  = ((buffer[4]<<8) | (buffer[3]));
		//bufCopy(buffer+5,c->data,59);
		return count;
	}

	else if(count == 0)
		return 0;

	else 
		return -1;	
}

uint16_t TransmitCommand(struct CommandStruct *c)
{
	/*buffer[0] = c->command;
	buffer[1] = (uint8_t)(c->address)>>8;
	buffer[2] = (uint8_t)(c->address);
	buffer[3] = (uint8_t)(c->length)>>8;
	buffer[4] = (uint8_t)(c->length);*/
	
	buffer[0] = "J";
	buffer[1] = "J";
	buffer[2] = "J";
	//bufCopy(c->data,(buffer+5),c->length);

	SendBuffer(buffer,3);
	return (0);
}
void bufCopy(uint8_t *src, uint8_t *dest, uint8_t length)
{
	uint8_t i;
	for(i = 0; i<length;i++)
	{
		dest[i] = src[i];
	}
}
