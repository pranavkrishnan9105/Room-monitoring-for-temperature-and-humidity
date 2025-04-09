#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h> // Use the Adafruit DHT library

LiquidCrystal_I2C lcd(0x27, 20, 4);
#define DHT11_PIN 5 // Use the correct GPIO pin for NodeMCU (D5 = GPIO14)

DHT DHT(DHT11_PIN, DHT11); // Initialize DHT object

void setup() 
{
  pinMode(7, OUTPUT); // Set buzzer pin as OUTPUT
  Serial.begin(9600); // Initialize Serial communication
  DHT.begin(); // Initialize DHT sensor
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("DHT11 SENSOR");
  delay(800);
}

void loop() 
{
  float humidity = DHT.readHumidity(); // Read humidity
  float temperature = DHT.readTemperature(); // Read temperature in Celsius

  // Check if readings are valid
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print data to Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(humidity, 1);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature, 1);
  Serial.println(" °C");

  // Display data on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("H: ");
  lcd.print(humidity, 1);
  lcd.print(" %");

  lcd.setCursor(0, 1);
  lcd.print("T: ");
  lcd.print(temperature, 1);
  lcd.print(" C");

  // Check for high temperature
  if (temperature >= 35) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("HIGH TEMP!");
    digitalWrite(7, HIGH); // Turn on buzzer
    delay(2000); // Wait for 2 seconds
    digitalWrite(7, LOW); // Turn off buzzer
  }

  delay(800); // Delay between readings
}