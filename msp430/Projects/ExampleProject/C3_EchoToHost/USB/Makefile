# makfile configuration
NAME            = ti-leaf-usb-app-api
CPU             = msp430f5510
LIB             = lib
INC             = -iquote. -iquote../../../../API/driverLib -I../../../../API/ -I/usr/ti/msp430/include
OBJ             = obj
SRCAPP          = $(wildcard USB_app/*.c)
SRCCFG          = $(wildcard USB_config/*.c)
APPOBJ          = $(SRCAPP:USB_app/%.c=USB_app/obj/%.o)
CFGOBJ          = $(SRCCFG:USB_config/%.c=USB_config/obj/%.o)

COPS = -Wall -D__$(DEVICE)__ -DDEPRECATED -mmcu=msp430f5510 -O3 -Os -g -fdata-sections -w -nostartfiles -ffreestanding
AOPS = --warn --fatal-warnings

ULIB = ../../../../API/USB_API/lib/libti-leaf-usb-api.a
ULIBL = ../../../../API/USB_API/lib/

#switch the compiler (for the internal make rules)
CC   = msp430-elf-gcc

#all should be the first target. it's built when make is run without args
all: ${OBJ} ${LIB} ${ULIB} ${NAME}.a
	echo "Starting API Compile"
#confgigure the next line if you want to use the serial download

#additional rules for files
${NAME}.a: ${APPOBJ} ${CFGOBJ}
	msp430-elf-ar rcs lib/lib${NAME}.a $^  

clean:
	rm -f USB_app/obj/*.o
	rm -f USB_config/obj/*.o
	rm -f lib/*.a
	make clean -C ../../../../API/USB_API

${ULIB}:
	make -C ../../../../API/USB_API

USB_app/obj/%.o: USB_app/%.c
	echo "making objects"
	msp430-elf-gcc -mmcu=${CPU} ${COPS} ${INC} -c $< -o $@

USB_config/obj/%.o: USB_config/%.c
	echo "making config objects"
	msp430-elf-gcc -mmcu=${CPU} ${COPS} ${INC} -c $< -o $@

${LIB}: 
	mkdir -p lib

${OBJ}:
	mkdir -p USB_app/obj 
	mkdir -p USB_confg/obj	
