#include <stdio.h>
#include "leaf-i2c.h"


int16_t Leaf_I2C_Init(struct Leaf_I2C_Bus *bus, uint8_t mode, uint8_t speed, uint8_t slaveAddr)
{	
	int16_t ret = 0;	

	bus->current_speed = speed;
	bus->mode   	   = mode;
	bus->base          = I2C_BASE;

	if (mode == MODE_MASTER)
	{
		USCI_B_I2C_initMasterParam masterInit;

		//set clock source based off of board config
		masterInit.selectClockSource = Board_GetClockSource(I2C_CLK);
	
		//set frequency based off of board config
		masterInit.i2cClk = Board_GetClockSpeed(I2C_CLK);
		
		//set data rate based off of user config
		if(speed == SPEED_400K)
			masterInit.dataRate = USCI_B_I2C_SET_DATA_RATE_400KBPS;

		else
			masterInit.dataRate = USCI_B_I2C_SET_DATA_RATE_100KBPS;

		//initialize Master Address
		USCI_B_I2C_initMaster(I2C_BASE, &masterInit);
	
	}
	else
	{
		//initialize Slave Address
		USCI_B_I2C_initSlave(I2C_BASE, slaveAddr);	
	}	

	return 0;

}

int16_t Leaf_I2C_WritePacket(struct Leaf_I2C_Bus *bus, struct Leaf_I2C_Packet *p)
{	

	uint16_t i = 0;
	uint32_t timeout = 100;
    
	//wait for bus to be free 
	while(USCI_B_I2C_isBusBusy(bus->base) != USCI_B_I2C_BUS_NOT_BUSY);
	
	//set slave address
	USCI_B_I2C_setSlaveAddress(bus->base, p->address);

    //Set Transmit mode
    USCI_B_I2C_setMode(bus->base,USCI_B_I2C_TRANSMIT_MODE);

    //Enable I2C Module to start operations
    USCI_B_I2C_enable(bus->base);
    
	//send first byte 
	USCI_B_I2C_masterSendMultiByteStartWithTimeout(bus->base,p->buffer[0],p->timeout);
        
	for (i =1;i < (p->length-1);i++)
	{
		while(USCI_B_I2C_isBusBusy(bus->base) != USCI_B_I2C_BUS_NOT_BUSY);
		USCI_B_I2C_masterSendMultiByteNextWithTimeout(bus->base,p->buffer[i],p->timeout);	      
	}
    
    while(USCI_B_I2C_isBusBusy(bus->base) != USCI_B_I2C_BUS_NOT_BUSY);    
	USCI_B_I2C_masterSendMultiByteFinishWithTimeout(bus->base,p->buffer[i],p->timeout);
	
    //disable I2C 
    USCI_B_I2C_disable(bus->base);
	return(0);
}	

int16_t Leaf_I2C_WriteByte(struct Leaf_I2C_Bus *bus, uint8_t data, uint8_t address)
{	

	uint16_t i = 0;
	uint32_t timeout = 1;
	//wait for bus to be free 
	while(USCI_B_I2C_isBusBusy(bus->base) != USCI_B_I2C_BUS_NOT_BUSY);
	
	//set slave address
	USCI_B_I2C_setSlaveAddress(bus->base, address);

    //Set Transmit mode
    USCI_B_I2C_setMode(bus->base,USCI_B_I2C_TRANSMIT_MODE);

    //Enable I2C Module to start operations
    USCI_B_I2C_enable(bus->base);
    
	//send first byte 
	USCI_B_I2C_masterSendSingleByte(bus->base,data);
	
    //wait for completion
    while(USCI_B_I2C_isBusBusy(bus->base) != USCI_B_I2C_BUS_NOT_BUSY);    
	
	return(0);
}	

int16_t Leaf_I2C_ReadPacket(struct Leaf_I2C_Bus *bus, struct Leaf_I2C_Packet *p)
{	

	uint16_t i = 0;
	uint32_t timeout = 100;
    
	//wait for bus to be free 
	while(USCI_B_I2C_isBusBusy(bus->base) != USCI_B_I2C_BUS_NOT_BUSY);
	
	//set slave address
	USCI_B_I2C_setSlaveAddress(bus->base, p->address);

    //Set Transmit mode
    USCI_B_I2C_setMode(bus->base,USCI_B_I2C_RECEIVE_MODE);

    //Enable I2C Module to start operations
    USCI_B_I2C_enable(bus->base);
    
    //init multi receive , send start 
    USCI_B_I2C_masterReceiveMultiByteStart(bus->base);
    
	for (i =0;i < (p->length-1);i++)
	{
		while(USCI_B_I2C_isBusBusy(bus->base) != USCI_B_I2C_BUS_NOT_BUSY);
		p->buffer[i] = USCI_B_I2C_masterReceiveMultiByteNext(bus->base);	      
	}
    
    while(USCI_B_I2C_isBusBusy(bus->base) != USCI_B_I2C_BUS_NOT_BUSY);    
	p->buffer[i] = USCI_B_I2C_masterReceiveMultiByteFinish(bus->base);
	
    //disable I2C 
    USCI_B_I2C_disable(bus->base);
	return(0);
}

int16_t Leaf_I2C_ReadByte(struct Leaf_I2C_Bus *bus, uint8_t *data, uint8_t address )
{	

	uint16_t i = 0;
	uint32_t timeout = 100;
    
	//wait for bus to be free 
	while(USCI_B_I2C_isBusBusy(bus->base) != USCI_B_I2C_BUS_NOT_BUSY);
	
	//set slave address
	USCI_B_I2C_setSlaveAddress(bus->base, address);

    //Set Transmit mode
    USCI_B_I2C_setMode(bus->base,USCI_B_I2C_RECEIVE_MODE);

    //Enable I2C Module to start operations
    USCI_B_I2C_enable(bus->base);
    
    //init multi receive , send start 
    USCI_B_I2C_masterReceiveSingleStart(bus->base);
    
	while(USCI_B_I2C_isBusBusy(bus->base) != USCI_B_I2C_BUS_NOT_BUSY);
	*data = USCI_B_I2C_masterReceiveSingle(bus->base);	      
	
    //disable I2C 
    USCI_B_I2C_disable(bus->base);
	return(0);
}

/* End Of File*/
