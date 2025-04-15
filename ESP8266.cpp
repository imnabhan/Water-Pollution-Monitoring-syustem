#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "Nura";
const char* password = "Nura7777";
const char* server = "api.thingspeak.com";
const String apiKey = "8JMODAEBK4JA8L4A";

void setup() {
  Serial.begin(9600); // Initialize serial communication with Arduino Uno
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}

void loop() {
  // Check if data is available to read
  if (Serial.available()) {
    // Read data from Arduino Uno
    String dataFromArduino = "";
    char character;
    while (true) {
      character = Serial.read();
      if (character == '\n') {
        break;
      }
      dataFromArduino += character;
    }
    dataFromArduino.trim(); // Remove leading and trailing whitespace

    Serial.println("Data from Arduino: " + dataFromArduino);

    // Split the data into individual values
    int commaIndex1 = dataFromArduino.indexOf(',');
    int commaIndex2 = dataFromArduino.indexOf(',', commaIndex1 + 1);
    String temperature = dataFromArduino.substring(0, commaIndex1);
    String turbidity = dataFromArduino.substring(commaIndex1 + 1, commaIndex2);
    String pH = dataFromArduino.substring(commaIndex2 + 1);

    // Connect to ThingSpeak
    WiFiClient client;
    if (client.connect(server, 80)) {
      // Construct URL for ThingSpeak update
      String url = "/update?api_key=" + apiKey + "&field1=" + temperature + "&field2=" + turbidity + "&field3=" + pH;

      // Send HTTP GET request to ThingSpeak
      Serial.print("Sending data to ThingSpeak: ");
      Serial.println(url);
      client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                   "Host: " + server + "\r\n" +
                   "Connection: close\r\n\r\n");
      delay(1000);  // Wait for response
      Serial.println("Data sent to ThingSpeak");
    } else {
      Serial.println("Connection to ThingSpeak failed...");
    }
  }

  // Wait before sending next update
  delay(5000); // Update interval (in milliseconds)
}