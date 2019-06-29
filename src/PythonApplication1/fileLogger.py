import datetime

class FileLogger:
    file = None

    def __init__(self, path):
        # Prepare a log file
        self.file = open(path, "w")
        self.file.write("sep=;\n")
        self.file.write("TimeStamp; CycleTime; ReferenceVoltage; BatteryVoltage; O2Voltage; AirFlowPercentage; AirTemperature; CoolantTemperature; OilPressure; OilPressureLowAlarm; OilPressureHighAlarm; FuelLevel; CamShaftRevolutions\n")
        #

    def close(self):
        if self.file != None:
            self.file.clos()

    def append(self, data):
        self.file.write(str(datetime.datetime.utcnow()) + ";" + str(data.CycleTime) + ";" + str(data.ReferenceVoltage) + ";" + str(data.BatteryVoltage) + ";" + str(data.O2Voltage) + ";" + str(data.AirFlowPercentage) + ";" + str(data.AirTemperature) + ";" + str(data.CoolantTemperature) + ";" + str(data.OilPressure) + ";" + str(data.OilPressureLowAlarm) + ";" + str(data.OilPressureHighAlarm) + ";" + str(data.FuelLevel) + ";" + str(data.CamshaftRevolutions) + "\n")