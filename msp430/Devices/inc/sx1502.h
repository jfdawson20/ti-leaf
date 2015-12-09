#include <stdio.h>
#include <leaf-i2c.h>

/* REGISTER MAP DEFINES*/
#define SX_REGDATA        0x00 
#define SX_REGDIR         0x01
#define SX_REGPULLUP      0x02
#define SX_REGPULLDOWN    0x03
#define SX_REGINTMASK     0x05
#define SX_REGSENSEHIGH   0x06
#define SX_REGSENSELOW    0x07
#define SX_REGINTSRC      0x08
#define SX_REGEVENTSTATUS 0x09
#define SX_REGPLDMODE     0x10
#define SX_REGPLDTABLE0   0x11
#define SX_REGPLDTABLE1   0x12
#define SX_REGPLDTABLE2   0x13
#define SX_REGPLDTABLE3   0x14
#define SX_REGPLDTABLE4   0x15
#define SX_REGADVANCED    0xAB

/* Structs */

/* Function Prototypes */

struct Leaf_I2C_Device sx1502_init(struct Leaf_I2C_Bus *bus, uint8_t address);

int16_t sx1502_ReadGPIO(struct Leaf_I2C_Device *dev, uint8_t *data);

int16_t sx1502_WriteGPIO(struct Leaf_I2C_Device *dev, uint8_t value, uint8_t mask);

int16_t sx1502_GetGPIODirection(struct Leaf_I2C_Device *dev, uint8_t *data);

int16_t sx1502_SetGPIODirection(struct Leaf_I2C_Device *dev, uint8_t setting, uint8_t mask);

int16_t sx1502_GetIntMask(struct Leaf_I2C_Device *dev, uint8_t *data);

int16_t sx1502_SetIntMask(struct Leaf_I2C_Device *dev, uint8_t mask);

int16_t sx1502_SetEdgeSense(struct Leaf_I2C_Device *dev, uint8_t port, uint8_t setting);

int16_t sx1502_GetEdgeSense(struct Leaf_I2C_Device *dev, uint8_t port, uint8_t *data);

int16_t sx1502_GetInts(struct Leaf_I2C_Device *dev, uint8_t *data);

int16_t sx1502_GetEvents(struct Leaf_I2C_Device *dev, uint8_t *data);

int16_t sx1502_SetPLD(struct Leaf_I2C_Device *dev, uint8_t value);

int16_t sx1502_GetPLD(struct Leaf_I2C_Device *dev, uint8_t *value);

int16_t sx1502_SetPLDTable(struct Leaf_I2C_Device *dev, uint8_t tableID, uint8_t table);

int16_t sx1502_GetPLDTable(struct Leaf_I2C_Device *dev, uint8_t tableID, uint8_t *table);

int16_t sx1502_EnableBoost(struct Leaf_I2C_Device *dev);

int16_t sx1502_DisableBoost(struct Leaf_I2C_Device *dev);
/* End oF File*/
