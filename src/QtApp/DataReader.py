import serial
import serial.tools.list_ports
import time
from PyQt5.QtCore import QObject, pyqtSignal

class VanagonData:
    CycleTime = 0
    ReferenceVoltage = 0
    BatteryVoltage = 0
    O2Voltage = 0
    AirFlowPercentage = 0
    AirTemperature = 0
    CoolantTemperature = 0
    OilPressure = 0
    OilPressureLowAlarm = False
    OilPressureHighAlarm = False
    FuelLevel = 0
    CamshaftRevolutions = 0

class DataReader(QObject):
    serialPort = None

    dataReceived = pyqtSignal(VanagonData)
    finished = pyqtSignal()

    def __init__(self, portName):
        super().__init__()

        # Find the COM port
        ports = serial.tools.list_ports.comports()
        for port in ports:
            print(port.description)
            if port.description == portName:
                print("Arduino found on " + port.device)
                self.serialPort = serial.Serial(port.device, baudrate=9600, timeout=1)
        #
        if self.serialPort != None:
            time.sleep(3)

    def run(self):
        if self.serialPort == None:
            self.finished.emit()

        while 1:
            try:
                arduinoData = self.serialPort.readline().decode('ascii')
                #print(arduinoData, end="")
                values = arduinoData.split(" ")
                page = int(values[0])
                if page == 0:
                    data = VanagonData()
                    data.CycleTime = int(values[1])
                    data.ReferenceVoltage = float(values[12])
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

                    self.dataReceived.emit(data)

                    #file.write(str(datetime.datetime.utcnow()) + ";" + str(arduino.CycleTime) + ";" + str(arduino.ReferenceVoltage) + ";" + str(data.BatteryVoltage) + ";" + str(data.O2Voltage) + ";" + str(data.AirFlowPercentage) + ";" + str(data.AirTemperature) + ";" + str(data.CoolantTemperature) + ";" + str(data.OilPressure) + ";" + str(data.OilPressureLowAlarm) + ";" + str(data.OilPressureHighAlarm) + ";" + str(data.FuelLevel) + ";" + str(data.CamshaftRevolutions) + "\n")

                    #print(data)
                    #append(batteryVoltage, data.BatteryVoltage)
                else:
                    print("Page " + str(page))
            except UnicodeDecodeError:
                print("Read error")
            except ValueError:
                print("Parsing error")
            except serial.SerialException:
                self.finished.emit()