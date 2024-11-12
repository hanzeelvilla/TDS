# TDS Library

This library is used to measure Total Dissolved Solids (TDS) in water, typically with an Arduino or ESP32-based system. It provides functionality to read and calculate TDS levels using a connected TDS sensor and compensates for water temperature.

## Features
* Calculates TDS in parts per million (ppm)
* Temperature compensation for accurate readings
* Supports reading from an analog sensor pin
* Includes methods for median filtering for noise reduction

## Installation

1. Download the repository as a ZIP file or clone it to your Arduino libraries folder

```
git clone https://github.com/hanzeelvilla/TDS.git
```

2. Place the TDS folder into your Arduino libraries directory (typically Documents/Arduino/libraries on most systems).
3. Restart the Arduino IDE if it was open during installation.

## Getting started

### Initialize the TDS Sensor
To use the library, create a TDS object, specifying:

* The analog pin where the sensor is connected.
* The reference voltage (default is 5V; for ESP32, use 3.3V if that is your board's reference voltage).

```
#include <TDS.h>

TDS tds(27, 3.3);  // Example with ESP32 (3.3V)
```

### Initialize the Sensor with init()
Before taking readings, call init() in the setup() function to configure the sensor pin as an input. This method also sends a message to the Serial Monitor confirming that the TDS sensor is initialized.

```
void setup() {
  Serial.begin(115200);
  tds.init();  // Initializes the TDS sensor and sets the pin as input
}
```

### Take a Reading with read()
The primary function of this library is to take a TDS reading. The **read()** method reads the analog value, applies a median filter for stability, compensates for temperature, and then converts the result to a TDS value in parts per million (ppm).

* Parameter: temperature (optional) — The water temperature in degrees Celsius, which adjusts the reading for accuracy. If not specified, the default temperature is 25°C.
* Return: A TDSData structure

```
void loop() {
  // Assuming a water temperature of 20°C; update this value if you have a temperature sensor
  TDSData tds_data = tds.read(20);

  // Print TDS data to the Serial Monitor
  Serial.print("TDS Value: ");
  Serial.print(tds_data.ppm);
  Serial.println(" ppm");

  delay(200);  // Small delay between readings
}
```

### TDSData Structure
* **averageVoltage**: Average sensor voltage.
* **compensationCoefficient**: Compensation factor based on temperature.
* **compensationVoltage**: Temperature-adjusted voltage.
* **ppm**: TDS value in ppm.

## Methods
* **init():** Initializes the TDS sensor pin and prints a confirmation message to the serial monitor.
* **info():** Outputs the sensor configuration details (pin and reference voltage) to the serial monitor.
* **read(float temperature):** Reads data from the sensor, calculates the TDS value in ppm, and returns it as a TDSData structure. Temperature can be specified to adjust the compensation * coefficient for more accurate readings.
