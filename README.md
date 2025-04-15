# IoT Water Quality Monitoring System

This project implements a basic IoT system for monitoring water quality parameters: temperature, pH, and turbidity. It utilizes an Arduino Uno for sensor data acquisition and an ESP8266 for Wi-Fi connectivity and data transmission to the ThingSpeak cloud platform.

## Overview

The system works by:

1.  **Data Acquisition (Arduino Uno):** The Arduino Uno reads data from connected sensors:
    * A DS18B20 temperature sensor.
    * A pH sensor (analog output).
    * A turbidity sensor (analog output).
2.  **Serial Communication (Arduino Uno to ESP8266):** The Arduino Uno sends the sensor readings (temperature, a processed pH-related value, and raw turbidity) sequentially over its serial port, separated by commas and ending with a newline character.
3.  **Wi-Fi Connectivity and Data Transmission (ESP8266):**
    * The ESP8266 connects to a specified Wi-Fi network.
    * It listens for incoming serial data from the Arduino Uno.
    * Upon receiving a complete set of sensor readings, it parses the individual values.
    * It then sends this data to the ThingSpeak platform using HTTP GET requests, updating specific fields in a designated ThingSpeak channel.
4.  **Cloud Data Storage and Visualization (ThingSpeak):** The sensor data is stored on the ThingSpeak cloud, where it can be visualized using charts and further analyzed.

## Hardware Components

* Arduino Uno
* ESP8266 (e.g., ESP-01)
* DS18B20 Temperature Sensor
* pH Sensor (with analog output)
* Turbidity Sensor (with analog output)
* Connecting wires

## Software Components

* **Arduino Uno Code (`.cpp`):** Reads sensor data and sends it serially. Requires the `OneWire` and `DallasTemperature` libraries.
* **ESP8266 Code (`.cpp`):** Connects to Wi-Fi, receives serial data, and transmits it to ThingSpeak. Requires the `ESP8266WiFi` and `WiFiClient` libraries.

## Setup Instructions

1.  **Hardware Connections:** Connect the sensors to the Arduino Uno according to the pin definitions in the Arduino code (turbidity sensor to A0, pH sensor to A1, DS18B20 data wire to digital pin 2). Connect the serial communication pins (TX and RX) of the Arduino Uno to the corresponding RX and TX pins of the ESP8266 (ensure proper voltage level shifting if necessary).
2.  **Arduino IDE Setup:**
    * Install the Arduino IDE.
    * Install the `OneWire` and `DallasTemperature` libraries through the Arduino Library Manager.
    * Upload the `arduino_code.cpp` (rename your Arduino file accordingly) to the Arduino Uno.
3.  **ESP8266 IDE Setup:**
    * Install the ESP8266 board support in the Arduino IDE (if not already installed).
    * Install the `ESP8266WiFi` library through the Arduino Library Manager.
    * **Configure Wi-Fi Credentials:** Open the `esp8266_code.cpp` (rename your ESP8266 file accordingly) and replace `"Nura"` with your Wi-Fi SSID and `"Nura7777"` with your Wi-Fi password.
    * **Configure ThingSpeak API Key:** Replace `"8JMODAEBK4JA8L4A"` with your ThingSpeak Write API Key.
    * Upload the `esp8266_code.cpp` to the ESP8266.
4.  **ThingSpeak Setup:**
    * Create a free account on [ThingSpeak](https://thingspeak.com/).
    * Create a new channel.
    * Configure at least three fields in your channel to store temperature, turbidity, and pH values.
    * Note down your channel's Write API Key, which you will need to put in the ESP8266 code.

## Important Notes

* **pH Calibration:** The pH reading in the Arduino code (`sensor_value = (ph_value) / 25.0;`) is a simplified conversion and likely requires proper calibration with pH buffer solutions to obtain accurate pH values. Refer to the datasheet and calibration instructions for your specific pH sensor.
* **Turbidity Calibration:** Similarly, the raw analog reading from the turbidity sensor needs to be calibrated to meaningful units (e.g., NTU) based on the sensor's characteristics and your application requirements.
* **Serial Communication:** Ensure the baud rate is consistent (9600) in both the Arduino and ESP8266 code.
* **Power Supply:** Provide stable and appropriate power to both the Arduino Uno and the ESP8266.

## Further Development

* Implement proper calibration for pH and turbidity sensors.
* Add more sensors to monitor other water quality parameters.
* Implement error handling and data validation.
* Explore different data visualization and analysis options on ThingSpeak or other platforms.
* Consider using more robust communication protocols (e.g., MQTT) for larger-scale deployments.
