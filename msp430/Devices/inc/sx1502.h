#include <stdio.h>
#include <tileaf-i2c.h>

/* REGISTER MAP DEFINES*/
#define REGDATA        0x00 
#define REGDIR         0x01
#define REGPULLUP      0x02
#define REGPULLDOWN    0x03
#define REGINTMASK     0x05
#define REGSENSEHIGH   0x06
#define REGSENSELOW    0x07
#define REGINTSRC      0x08
#define REGEVENTSTATUS 0x09
#define REGPLDMODE     0x10
#define REGPLDTABLE0   0x11
#define REGPLDTABLE1   0x12
#define REGPLDTABLE2   0x13
#define REGPLDTABLE3   0x14
#define REGPLDTABLE4   0x15
#define REGADVANCED    0xAB

/* Structs */

/* Function Prototypes */

struct s_I2C_Handle sx1602_init();

int16_t ReadGPIO();

int16_t WriteGPIO(uint8_t value), uint8_t mask;

int16_t SetGPIODirection(uint8_t setting, uint8_t mask);

int16_t SetIntMask(uint8_t mask);

int16_t SetEdgeSense(uint8_t port, uint8_t setting);

int16_t CheckInts();

int16_t CheckEvents();

int16_t SetPLD(uint8_t tableID, uint8_t table);

int16_t EnableBoost();

int16_t DisableBoost();
/* End oF File*/
