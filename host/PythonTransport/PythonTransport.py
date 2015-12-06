#!/usr/bin/python
import argparse 
import time 
import serial 
import sys


#start of main program 
#argument parsing 
parser = argparse.ArgumentParser(description='Hex Programmer Utility')
parser.add_argument('-s','--serial', help='Serial Port Device File', required=True)


logfile = None 
args         = vars(parser.parse_args())
port         = args['serial']

USCABASE = 0x05C0


#setup serial port 
ser = serial.Serial(
	port=port,
	baudrate=2,
	parity=serial.PARITY_NONE,
	stopbits=serial.STOPBITS_ONE, 
	bytesize=serial.EIGHTBITS,
	timeout=.1
)

p=[]
r=[]
for i in range(64):
	p.append(0x00)
	r.append("")

p[0] = 0x02
p[1] = 0x00
p[2] = 0x04
p[3] = 0x00
p[5] = 0x01

ser.flush()
ser.write(p)     
r = ser.read(3)
ser.flush()
print r
for x in r: 
	print str(x)
