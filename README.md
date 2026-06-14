# Sensor Site Surveyor: Multi-Linked List ADT for Sensor Data collection

# Usage:
`Usage: ./process <datafile>`

**INPUT FILE FORMAT**:
```
<sector number> <iron> <silicon>
167 241 57
259 22 91
...
```
**OUTPUT FILE FORMAT**:
```
----------------------------------------------------------------------
Data values
----------------------------------------------------------------------
Data by Sector
Sector: #1 183 grams iron, 64 milligrams silicon
Sector: #1 116 grams iron, 15 milligrams silicon
...
Data by Iron Level
Sector: #277 1 grams iron, 5 milligrams silicon
Sector: #406 1 grams iron, 61 milligrams silicon
...
Data by Silicon Level
Sector: #259 468 grams iron, 1 milligrams silicon
Sector: #73 317 grams iron, 1 milligrams silicon
...
----------------------------------------------------------------------
Averages per sector
----------------------------------------------------------------------
Sector: #1 233 grams iron, 49 milligrams silicon
...
Sector: #9 276 grams iron, 51 milligrams silicon
Sector: #10  -- no data -- 
...
----------------------------------------------------------------------
Bad sectors
----------------------------------------------------------------------
10, 20, 30, 50, 70, 80, 120, 130, 140, 150, 190, 200, 210, 220, 230, 240, 260, 280, 300, 320, 330, 380, 390, 400, 410, 420, 430, 440, 450, 460, 470, 500
```

# Purpose
This program reads from a formatted .txt file of sensor data, populates and orders a Multi-Linked List of sensors according to their member values(ie iron and silicon levels), and generates human-readble formatted and ordered lists of the sensor data to another file named `[<inputfile.txt>].out`, according to the 3 different ordering techniques, as well as sector averages(sensors are grouped into sectors) and listings of "bad sectors" - that is, any sector where reading from a sensor from that sector has failed. 
- `small.txt`, `medium.txt`, `large.txt` and `huge.txt` files are provided for demonstration of this program, allowing us to watch performance as the input scales

# File Descriptions:
- `process.cpp` : MAIN main() [depends on datalogger.*]
  Take file to read from as argument, opens the file read reading, creates `data` and `badSectorData` DataLogger objects to handle the sensor data listed in the input file.
  Reads data in a while loop, one param at a time, checking for bad sensor data and respectively placing sensor data in either `data` or `badSectorData` DataLogger objects. 
  After data is read, the `data` DataLogger object is printed via its class member function `printReport()`
  Then, `badsSectorData` is also formatted and outputted via DataLogger class's `printSectorList()` class member function
- `datalogger.*` : [depends on linkedlist.*]
ADT for a DataLogger object containing the ordered Sensor data given by the input file. 
- `linkedlist.h`: [depends on sensordata.*]
  Defines a multi-linked list class object `LinkedList` (ordered in 3 ways: silicon leve, iron level, and sector number) traversable from one of the 3 LL heads. Each data object(`SensorData` object described in `sensordata.*`) only exists once in memory. The ndoes simply reference pointers to where each data object is located in memory. struct `Node` contains the next *`Node` pointer for each of the three list traversal orders, as well as a pointer to the `SensorData` object it is referencing itself. 
- `sensordata.*`: SensorData obj def, set/getters, construct, and op overloading for SensorData objects. Describes what DATA each sensor holds. This is the *data member of a linkedlist node.


**NOTE FOR FUTURE DEV:** I intend to create some integration into and actual HW-base sensor collection network utilizing a collection of sensor nodes made up of some sort of MCU with Wifi or LoRa capabilities(first to thought might be ESP32). The Overall intent of this project is to give a good data collection/management server-side process that deals with a "crop" of sensor sources that exhibit the same characteristics, each sectioned into different sectors of the crop. Ideally, a server would be able to run multiple instances of this process(./process executeable) simultaneously, allowing entire files containing sensor data to be sent, processed on the server side, formatted, and transported elsewhere. But that's a bigger project. We will see if I have time (:
