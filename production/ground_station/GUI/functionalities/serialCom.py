import serial
import json
# "COM11" is the port that your Arduino board is connected.set it to port that your are using
ser = serial.Serial("COM1", 9600)
while True:
    cc=str(ser.readline())[2:][:-5]
    if cc[0]=='[':
        cansatData=json.loads(cc)
        print(cansatData)
    else:
        print(cc)