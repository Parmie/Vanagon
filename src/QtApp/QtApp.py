import sys
import threading
from PyQt5.QtCore import QThread, pyqtSlot, Qt
from PyQt5.QtWidgets import QApplication, QWidget, QHBoxLayout, QVBoxLayout, QLabel
import pyqtgraph as pg
from DataReader import DataReader, VanagonData

class MainForm(QWidget):
    arrayLength = 100
    counter = 0
    x_list = []
    plotdata_battery = []
    plotData_lambda = []
    plotdata_airFlow = []
    plotdata_airTemp = []
    plotdata_coolantTemp = []
    plotdata_oilPressure = []
    plotdata_oilPressureHigh = []
    plotdata_oilPressureLow = []
    plotdata_fuelLevel = []
    plotdata_revolutions = []

    def __init__(self):
        super().__init__()

        self.setWindowTitle("Vanagon engine monitor")
        palette = self.palette()
        palette.setColor(self.backgroundRole(), Qt.black)
        self.setPalette(palette)
        self.resize(500, 400)
        layout = QHBoxLayout(self)

        label = QLabel()
        palette = label.palette()
        palette.setColor(self.foregroundRole(), Qt.white)
        label.setPalette(palette)
        label.setText("Test")
        self.layout().addWidget(label)

        self.canvas = pg.GraphicsLayoutWidget()
        self.layout().addWidget(self.canvas)

        self.plot = self.canvas.addPlot(title="Battery Voltage")
        self.plot.showGrid(True, True)
        self.plot.setYRange(0, 15)
        self.batteryPlot = self.plot.plot(pen="r")

        #self.canvas.nextRow()

        self.plot2 = self.canvas.addPlot(title="O2 Voltage")
        self.plot2 .showGrid(True)
        self.plot2.setYRange(0, 1)
        self.plot2.setXLink(self.plot)
        self.lambdaPlot = self.plot2.plot(pen="y")

        self.canvas.nextRow()

        self.plot3 = self.canvas.addPlot(title="Air Flow")
        self.plot3.showGrid(True, True)
        self.plot3.setYRange(0, 1)
        self.plot3.setXLink(self.plot2)
        self.airFlowPlot = self.plot3.plot()

        #self.canvas.nextRow()

        self.plot4 = self.canvas.addPlot(title="Air Temperature")
        self.plot4.showGrid(True, True)
        self.plot4.setYRange(0, 40)
        self.plot4.setXLink(self.plot3)
        self.airTempPlot = self.plot4.plot()

        self.canvas.nextRow()

        self.plot5 = self.canvas.addPlot(title="Coolant Temperature")
        self.plot5.showGrid(True, True)
        self.plot5.setYRange(0, 120)
        self.plot5.setXLink(self.plot4)
        self.coolantTempPlot = self.plot5.plot()

        #self.canvas.nextRow()

        self.plot6 = self.canvas.addPlot(title="Oil Pressure")
        self.plot6.showGrid(True, True)
        self.plot6.setYRange(0, 5)
        self.plot6.setXLink(self.plot5)
        self.oilPressurePlot = self.plot6.plot()
        self.oilPressureHighPlot = self.plot6.plot(pen="y")
        self.oilPressureLowPlot = self.plot6.plot(pen="r")

        self.canvas.nextRow()

        self.plot7 = self.canvas.addPlot(title="Fuel Level")
        self.plot7.showGrid(True, True)
        self.plot7.setYRange(0, 70)
        self.plot7.setXLink(self.plot6)
        self.fuelLevelPlot = self.plot7.plot()

        #self.canvas.nextRow()

        self.plot8 = self.canvas.addPlot(title="Camshaft Revolutions")
        self.plot8.showGrid(True, True)
        self.plot8.setYRange(0, 10000)
        self.plot8.setXLink(self.plot7)
        self.revolutionsPlot = self.plot8.plot()

        self.dataReader = DataReader("USB-SERIAL CH340 (COM4)")
        if self.dataReader.serialPort == None:
            sys.exit()
            return
        
        self.thread = QThread()
        self.dataReader.moveToThread(self.thread)
        self.dataReader.dataReceived.connect(self.dataReceived)
        self.thread.started.connect(self.dataReader.run)
        self.thread.finished.connect(app.exit)
        self.thread.start()
    
    @pyqtSlot(VanagonData)
    def dataReceived(self, data):        
        self.counter = self.counter + 1
        self.x_list.append(self.counter)
        self.plotdata_battery.append(data.BatteryVoltage)
        self.plotData_lambda.append(data.O2Voltage)
        self.plotdata_airFlow.append(data.AirFlowPercentage)
        self.plotdata_airTemp.append(data.AirTemperature)
        self.plotdata_coolantTemp.append(data.CoolantTemperature)
        self.plotdata_oilPressure.append(data.OilPressure)
        self.plotdata_oilPressureHigh.append(0.9 if data.OilPressureHighAlarm else -100)
        self.plotdata_oilPressureLow.append(0.3 if data.OilPressureLowAlarm else -100)
        self.plotdata_fuelLevel.append(data.FuelLevel)
        self.plotdata_revolutions.append(data.CamshaftRevolutions)

        if (self.counter > self.arrayLength):
            self.x_list.pop(0)
            self.plotdata_battery.pop(0)
            self.plotData_lambda.pop(0)
            self.plotdata_airFlow.pop(0)
            self.plotdata_airTemp.pop(0)
            self.plotdata_coolantTemp.pop(0)
            self.plotdata_oilPressure.pop(0)
            self.plotdata_oilPressureHigh.pop(0)
            self.plotdata_oilPressureLow.pop(0)
            self.plotdata_fuelLevel.pop(0)
            self.plotdata_revolutions.pop(0)

        self.batteryPlot.setData(self.x_list, self.plotdata_battery)
        self.lambdaPlot.setData(self.x_list, self.plotData_lambda)
        self.airFlowPlot.setData(self.x_list, self.plotdata_airFlow)
        self.airTempPlot.setData(self.x_list, self.plotdata_airTemp)
        self.coolantTempPlot.setData(self.x_list, self.plotdata_coolantTemp)
        self.oilPressurePlot.setData(self.x_list, self.plotdata_oilPressure)
        self.oilPressureHighPlot.setData(self.x_list, self.plotdata_oilPressureHigh)
        self.oilPressureLowPlot.setData(self.x_list, self.plotdata_oilPressureLow)
        self.fuelLevelPlot.setData(self.x_list, self.plotdata_fuelLevel)
        self.revolutionsPlot.setData(self.x_list, self.plotdata_revolutions)

arraySize = 100

class Plot(pg.PlotItem):
    def __init__(self, title=None):
        super().__init__(title=title)
        self.values = []
        self.plot = self.plot()

    def update(self, value):
        pass

class BatteryVoltageplot(Plot):
    def __init__(self):
        super().__init__(title="Battery Voltage")
        self.values = []

if __name__ == "__main__":
    app = QApplication([])
    form = MainForm()
    form.showFullScreen()
    sys.exit(app.exec_())