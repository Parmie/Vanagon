# Digifant

| Pin  |       | Description                                                                                             |
| :--- | :---: | :------------------------------------------------------------------------------------------------------ |
| 1    |  12V  | Starter signal from contact. +12V IN when key is turned and starter is activated.                       |
| 2    |  1V   | Oxygen sensor                                                                                           |
| 3    |       | + OUT Fuel pump relay                                                                                   |
| 4    |       | X                                                                                                       |
| 5    |       | X                                                                                                       |
| 6    |  GND  | Ground for sensors (hall generator, trottle switch, coolant temperature, intake air temperature & flow) |
| 7    |       | X                                                                                                       |
| 8    |       | Hall generator.                                                                                         |
| 9    |  5V   | Air temperature sensor.                                                                                 |
| 10   |  5V   | Coolant temperature sensor.                                                                             |
| 11   |  5V   | Throttle valve switch. 4.9V when open. 0V when closed.                                                  |
| 12   |       | Fuel injectors                                                                                          |
| 13   |  GND  | Ground connection for Digifant. Connected to chassis.                                                   |
| 14   |       | Power for Digifant. From battery, switched by key contact.                                              |
| 15   |       | X                                                                                                       |
| 16   |       | X                                                                                                       |
| 17   |  5V   | Power for air temperature & flow sensor. Internal resistor of 10 ohms.                                  |
| 18   |  12V  | Hall generator signal. Normal 12V, 0V signal 4x per rotation.                                           |
| 19   |  GND  | connection on engine block.                                                                             |
| 20   |       | Serial interface? Connection should be under the instrument cluster.                                    |
| 21   |  5V   | Air flow sensor.                                                                                        |
| 22   |       | X                                                                                                       |
| 23   |       | X                                                                                                       |
| 24   |       | X                                                                                                       |
| 25   |       | OUT Ignition coil.                                                                                      |

## Starter signal
Digital pin 1: +12V when key is turned to start the engine. Floating when not.
Digifant:
 - Limited to 3.5V
 - Pull-up to 1.23V
 - R = 18,94K

## Oxygen sensor
Analog pin 2: +1V. < 0.25V = rich; > 0.75V = lean

## Fuel pump

## Hall sensor

## Air temperature
Analog pin 9: 5V
NTC - same specs as coolant temperature

## Air flow meter

## Coolant temperature
Analog pin 10: 5V
NTC
R25: 2041
beta: 3545
divider resistance: 8.25ko
voltage can't go over 5V
voltage can go over 4.1V when temp below -30

## Throttle switch
Digital pin 11: 5V
Open: 4.91V
Closed: 0V

## Fuel injectors

## Ignition

## Battery voltage
Arduino:
  - pin A0


## Diagnostics


## Oil pressure

# Dashboard

## Temperature
### Sensor
Part nr: 049-919-501
|   Temp | Resistance |
| -----: | ---------: |
|  -20°C |   6500 ohm |
|    0°C |   2500 ohm |
|   20°C |   1000 ohm |
|   40°C |    450 ohm |
|   60°C |    250 ohm |
|   80°C |    140 ohm |
| 100 °C |    100 ohm |

## Fuel level
### Sender
