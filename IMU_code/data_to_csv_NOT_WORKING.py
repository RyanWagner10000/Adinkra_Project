import csv
import serial

ser = serial.Serial('COM4', baudrate = 57600, timeout = 10)
fileName = "sensor_data2.csv"

print_labels = True

with open(fileName, 'w+') as f:
    while True:
        s = ser.readline()
        print(s)
        print(type(s))

print("Data collection complete!")