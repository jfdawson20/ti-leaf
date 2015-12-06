#ifndef TRANSPORT_H
#define TRANSPORT_H


#define READ   0x01
#define WRITE  0x02


struct CommandStruct 
{
	uint8_t  command;
	uint16_t address;
	uint16_t length;
	uint16_t data[59];
};


int16_t WaitForCommand(struct CommandStruct * c);
uint16_t TransmitCommand(struct CommandStruct *c);
void bufCopy(uint8_t *src, uint8_t *dest, uint8_t length);


#endif
