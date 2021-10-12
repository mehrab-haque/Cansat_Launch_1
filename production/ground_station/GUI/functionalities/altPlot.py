import serial
import json
#import matplotlib.pyplot as plt
import time
import threading

import time


dataPoints=[]






def current_milli_time():
    return round(time.time() * 1000)

ser = serial.Serial("COM4", 9600)



def kbdListener():
    global dataPoints
    while True:
        kbdInput = input()
        if kbdInput=='launch':
            with open("output.txt", "a") as f:
                f.write((str(current_milli_time())+" => launched\n"))
                print("launch confirmed...")
                dataPoints=[]
        elif kbdInput=='rocket_grounded':
            with open("output.txt", "a") as f:
                f.write((str(current_milli_time())+" => rocket grounded\n"))
                print("rocket grounded confirmed...")
        elif kbdInput=='cansat_grounded':
            with open("output.txt", "a") as f:
                f.write((str(current_milli_time())+" => cansat grounded\n"))
                print("cansat grounded confirmed...")
        else:
            ser.write(kbdInput.encode())

listener = threading.Thread(target=kbdListener)
listener.start()

def signalListener():
    while True:
        try:
            cc = str(ser.readline())[2:][:-5]
            with open("output.txt", "a") as f:
                f.write(str(current_milli_time()) + " => " + cc + "\n")
            if cc[0] == '[':
                cansatData = json.loads(cc)
                dataPoints.append([current_milli_time(),cansatData[2]])
                # plt.scatter(ts, cansatData[2])
                # plt.pause(0.001)
                with open("data.txt", "w") as f:
                    f.write((str(dataPoints)))
            else:
                print(cc)
        except:
            print()

signalListenerT = threading.Thread(target=signalListener)
signalListenerT.start()