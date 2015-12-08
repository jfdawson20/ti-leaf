#ifndef LEAF_I2C
#define LEAF_I2C

/* Library Includes */
#include <stdio.h>
#include <eusci_b_i2c.h>


/* Defines */
#define MODE_SLAVE  0x01
#define MODE_MASTER 0x00
#define SPEED_100K  100
#define SPEED_400K  400 

#define STATUS_ENABLED;
#define STATUS_DISABLED;


/* Structs */

struct Leaf_I2C_Bus
{
	uint8_t current_speed;
	uint8_t status;
	uint8_t mode; 	
	uint16_t base;
};

struct Leaf_I2C_Device 
{
	uint8_t DeviceID;
	uint8_t Address;
	uint8_t maxspeed;
};

struct Leaf_I2C_Packet
{
	uint8_t slaveAddress;
	uint8_t length;
	uint8_t buffer[64];
	uint8_t timeout = 100;
};

/* Function Prototypes */

int16_t Leaf_I2C_Init(struct Leaf_I2C_Bus *bus, uint8_t mode, uint8_t speed, uint8_t slaveAddr);
int16_t Leaf_I2C_WritePacket(struct Leaf_I2C_Packet *p);
int16_t Leaf_I2C_WriteByte(uint8_t address, uint8_t data);
int16_t Leaf_I2C_ReadPacket(struct Leaf_I2C_Packet *p);
int16_t Leaf_I2C_ReadByte(uint8_t address, uint8_t *data)


#endif







