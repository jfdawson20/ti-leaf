# makfie configuration
#General Project Settings 
NAME		= example#		# Project name
CPU             = msp430f5510#		# msp430 part number, used by the compiler. 
REPOTIP         = ../../../../..#	# Tip of repo, points to ti-leaf directory

#Project Includes 
CINC	 = /usr/ti/msp430/include#			# msp430-elf-gcc compiler libaries and stuff  
PINC     = ../inc#					# project include files 
DINC     = ${REPOTIP}/msp430/API/driverLib#		# MSP430 API Library Includes 
AINC     = ${REPOTIP}/msp430/API/#			# MSP430 API Tip
AUINC    = ${REPOTIP}/msp430/API/USB_API#	       	# MSP430f5xx/6xx USB API
AUCINC   = ${REPOTIP}/msp430/API/USB_API/USB_Common#   	# 
UCINC    = ../USB#				# Project Specific USB Includes 
UAINC    = ../USB/USB_app/#
INCLUDES = -iquote${UAINC} -iquote${UCINC} -iquote${CINC} -iquote${PINC} -iquote${DINC} -iquote${AINC} -iquote${AUINC} -I${AUCINC} -I${CINC} -I${PINC} -I${DINC} -I${AINC} -I${AUINC} 

#Output Directories, where the objects and output binarys go
BIN             = ../bin#
OBJ		= ../obj#
USBAOBJ		= ../USB/USB_app/obj#	
USBCOBJ		= ../USB/USB_config/obj#

#source files
PROJSRC         = $(wildcard ../src/*.c)
USBAPPSRC	= $(wildcard ../USB/USB_app/*.c)
USBCFGSRC	= $(wildcard ../USB/USB_config/*.c)

#compiled objects 
PROJOBJ         = $(PROJSRC:../src/%.c=../obj/%.o)
USBAPPOBJ       = $(USBAPPSRC:../USB/USB_app/%.c=../USB/USB_app/obj/%.o)
USBCFGOBJ       = $(USBCFGSRC:../USB/USB_config/%.c=../USB/USB_config/obj/%.o)

#Linker Scripts
LD		=  -T /usr/ti/msp430/include/msp430f5510.ld# MSP430 device specific linker script.  
LD 		+= -T ../../../../API/USB_API/msp430USB.ld# MSP430F5xx/6xx USB API additional linker script 

#Static Library locations, names, etc 
LIBAPI 		= ../../../../API/driverLib/lib/ti-leaf-api.a
USBAPI 		= ../USB/lib/ti-leaf-usb-api.a
LIBPATH         = -L../../../../API/driverLib/lib/
LIBPATH         += -L../USB/lib/
LIBPATH         += -L../../../../API/USB_API/lib
LIBPATH         += -L/usr/ti/msp430/

#MSP430 USB BSL programmer and programmer command 
PROGDIR         = ../../../../../host/Host_USB_Software/Python_Firmware_Upgrader/
PROG            = sudo PYTHONPATH=${PROGDIR}/python-msp430-tools python -m msp430.bsl5.hid_1 -e -v -P 


#Compiler Options
COPS 	= -mmcu=${CPU} -Wall -D__${CPU}__ -DDEPRECATED -O3 -Os -fdata-sections -w### C Compiler Options 
#COPS 	= -Wall -DDEPRECATED -O3 -Os -fdata-sections -w### C Compiler Options 
LOPS 	= -Wl,--gc-sections#								# Linker Options 	
CC   	= msp430-elf-gcc#								# C compiler 
LDC  	= msp430-elf-ld#								# Linker 
OBCC 	= msp430-elf-objcopy#								# Object Copy Utility (Used to convert .elf to .hex files)
OBJDMP 	= msp430-elf-objdump#								# Object Dump Utiltiy (Used to create .lst file)
H2T    	= ../../../../../host/tools/hex2txt/hex2txt.bin#				# Hex2Txt utility (Used to convert .hex to ti-txt format files)


#all should be the first target. it's built when make is run without args
all: ${BIN} ${OBJ} ${LIBAPI} ${USBAPI} ${BIN}/${NAME}.elf ${BIN}/$(NAME).hex ${BIN}/$(NAME).txt ${BIN}/$(NAME).lst 

#Download target. running "make download" will perform a full compile and attempt to download the image onto 
#the ti-leaf board. for this to work the board must be installed in a USB port on the system and put into bootloader mode
download: ${BIN}/${NAME}.txt
	${PROG} ../bin/${NAME}.txt 

# .elf target: compiles project and produces an output binary in msp430-elf format 
${BIN}/${NAME}.elf: ${PROJOBJ} ${USBAPPOBJ} ${USBCFGOBJ}
	$(CC) ${LOPS} ${LD} ${INC} ${LIBPATH} -lti-leaf-usb-api -lti-leaf-api -lti-leaf-usb-api -lti-leaf-api ${PROJOBJ} ${USBAPPOBJ} ${USBCFGOBJ} -lti-leaf-usb-api -lti-leaf-api -lti-leaf-usb-api -lti-leaf-api -o ../bin/${NAME}.elf

# .hex target: converts .elf binary to an intel hex .hex binary. 
${BIN}/${NAME}.hex: ${BIN}/${NAME}.elf
	$(OBCC) -O ihex $^ ../bin/$@

# .lst target. converts .elf to .lst file. .lst file contains the assembly dump of the entire binary 
${BIN}/${NAME}.lst: ${BIN}/${NAME}.elf
	$(OBJDMP) -dSt $^ >../bin/$@

# .txt target: converts .hex to .txt binary. .txt binaries are used by the BSL USB programmer to program the board
${BIN}/${NAME}.txt: ${BIN}/${NAME}.hex
	$(H2T) ${BIN}/${NAME}.hex ${BIN}/${NAME}.txt

# clean target: deletes all generated output files (.o, .bin, etc) 
clean:
	make clean -C ../../../../API/driverLib
	make clean -C ../USB/
	rm -f ${AUINC}/USR_USB
	rm -f ../obj/*.o
	rm -f ../obj/*.d
	rm -f -r ../bin
	rm -f -r ../obj
	rm -f ../USB/USB_app/obj/*.o
	rm -f ../USB?USB_config/obj/*.o
	rm -f -r ../USB/USB_app/obj
	rm -f -r ../USB/USB_config/obj

dist target: packages up the project directory for release
dist:
	echo "not implemented yet"

#project dependencies
#bin target: create bin directory to hold project outputs
${BIN}: 
	mkdir -p ../bin
	ln -f -s ../../Projects/ExampleProject/Py_Transport/USB/USB_config ${AUINC}/USR_USB 

#obj target: create obj directories to hold object outputs 
${OBJ}:
	mkdir -p ../obj
	mkdir -p ../USB/USB_app/obj
	mkdir -p ../USB/USB_config/obj

#MSP430 API target: Builds driverLib MSP430 API
${LIBAPI}:  
	make -C ../../../../API/driverLib

#USB API target: Builds core USB API 
${USBAPI}:
	make -C ../../../../API/USB_API	

#Project Target: Build project specific files 
../obj/%.o: ../src/%.c
	msp430-elf-gcc ${COPS} ${INCLUDES} -c $< -o $@

../USB/USB_app/obj/%.o: ../USB/USB_app/%.c
	msp430-elf-gcc ${COPS} ${INCLUDES} -c $< -o $@

../USB/USB_config/obj/%.o: ../USB/USB_config/%.c
	msp430-elf-gcc ${COPS} ${INCLUDES} -c $< -o $@



