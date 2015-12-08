//project specific USB includes 
#include "USB_config/descriptors.h"
#include "USB_API/USB_Common/device.h"
#include "USB_API/USB_Common/usb.h"                 // USB-specific functions
#include "USB_API/USB_CDC_API/UsbCdc.h"
#include "USB_app/usbConstructs.h"
#include "driverlib.h"

#define BUFFER_SIZE 256 

//function prototypes 
uint16_t checkUSB(char * buf);
uint16_t SendBuffer(char * buf, uint16_t length);
uint16_t ReceiveBuffer(char *buf);
