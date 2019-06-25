import serial
import time
import sys
import datetime

class Arduino:
    CycleTime=0
    ReferenceVoltage=0

class VanagonData:
    BatteryVoltage=0
    O2Voltage=0
    AirFlowPercentage=0
    AirTemperature=0
    CoolantTemperature=0
    OilPressure=0
    OilPressureLowAlarm=False
    OilPressureHighAlarm=False
    FuelLevel=0
    CamshaftRevolutions=0

ser = serial.Serial('COM4', baudrate = 9600, timeout=1)
file = open("datalog.csv", "w")
file.write("sep=;\n")
file.write("TimeStamp; CycleTime; ReferenceVoltage; BatteryVoltage; O2Voltage; AirFlowPercentage; AirTemperature; CoolantTemperature; OilPressure; OilPressureLowAlarm; OilPressureHighAlarm; FuelLevel; CamShaftRevolutions\n")
time.sleep(3)

while 1:
    try:
        arduinoData = ser.readline().decode('ascii')
        print(arduinoData, end="")
        values = arduinoData.split(" ")
        page = int(values[0])
        if page == 0:
            arduino = Arduino()
            arduino.CycleTime = int(values[1])
            arduino.ReferenceVoltage = float(values[12])

            data = VanagonData()
            data.BatteryVoltage = float(values[2])
            data.O2Voltage = float(values[3])
            data.AirFlowPercentage = float(values[4])
            data.AirTemperature = float(values[5])
            data.CoolantTemperature = float(values[6])
            data.OilPressure = float(values[7])
            data.OilPressureLowAlarm = int(values[8]) > 0
            data.OilPressureHighAlarm = int(values[9]) > 0
            data.FuelLevel = float(values[10])
            data.CamshaftRevolutions = int(values[11])

            file.write(str(datetime.datetime.utcnow()) + ";" + str(arduino.CycleTime) + ";" + str(arduino.ReferenceVoltage) + ";" + str(data.BatteryVoltage) + ";" + str(data.O2Voltage) + ";" + str(data.AirFlowPercentage) + ";" + str(data.AirTemperature) + ";" + str(data.CoolantTemperature) + ";" + str(data.OilPressure) + ";" + str(data.OilPressureLowAlarm) + ";" + str(data.OilPressureHighAlarm) + ";" + str(data.FuelLevel) + ";" + str(data.CamshaftRevolutions) + "\n")

            #print(data)
        else:
            print("Page " + str(page))
    except UnicodeDecodeError:
        print("Read error")
    except ValueError:
        print("Parsing error")
    except KeyboardInterrupt:
        file.close()
        sys.exit()