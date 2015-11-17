# makfile configuration
NAME            = ti-leaf-api
CPU             = msp430f5510
LIB             = lib
INC             = -Iinc -I/home/jack/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5/include$
OBJ             = obj
SRC             = $(wildcard *.c)
SRCOBJ          = $(addprefix obj/,$(SRC:.c=.o))

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
	rm -f obj/*.d
	rm -f lib/*.a

obj/%.o:%.c
	msp430-gcc -mmcu=${CPU} ${COPS} ${INC} -c -o $@ $<


${LIB}: 
	mkdir -p lib

${OBJ}:
	mkdir -p obj  
