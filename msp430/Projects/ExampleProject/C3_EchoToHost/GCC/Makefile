# makfile configuration
NAME            = example
CPU             = msp430f5510
LIB             = ../lib
INC             = ../inc ../../../../API/inc ../../../../API 
BIN             = ../bin
SRC             = $(wildcard ../src/*.c)
SRCOBJ          = $(addprefix ../lib/, $(notdir $(SRC:.c=.o)))
LD		= ../ld/msp430f5510.ld
APISRC	 	= $(wildcard ../../../../API/*.c)
APIOBJ	 	= $(APISRC:.c=.o)

COPS = -Wall -O2 -nostartfiles -ffreestanding -MMD
AOPS = --warn --fatal-warnings

#switch the compiler (for the internal make rules)
CC   = msp430-gcc

#all should be the first target. it's built when make is run without args
all: ${BIN} ${LIB} ${NAME}.elf ${NAME}.a43 ${NAME}.lst

#confgigure the next line if you want to use the serial download

#additional rules for files
${NAME}.elf: ${APIOBJ} ${SRCOBJ}
	echo ${SRCOBJ}
	echo ${APIOBJ}
	msp430-gcc -mmcu=${CPU} -T${LD} $< -o ${BIN}/${NAME}.elf

${NAME}.a43: ${BIN}/${NAME}.elf
	msp430-objcopy -O ihex $^ ${BIN}/$@

${NAME}.lst: ${BIN}/${NAME}.elf
	msp430-objdump -dSt $^ >${BIN}/$@

clean:
	rm -f lib/*.o
	rm -f bin/*.elf
	rm -f bin/*.lst
	rm -f bin/*.a43
	rm -f ../../../API/*.o

#backup archive
dist:
	tar czf dist.tgz *.c *.h *.txt makefile

#project dependencies
${BIN}: 
	mkdir bin

${LIB}:
	mkdir lib

${APIOBJ}: ${APISRC}
	echo "API COMPILE"
	msp430-gcc -mmcu=${CPU} ${COPS} -quote ${INC} -c $< -o $@ 

${SRCOBJ}: ${SRC}
	echo "SRC COMPILE"
	msp430-gcc -mmcu=${CPU} ${COPS} -iquote ${INC} -c $< -o $@ 

