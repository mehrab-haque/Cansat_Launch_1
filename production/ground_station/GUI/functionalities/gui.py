import sys
from PyQt5 import QtCore, QtWidgets
from PyQt5.QtWidgets import QMainWindow, QLabel, QGridLayout, QWidget
from PyQt5.QtWidgets import QPushButton
from PyQt5.QtCore import QSize
import serial
import json
import matplotlib.pyplot as plt
import time
import threading

import time

def current_milli_time():
    return round(time.time() * 1000)

ser = serial.Serial("COM3", 9600)


class MainWindow(QMainWindow):
    def __init__(self):
        QMainWindow.__init__(self)

        self.setMinimumSize(QSize(200, 250))
        self.setWindowTitle("Spacelab")

        pybutton = QPushButton('Launch', self)
        pybutton.clicked.connect(self.launch)
        pybutton.resize(100,32)
        pybutton.move(50, 50)

        pybutton = QPushButton('Eject', self)
        pybutton.clicked.connect(self.eject)
        pybutton.resize(100, 32)
        pybutton.move(50, 100)

        pybutton = QPushButton('Rocket Grounded', self)
        pybutton.clicked.connect(self.rocket_grounded)
        pybutton.resize(100, 32)
        pybutton.move(50, 150)

        pybutton = QPushButton('Cansat Grounded', self)
        pybutton.clicked.connect(self.cansat_grounded)
        pybutton.resize(100, 32)
        pybutton.move(50, 200)

    def launch(self):
        with open("output.txt", "a") as f:
            f.write((str(current_milli_time()) + " => launched\n"))
            print("launch confirmed...")
    def eject(self):
        ser.write("eeeeeeeeeeeeeeee".encode())
    def rocket_grounded(self):
        with open("output.txt", "a") as f:
            f.write((str(current_milli_time()) + " => rocket grounded\n"))
            print("rocket grounded confirmed...")
    def cansat_grounded(self):
        with open("output.txt", "a") as f:
            f.write((str(current_milli_time()) + " => cansat grounded\n"))
            print("cansat grounded confirmed...")



def gui():
    app = QtWidgets.QApplication(sys.argv)
    mainWin = MainWindow()
    mainWin.show()
    sys.exit(app.exec_())

listener = threading.Thread(target=gui)
#listener.start()
while True:
    try:
        cc = str(ser.readline())[2:][:-5]
        with open("output.txt", "a") as f:
            f.write(str(current_milli_time()) + " => " + cc + "\n")
        if cc[0] == '[':
            cansatData = json.loads(cc)
            ts = time.time()
            plt.scatter(ts, cansatData[2])
            plt.pause(0.001)
        else:
            print(cc)
    except:
        print()
plt.show()



