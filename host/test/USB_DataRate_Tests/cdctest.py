#!/usr/bin/python
import argparse 
import time 
import serial 
import sys


#start of main program 
#argument parsing 
parser = argparse.ArgumentParser(description='Hex Programmer Utility')
parser.add_argument('-s','--serial', help='Serial Port Device File', required=True)
parser.add_argument('-o','--out', help='output log file')
parser.add_argument('-b','--bytesize', help='maximum byte size')
parser.add_argument('-r','--runs', help='send iterations')


logfile = None 
args         = vars(parser.parse_args())
port         = args['serial']
logfile      = args['out']
byteSize     = int(args['bytesize'])
siter	     = int(args['runs'])

#setup serial port 
ser = serial.Serial(
	port=port,
	baudrate=2,
	parity=serial.PARITY_NONE,
	stopbits=serial.STOPBITS_ONE, 
	bytesize=serial.EIGHTBITS,
	timeout=.1
)

data    = []
payload = []
for i in range(byteSize):
	payload.append('b'*i)

x=1
for p in payload:
	startTime = time.time()
	print "STARTING TEST: " + str(startTime)
	print "PAYLOAD SIZE: " + str(x) + " Byte(s)\n"

	for i in range(siter):
		ser.write(p)


	endTime = time.time()
	tElapse = endTime - startTime;

	rate = (siter*8*x)/tElapse
	data.append((x,rate/siter))
	
	print "TIME: " + str(tElapse) + " s\n"
	print "RATE: " + str(rate) + " bits/s\n"
	print "RATEL " + str(rate/1000) + " kb/s\n"
	x = x +1

if logfile != None:
	fhandle = open(logfile,'w')

for stuff in data:
	fhandle.write(str(stuff[0])+","+str(stuff[1])+"\n")
	
if logfile != None:
	fhandle.close()

print "PROGRAM FINISHED\n"

      
      
      
