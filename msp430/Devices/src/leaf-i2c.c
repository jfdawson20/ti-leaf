#include <stdio.h>
#include "leaf-I2c.h"


int16_t Leaf_I2C_Init(struct Leaf_I2C_Bus *bus, uint8_t mode, uint8_t speed, uint8_t slaveAddr)
{	
	int16_t ret = 0;	

	bus->current_speed = speed;
	bus->status 	   = STATUS_DISABLED;
	bus->mode   	   = mode;
	bus->base          = I2C_BASE;

	if (mode == MODE_MASTER)
	{
		UCSI_B_I2C_initMasterParam masterInit;

		//set clock source based off of board config
		masterInit.selectClockSource = GetClockSource(I2C_CLK);
	
		//set frequency based off of board config
		masterInit.i2cClk = getClockSpeed(I2C_CLK);
		
		//set data rate based off of user config
		if(speed == SPEED_400K)
			masterInit.dataRate = EUSCI_B_I2C_SET_DATA_RATE_400KBPS;

		else
			masterInit.dataRate = EUSCI_B_I2C_SET_DATA_RATE_100KBPS;

		//byte threshold feature not used currently
		masterInit.byteCounterThreshold = 0x00;
		masterInit.autoSTOPGeneration	= EUSCI_B_I2C_NO_AUTO_STOP;

		//initialize Master Address
		USCI_B_I2C_initMaster(I2C_BASE, masterInit);
	
	}
	else
	{
		//initialize Slave Address
		USCI_B_I2C_initSlave(I2C_BASE, slaveAddr);	
	}	

	//enable I2C
	USCI_B_I2C_Enable(I2C_BASE);
	return 0;

}

int16_t Leaf_I2C_WritePacket(struct Leaf_I2C_Bus *bus, struct Leaf_I2C_Packet *p)
{	

	uint16_t i = 0;
	uint32_t timeout = 1;
	//wait for bus to be free 
	while(USCI_B_I2C_isBusBusy(bus->base) != USCI_B_I2C_BUS_NOT_BUSY);
	
	//set slave address
	USCI_B_I2C_setSlaveAddress(bus->base, p->address);

	//send first byte 
	USCI_B_I2C_masterSendMultiByteStartWithTimeout(b->base,p->buffer[0],p->timeout);
	
	for (i =1;i < (p->length-1);i++)
	{
		while(USCI_B_I2C_isBusBusy(bus->base) != USCI_B_I2C_BUS_NOT_BUSY);
		USCI_B_I2C_masterSendMultiByteNextWithTimeout(b->base,p->buffer[i],p->timeout);	
	}
	
	USCI_B_I2C_masterSendMultiByteStopWithTimeout((b->base,p->buffer[i],p->timeout);
	
	return(0);
}	
/* End Of File*/
