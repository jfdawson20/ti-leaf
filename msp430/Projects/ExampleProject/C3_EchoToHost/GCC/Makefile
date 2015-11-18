DEVICE = MSP430F5510
EXAMPLE_NAME = C3_EchoToHost
USB_BASE =  ~/Sandbox/ti-leaf/msp430
REDHAT_GCC = 
CC = msp430-elf-gcc
GDB = msp430-elf-gdb
SUPPORT_FILE_DIRECTORY = /usr/ti/msp430/include
DRIVERLIB_DIR = ~/Sandbox/ti-leaf/msp430/API/driverLib
MSP430_FILE = $(USB_BASE)/API/USB_API/msp430USB.ld
PROJECT_ROOT = $(USB_BASE)/examples/CDC_VirtualCOMport/$(EXAMPLE_NAME)
USB_CONFIG = $(PROJECT_ROOT)/USB_config
USB_API = $(USB_BASE)/API/USB_API/


CFLAGS = -iquote../inc -iquote$(DRIVERLIB_DIR) -iquote$(USB_API) -iquote$(USB_API)/USB_Common/ -iquote ../USB -I../USB/USB_config -I $(SUPPORT_FILE_DIRECTORY) -I $(USB_BASE) -I $(DRIVERLIB_DIR) -I $(PROJECT_ROOT) -I $(USB_CONFIG) -I $(USB_API) -D__$(DEVICE)__ -DDEPRECATED -mmcu=msp430f5510 -O3 -Os -fdata-sections -w
LFLAGS = -T $(MSP430_FILE) -T $(SUPPORT_FILE_DIRECTORY)/msp430f5510.ld -Wl,--gc-sections

SRC_FILES = \
../src/hal.c \
../src/main.c \
../src/system_pre_init.c \
../USB/USB_app/usbConstructs.c \
../USB/USB_app/usbEventHandling.c \
../USB/USB_config/descriptors.c \
../USB/USB_config/UsbIsr.c \
../../../../API/USB_API/USB_CDC_API/UsbCdc.c \
../../../../API/USB_API/USB_Common/usb.c \
../../../../API/USB_API/USB_Common/usbdma.c \
../../../../API/USB_API/USB_HID_API/UsbHid.c \
../../../../API/USB_API/USB_HID_API/UsbHidReq.c \
../../../../API/USB_API/USB_MSC_API/UsbMscReq.c \
../../../../API/USB_API/USB_MSC_API/UsbMscScsi.c \
../../../../API/USB_API/USB_MSC_API/UsbMscStateMachine.c \
../../../../API/USB_API/USB_PHDC_API/UsbPHDC.c \
../../../../API/driverLib/adc10_a.c \
../../../../API/driverLib/adc12_a.c \
../../../../API/driverLib/aes.c \
../../../../API/driverLib/battbak.c \
../../../../API/driverLib/comp_b.c \
../../../../API/driverLib/crc.c \
../../../../API/driverLib/dac12_a.c \
../../../../API/driverLib/dma.c \
../../../../API/driverLib/eusci_a_spi.c \
../../../../API/driverLib/eusci_a_uart.c \
../../../../API/driverLib/eusci_b_i2c.c \
../../../../API/driverLib/eusci_b_spi.c \
../../../../API/driverLib/flashctl.c \
../../../../API/driverLib/gpio.c \
../../../../API/driverLib/ldopwr.c \
../../../../API/driverLib/mpy32.c \
../../../../API/driverLib/pmap.c \
../../../../API/driverLib/pmm.c \
../../../../API/driverLib/ram.c \
../../../../API/driverLib/ref.c \
../../../../API/driverLib/rtc_a.c \
../../../../API/driverLib/rtc_b.c \
../../../../API/driverLib/rtc_c.c \
../../../../API/driverLib/sd24_b.c \
../../../../API/driverLib/sfr.c \
../../../../API/driverLib/sysctl.c \
../../../../API/driverLib/tec.c \
../../../../API/driverLib/timer_a.c \
../../../../API/driverLib/timer_b.c \
../../../../API/driverLib/timer_d.c \
../../../../API/driverLib/tlv.c \
../../../../API/driverLib/ucs.c \
../../../../API/driverLib/usci_a_spi.c \
../../../../API/driverLib/usci_a_uart.c \
../../../../API/driverLib/usci_b_i2c.c \
../../../../API/driverLib/usci_b_spi.c \
../../../../API/driverLib/wdt_a.c \


C3_EchoToHost: $(SRC_FILES)
	$(CC) $(CFLAGS) $(LFLAGS) $? -o $(EXAMPLE_NAME).out

debug: C3_EchoToHost
	$(GDB) $(EXAMPLE_NAME).out
