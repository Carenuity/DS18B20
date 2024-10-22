#include <Wire.h>
#include <SSD1306Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Initialize the OLED display using the ThingPulse SSD1306 library
#define SCREEN_ADDRESS 0x3C
SSD1306Wire display(SCREEN_ADDRESS, SDA, SCL, GEOMETRY_64_48);

// DS18B20 Temperature Sensor Pin
#define ONE_WIRE_PIN 7  // GPIO8 for ESP32-C3 Mini
OneWire oneWire(7);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);

  // Initialize the display
  display.init();
  display.flipScreenVertically();
  display.clear();
  display.setFont(ArialMT_Plain_10); // Use a readable font

  // Start the DS18B20 sensor
  sensors.begin();
}

void loop() {
  // Request temperature from DS18B20 sensor
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);  // Get temperature in Celsius
  float tempK = tempC + 273.15;              // Convert Celsius to Kelvin

  // Clear the display
  display.clear();

  // Display temperature in Celsius with 1 decimal place and the degree symbol
  display.drawString(0, 0, "Temperature:");
  display.drawString(8, 16, String(tempC, 1) + " \xB0""C");
  display.drawString(8, 30, String(tempK, 1) + "K");  // Print Kelvin with 1 decimal

  // Display the buffer contents on the screen
  display.display();

  // Wait 2 seconds before the next update
  delay(2000);
}
