# makfile configuration
NAME            = ti-leaf-api
CPU             = msp430f5510
LIB             = lib
INC             = -Iinc -I/usr/ti/msp430/include -I../  
OBJ             = obj
SRC             = $(wildcard *.c)
SRCOBJ          = $(addprefix obj/,$(SRC:.c=.o))

COPS = -Wall -nostartfiles -ffreestanding -O3 -Os -g -fdata-sections -w -DDEPRECATED -D__$(CPU)__

#switch the compiler (for the internal make rules)
CC   = msp430-elf-gcc

#all should be the first target. it's built when make is run without args
all: ${OBJ} ${LIB} ${NAME}.a
	echo "API Compile Completed"

#confgigure the next line if you want to use the serial download

#additional rules for files
${NAME}.a: ${SRCOBJ}
	msp430-elf-ar rcs lib/lib${NAME}.a $^  

clean:
	rm -f obj/*.o
	rm -f obj/*.d
	rm -f lib/*.a

obj/%.o:%.c
	$(CC) -mmcu=${CPU} ${COPS} ${INC} -c -o $@ $<


${LIB}: 
	mkdir -p lib

${OBJ}:
	mkdir -p obj  
