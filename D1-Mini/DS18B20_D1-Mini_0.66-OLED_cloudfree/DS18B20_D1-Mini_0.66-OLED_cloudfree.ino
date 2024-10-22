#include <U8x8lib.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Initialize the U8x8 library for SSD1306 64x48 OLED display using I2C
U8X8_SSD1306_64X48_ER_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL, /* data=*/ SDA);

// DS18B20 Temperature Sensor Pin
#define ONE_WIRE_PIN D2
OneWire oneWire(ONE_WIRE_PIN);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);
  
  // Initialize the display
  u8x8.begin();
  
  // Set the font to a bold font, readable on small displays
  u8x8.setFont(u8x8_font_victoriabold8_r);

  // Start the DS18B20 sensor
  sensors.begin();
}

void loop() {
  // Request temperature from DS18B20 sensor
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);  // Get temperature in Celsius
  float tempK = tempC + 273.15;              // Convert Celsius to Kelvin

  // Clear the display
  u8x8.clearDisplay();

  u8x8.setCursor(0, 0);
  u8x8.print("Temperature:");
  u8x8.setCursor(0, 2);
  u8x8.print(tempC, 1);  // Print Celsius with 1 decimal
  u8x8.print(" \xB0""C"); // \xB0 is the degree symbol in ASCII for displays


  // Display temperature in Kelvin
  u8x8.setCursor(0, 4);
  u8x8.print(tempK, 1);  // Print Kelvin with 1 decimal
  u8x8.print("K");

  // Wait 2 seconds before the next update
  delay(2000);
}
