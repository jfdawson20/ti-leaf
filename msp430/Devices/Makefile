# makfile configuration
NAME            = device-api
CPU             = msp430f5510
LIB             = lib
INC             = -iquote. -iquote../driverLib -iquoteinc/ -I../driverLib -Iinc -I/usr/ti/msp430/include
OBJDIR          = src/obj
SRCS            = $(wildcard src/*.c) 
OBJS            = $(SRCS:src/%.c=src/obj/%.o)

COPS = -Wall -D__$(CPU)__ -DDEPRECATED  -O3 -Os -fdata-sections -w -nostartfiles -ffreestanding
AOPS = --warn --fatal-warnings

#switch the compiler (for the internal make rules)
CC   = msp430-elf-gcc

#all should be the first target. it's built when make is run without args
all: ${OBJDIR} ${LIB} ${NAME}.a
	echo "Finished Device Compile"
#confgigure the next line if you want to use the serial download

#additional rules for files
${NAME}.a: ${OBJS}
	msp430-elf-ar rcs lib/lib${NAME}.a $^  

clean:
	rm -f src/obj/*.o
	rm -f lib/*.a

src/obj/%.o: src/%.c
	msp430-elf-gcc -mmcu=${CPU} ${COPS} ${INC} -c $< -o $@
${LIB}: 
	mkdir -p lib

${OBJDIR}:
	mkdir -p src/obj 
