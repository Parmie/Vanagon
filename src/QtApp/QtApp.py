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
    y_list = []

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
        self.drawPlot = self.plot.plot()

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
        print(str(data.BatteryVoltage))  
        self.updateBatteryVoltage(data.BatteryVoltage)

    def updateBatteryVoltage(self, voltage):
        self.counter = self.counter + 1
        self.x_list.append(self.counter)
        self.y_list.append(voltage)

        if (self.counter > self.arrayLength):
            self.x_list.pop(0)
            self.y_list.pop(0)

        self.drawPlot.setData(self.x_list, self.y_list)

if __name__ == "__main__":
    app = QApplication([])
    form = MainForm()
    form.show()
    sys.exit(app.exec_())