# makfile configuration
NAME            = ti-leaf-usb-api
CPU             = msp430f5510
LIB             = lib
INC             = -iquote. -I../../../../API/
OBJ             = obj
SRC             = $(wildcard USB_app/*.c)
SRC             += $(wildcard USB_config/*.c)
SRCOBJ          = $(addprefix obj/, $(notdir $(SRC:.c=.o)))

COPS = -Wall -O2 -nostartfiles -ffreestanding
AOPS = --warn --fatal-warnings

#switch the compiler (for the internal make rules)
CC   = msp430-gcc

#all should be the first target. it's built when make is run without args
all: ${OBJ} ${LIB} ${NAME}.a
	echo "Starting API Compile"
#confgigure the next line if you want to use the serial download

#additional rules for files
${NAME}.a: ${SRCOBJ}
	msp430-ar rcs lib/lib${NAME}.a $^  

clean:
	rm -f obj/*.o
	rm -f lib/*.a

${SRCOBJ}: ${SRC}
	#msp430-gcc -mmcu=${CPU} ${COPS} -iquote. -iquote../../../../API/ ${INC} -c $< -o $@
	msp430-gcc -mmcu=${CPU} ${COPS} ${INC} -c $< -o $@
	#msp430-gcc ${COPS} -quote ${INC} -c $< -o $@

${LIB}: 
	mkdir -p lib

${OBJ}:
	mkdir -p obj  
