import serial
import serial.tools.list_ports
import time
import sys
import datetime
import matplotlib.pyplot as plt
from dataReader import DataReader
from fileLogger import FileLogger
from plotter import Plotter
from pyLive import live_plotter_xy

dataReader = DataReader("USB-SERIAL CH340 (COM4)")
fileLogger = FileLogger("datalog.csv")
plotter = Plotter()

if dataReader.serialPort == None:
    print("Port not found")
    sys.exit()

line1 = []

try:
    for data in dataReader():
        plotter.append(data)
        line1 = live_plotter_xy(plotter.x_axis, plotter.batteryVoltage, line1)
        fileLogger.append(data)

except KeyboardInterrupt:
    fileLogger.close()
    sys.exit()