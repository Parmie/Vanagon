import matplotlib.pyplot as plt
import matplotlib.animation

class Plotter:
    arraySize = 100
    counter = 0
    x_axis = []
    batteryVoltage = []

    #def __init__(self):
    #    plt.ion()
    #    plt.title("Vanagon data")
    
    def update(self):
        plt.plot(self.batteryVoltage, label="Battery V")

    def append(self, data):
        self.counter = self.counter + 1
        self.x_axis.append(self.counter)
        self.batteryVoltage.append(data.BatteryVoltage)
        if self.counter > self.arraySize:
            self.x_axis.pop(0)
            self.batteryVoltage.pop(0)