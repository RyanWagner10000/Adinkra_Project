# Adinkra_Project

### Task 1: Create a ...
- Camera mount that incorporates the OAK-D stereo depth camera
- Rotates about the Y- and Z- axis
- Has a locking mechanism
- Parts are 3D printable
- Applied magnetically without slipping

### Task 2: Develop a program that ...
- Records time-stamped IMU data 
- Saves it to a .csv file
- Done via Serial or WiFi
- On a MCU & IMU of choosing
---

## Solution
### Task 1
All individual mount parts can be seen in the "Mount_Parts" file, as well as a complete assembly on the magnetic camera mount. The "BOM" Excel file can be used to easily identify what materials went/will go into the design, the price, the quantity, and where to acquire said item.  
SolidWorks was used to design all the parts. The Bill of Materials covers the time, material length and weight, and cost of 3D printing the parts.  
A 30lb, rubberized, square magnet was used because it was thought to be strong enough to withstand knocks/bumps in its environment. A rubber coating was included to provide better protection against the elements, and make it less prone to slippage on its applied surface. A small cutout was included on the base of the mount to make it easier to remove from a metal surface.

### Task 2
The components used were:
- 1x Adafruit Feather HUZZAH ESP8266
- 1x Adafruit PCF8523 RTC (Real-Time Clock)
- 1x Adafruit TDK InvenSense ICM-20948 9-DoF IMU (Internial Measurements Unit)
- 1x Breadboard
- 2x buttons
- 2x 10kOhm resistors
- Numerous jumper wires

#### Starting Point
1. Follow the instructions on the Adafruit website to install all the drivers for the Feather HUZZAH, and get it set-up in the Arduino IDE environment 
    - <https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/using-arduino-ide>
2. Reference the Adafruit IMU and RTC websites, and Aruino Button website for wiring and Arduino IDE library installation(s). A picture and .fzz (Fritzing) file are included in the project to help with wiring
    - RTC: <https://learn.adafruit.com/adafruit-pcf8523-real-time-clock>
    - IMU: <https://learn.adafruit.com/adafruit-tdk-invensense-icm-20948-9-dof-imu>
    - Button: <https://www.arduino.cc/en/pmwiki.php?n=Tutorial/Button>
        - There are two buttons in this build. One (the inner button) was used to start and stop the data being read/printed, and the other (outer) was used to stop the program all together
3. After the Arduino IDE is successfully installed along with the neccessary drivers and libraries for the components, open the "IMU_Code" folder. You can test each individual component using the example files provided
    - The "micropython" file can be ignored for now
    - If you wish to test the internet of the HUZZAH using the "wifi_test" file, make sure you have it connected to a 2.4 GHz network, or else it can take 3-5 min to connect with a 2.4/5 GHz network
    - The Wifi data collector is still in the works
4. Follow the directions on this website to install a Serial Output to CSV tool for the Aruduino IDE
    - Website: <https://circuitjournal.com/arduino-serial-to-spreadsheet>
    - Helpful Video: <https://www.youtube.com/watch?v=rT1CIa-ZiNo>
5. If you are satisfied with the components functionality, open up the data_collection file, compile, and run it. It may take 20-40 sec to upload, that is dependent on the type of cable and USB port being used
6. Once running, open the Serial Monitor and/or the ArduSpreadsheet tool. If the ArduSpreadshet is open, click the "Start" button in the bottom right corner. Then, press the button wired to begin printing data (Mine is the inner button)
    - The time interval can be easily changed in the Arduino script to be faster or slower
7. Once enough data is collected, stop the ArduSpreadsheet tool and save/append the data to a csv file
    - Make sure the baudrate is 57600 for the Serial Monitor, IDE, Script, and Ardu-tool
    - Make sure the column seperator is set to ','(comma)