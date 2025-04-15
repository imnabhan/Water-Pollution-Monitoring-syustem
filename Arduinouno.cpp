#include <OneWire.h>
#include <DallasTemperature.h>

// Define the pin for the turbidity sensor
const int turbidity_pin = A0;
// Define the pin for the pH sensor
const int ph_sensorPin = A1;

// Data wire is connected to pin 2 on the Arduino for DS18B20 temperature sensor
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass oneWire reference to DallasTemperature library
DallasTemperature tempSensors(&oneWire);

float ph_value, sensor_value = 0;

void setup() {
  Serial.begin(9600); // Initialize serial communication
  tempSensors.begin(); // Start up the DallasTemperature library for DS18B20 sensor
}

void loop() {
  // Read temperature from DS18B20 temperature sensor
  tempSensors.requestTemperatures(); // Request temperature readings
  float temperatureCelsius = tempSensors.getTempCByIndex(0);

  // Read pH value from pH sensor
  ph_value = analogRead(ph_sensorPin);
  sensor_value = (ph_value) / 25.0; // Adjust this value based on your pH sensor calibration

  // Read turbidity value
  int turbidity_value = analogRead(turbidity_pin);

  // Send sensor readings to ESP8266
  Serial.print(temperatureCelsius);
  Serial.print(",");
  Serial.print(sensor_value);
  Serial.print(",");
  Serial.println(turbidity_value);

  delay(1000); // Delay for a second before reading again
}

