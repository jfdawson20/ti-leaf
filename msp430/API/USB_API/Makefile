# makfile configuration
NAME            = ti-leaf-usb-api
CPU             = msp430f5510
LIB             = lib
INC             = -iquote. -iquote../driverLib -I../driverLib -I.. -I../../Projects/ExampleProject/C3_EchoToHost/USB/USB_config -I/usr/ti/msp430/include
OBJ             = obj
SRCUSB_CDC      = $(wildcard USB_CDC_API/*.c)         
SRCUSB_HID      = $(wildcard USB_HID_API/*.c)         
SRCUSB_MSC      = $(wildcard USB_MSC_API/*.c)         
SRCUSB_PHDC     = $(wildcard USB_PHDC_API/*.c)         
SRCUSB_COMMON   = $(wildcard USB_Common/*.c)         
CDC_OBJ         = $(SRCUSB_CDC:USB_CDC_API/%.c=USB_CDC_API/obj/%.o)
HID_OBJ         = $(SRCUSB_HID:USB_HID_API/%.c=USB_HID_API/obj/%.o)
MSC_OBJ         = $(SRCUSB_MSC:USB_MSC_API/%.c=USB_MSC_API/obj/%.o)
PHDC_OBJ        = $(SRCUSB_PHDC:USB_PHDC_API/%.c=USB_PHDC_API/obj/%.o)
COM_OBJ         = $(SRCUSB_COMMON:USB_Common/%.c=USB_Common/obj/%.o)

COPS = -Wall -D__$(DEVICE)__ -DDEPRECATED -mmcu=msp430f5510 -O3 -Os -g -fdata-sections -w -nostartfiles -ffreestanding
AOPS = --warn --fatal-warnings

#switch the compiler (for the internal make rules)
CC   = msp430-elf-gcc

#all should be the first target. it's built when make is run without args
all: ${OBJ} ${LIB} ${NAME}.a
	echo "Starting API Compile"
#confgigure the next line if you want to use the serial download

#additional rules for files
${NAME}.a: ${COM_OBJ} ${CDC_OBJ} ${HID_OBJ} ${MSC_OBJ} ${PHDC_OBJ}
	msp430-elf-ar rcs lib/lib${NAME}.a $^  

clean:
	rm -f USB_Common/obj/*.o
	rm -f USB_CDC_API/obj/*.o
	rm -f USB_HID_API/obj/*.o
	rm -f USB_MSC_API/obj/*.o
	rm -f USB_PHDC_API/obj/*.o
	rm -f lib/*.a

USB_Common/obj/%.o: USB_Common/%.c
	echo "making objects"
	msp430-elf-gcc -mmcu=${CPU} ${COPS} ${INC} -c $< -o $@

USB_CDC_API/obj/%.o: USB_CDC_API/%.c
	echo "making config objects"
	msp430-elf-gcc -mmcu=${CPU} ${COPS} ${INC} -c $< -o $@

USB_HID_API/obj/%.o: USB_HID_API/%.c
	echo "making config objects"
	msp430-elf-gcc -mmcu=${CPU} ${COPS} ${INC} -c $< -o $@
    
USB_MSC_API/obj/%.o: USB_MSC_API/%.c
	echo "making config objects"
	msp430-elf-gcc -mmcu=${CPU} ${COPS} ${INC} -c $< -o $@
    
USB_PHDC_API/obj/%.o: USB_PHDC_API/%.c
	echo "making config objects"
	msp430-elf-gcc -mmcu=${CPU} ${COPS} ${INC} -c $< -o $@
${LIB}: 
	mkdir -p lib

${OBJ}:
	mkdir -p USB_Common/obj 
	mkdir -p USB_CDC_API/obj	
	mkdir -p USB_HID_API/obj	
	mkdir -p USB_MSC_API/obj	
	mkdir -p USB_PHDC_API/obj	
