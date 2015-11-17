# makfile configuration
NAME            = example
CPU             = msp430f5510
LIB             = ../lib
INC             = -I../inc -I../../../../API/driverLib -I../../../../API/ -I../USB/
#IINC            = -iquote../inc -iquote../../../../API/driverLib -iquote../../../../API/driverLib/inc -iquote../../../../API/USB_API -iquote../../../../API/USB_API/USB_Common/ -iquote../USB/
BIN             = ../bin
SRC             = $(wildcard ../src/*.c)
SRCOBJ          = $(addprefix ../lib/, $(notdir $(SRC:.c=.o)))
LD		= ../ld/msp430f5510.ld
LIBAPI 		= ../../../../API/driverLib/lib/ti-leaf-api.a
USBAPI 		= ../USB/lib/ti-leaf-usb-api.a
LIBPATH         = -L../../../../API/driverLib/lib/
LIBPATH         += -L../USB/lib/




COPS = -Wall -O2 -nostartfiles -ffreestanding 
AOPS = --warn --fatal-warnings

#switch the compiler (for the internal make rules)
CC   = msp430-gcc

#all should be the first target. it's built when make is run without args
all: ${BIN} ${LIB} ${LIBAPI} ${USBAPI} ${NAME}.elf ${NAME}.a43 ${NAME}.lst

#confgigure the next line if you want to use the serial download

#additional rules for files
${NAME}.elf: ../lib/hal.o ../lib/main.o
	msp430-gcc -mmcu=${CPU} -T${LD} ${INC} ${LIBPATH} ../lib/hal.o ../lib/main.o -lti-leaf-api -lti-leaf-usb-api -o ${BIN}/${NAME}.elf

${NAME}.a43: ${BIN}/${NAME}.elf
	msp430-objcopy -O ihex $^ ${BIN}/$@

${NAME}.lst: ${BIN}/${NAME}.elf
	msp430-objdump -dSt $^ >${BIN}/$@

clean:
	make clean -C ../../../../API/driverLib
	make clean -C ../USB/
	rm -f ../lib/*.o
	rm -f ../lib/*.d
	rm -f ../bin/*.elf
	rm -f ../bin/*.lst
	rm -f ../bin/*.a43
	rmdir ../bin
	rmdir ../lib

#backup archive
dist:
	tar czf dist.tgz *.c *.h *.txt makefile

#project dependencies
${BIN}: 
	mkdir -p ../bin

${LIB}:
	mkdir -p ../lib

${LIBAPI}:  
	make -C ../../../../API/driverLib

${USBAPI}:
	make -C ../USB/	

${SRCOBJ}: ${SRC}
	echo "SRC COMPILE"
	msp430-gcc -mmcu=${CPU} ${COPS} --iquote../../../../API -iquote ../../../../../API/USB_API/USB_Common/ ${INC} -c ../src/main.c -o ../lib/main.o  
	msp430-gcc -mmcu=${CPU} ${COPS} --iquote../../../../API -iquote ../../../../../API/USB_API/USB_Common/ ${INC} -c ../src/hal.c -o ../lib/hal.o  

