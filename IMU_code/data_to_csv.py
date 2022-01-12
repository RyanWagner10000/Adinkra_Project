import csv
import serial

ser = serial.Serial('COM4', baudrate = 57600, timeout = 10)
fileName = "sensor_data.csv"

print_labels = True

f = open(fileName, "a+")
writer = csv.writer(f, delimiter=',')

while True:
    if print_labels:
        print_labels = False
    else:
        print("Line " + str(line) + ": writing...")
    
    s = ser.readline().decode()
    if s != "":
        rows = [float(x) for x in s.split(',')]
        print(rows)
        writer.writerow(rows)
        f.flush()

print("Data collection complete!")