import sys
import serial

ser = serial.Serial('COM3', baudrate = 115200)
fileName = "sensor_data.csv"

samples = 10 #how many samples to collect
print_labels = False
line = 0 #start at 0 because our header is 0 (not real data)

while line <= samples:
    if print_labels:
        if line==0:
            print("Printing Column Headers")
        else:
            print("Line " + str(line) + ": writing...")
    getData=str(ser.readline())
    data=getData[2:][:-5]
    print(data)

    file = open(fileName, "a")
    file.write(data) #write data with a newline
    file.write("\n")
    line = line+1

print("Data collection complete!")
file.close()