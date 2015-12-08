#ifndef LEAF_I2C
#define LEAF_I2C

/* Library Includes */
#include <stdio.h>
#include <usci_b_i2c.h>

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

/* Defines */
#define MODE_SLAVE  0x01
#define MODE_MASTER 0x00
#define SPEED_100K  100
#define SPEED_400K  400 

#define STATUS_ENABLED;
#define STATUS_DISABLED;


/* Structs */

//*****************************************************************************
//
//! \brief I2C Bus struct used in all Leaf I2C API Calls 
//
//*****************************************************************************
struct Leaf_I2C_Bus
{
	uint8_t current_speed;
	uint8_t status;
	uint8_t mode; 	
	uint16_t base;
};

//*****************************************************************************
//
//! \brief Leaf I2C Device Structure
//
//*****************************************************************************
struct Leaf_I2C_Device 
{
	uint8_t DeviceID;
	uint8_t Address;
	uint8_t maxspeed;
};

//*****************************************************************************
//
//! \brief Leaf I2C Packet used for bulk read/write transactions
//
//*****************************************************************************
struct Leaf_I2C_Packet
{
	uint8_t slaveAddress;
	uint8_t length;
	uint8_t buffer[64];
	uint8_t timeout = 100;
};

/* Function Prototypes */

//*****************************************************************************
//
//! \brief Initializes Leaf I2C Bus 
//!
//! This function initializes operation of the I2C Block on the Leaf board. 
//! This function must be called before any other I2C API Functions are used
//!
//! \param bus, Pointer to I2C Bus structure used with all Leaf I2C API Functions
//! \param mode, Configures I2C Bus as Master or Slave (MODE_MASTER, MODE_SLAVE)
//! \param speed, Configures I2C Bus speed (SPEED_400K, SPEED_100K)
//! \param slaveAddr, Sets Slave Address (Slave Mode Only)
//!
//!
//! \return 0 on success, bus structure will be populated
//
//*****************************************************************************
int16_t Leaf_I2C_Init(struct Leaf_I2C_Bus *bus, uint8_t mode, uint8_t speed, uint8_t slaveAddr);


//*****************************************************************************
//
//! \brief Writes Packet Data 
//!
//! This function accepts a Leaf_I2C_Packet sturcture and writes all data
//! out of I2C bus 
//!
//! \param bus, Pointer to I2C Bus structure used with all Leaf I2C API Functions
//! \param p, Leaf_I2C_Packet to send 
//!
//!
//! \return 0 on success
//
//*****************************************************************************
int16_t Leaf_I2C_WritePacket(struct Leaf_I2C_Packet *p);


//*****************************************************************************
//
//! \brief Writes a single byte 'data' to slave device at 'address'
//!
//! This function accepts a single byte of data and a target slave address
//! 
//!
//! \param bus, Pointer to I2C Bus structure used with all Leaf I2C API Functions
//! \param data, single byte of data to write out of device
//! \param address, Target slave address
//!
//!
//! \return 0 on success
//
//*****************************************************************************
int16_t Leaf_I2C_WriteByte(uint8_t address, uint8_t data, uint8_t address);


//*****************************************************************************
//
//! \brief Writes a single byte 
//!
//! This function accepts a Leaf_I2C_Packet sturcture and writes all data
//! out of I2C bus 
//!
//! \param bus, Pointer to I2C Bus structure used with all Leaf I2C API Functions
//! \param p, Leaf_I2C_Packet to send 
//!
//!
//! \return 0 on success
//
//*****************************************************************************
int16_t Leaf_I2C_ReadPacket(struct Leaf_I2C_Packet *p);


//*****************************************************************************
//
//! \brief Reads a single byte 'data' from slave device at 'address'
//!
//! This function accepts reads a single byte from device at 'address'
//! 
//!
//! \param bus, Pointer to I2C Bus structure used with all Leaf I2C API Functions
//! \param *data, buffer to hold recieved byte
//! \param address, Target slave address
//!
//!
//! \return 0 on success
//
//*****************************************************************************
int16_t Leaf_I2C_ReadByte(uint8_t address, uint8_t *data, uint8_t address)

#ifdef __cplusplus
}
#endif
#endif







