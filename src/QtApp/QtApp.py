import sys
import threading
from PyQt5.QtCore import QThread, pyqtSlot
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QLabel
import pyqtgraph as pg
from DataReader import DataReader, VanagonData

class MainForm(QWidget):
    arrayLength = 100
    counter = 0
    x_list = []
    plotdata_battery = []
    plotData_lambda = []
    plotdata_airFlow = []

    def __init__(self):
        super().__init__()

        self.setWindowTitle("Vanagon engine monitor")
        self.resize(500, 400)
        layout = QVBoxLayout(self)

        label = QLabel()
        label.setText("Test")
        self.layout().addWidget(label)

        self.canvas = pg.GraphicsLayoutWidget()
        self.layout().addWidget(self.canvas)

        self.plot = self.canvas.addPlot()
        self.plot.showGrid(True, True)
        self.plot.setYRange(0, 15)
        self.batteryPlot = self.plot.plot()
        self.lambdaPlot = self.plot.plot()

        self.canvas.nextRow()

        self.plot2 = self.canvas.addPlot()
        self.plot2.showGrid(True, True)
        self.plot2.setYRange(0, 1)
        self.airFlowPlot = self.plot2.plot()

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

        if (self.counter > self.arrayLength):
            self.x_list.pop(0)
            self.plotdata_battery.pop(0)
            self.plotData_lambda.pop(0)
            self.plotdata_airFlow.pop(0)

        self.batteryPlot.setData(self.x_list, self.plotdata_battery)
        self.lambdaPlot.setData(self.x_list, self.plotData_lambda)
        self.airFlowPlot.setData(self.x_list, self.plotdata_airFlow)

if __name__ == "__main__":
    app = QApplication([])
    form = MainForm()
    form.show()
    sys.exit(app.exec_())