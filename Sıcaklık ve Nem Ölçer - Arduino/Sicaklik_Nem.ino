#include <FaBoLCD_PCF8574.h>
#include <Wire.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

FaBoLCD_PCF8574 lcd;


void setup() {

  lcd.begin(16,2);
  lcd.print("Robotisan.com");
  delay(1000);
  dht.begin();

}

void loop() {

  int temp = dht.readTemperature();
  int hum = dht.readHumidity();

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Sicaklik: ");
  lcd.print(temp);
  lcd.print(" C");

  lcd.setCursor(0,1);
  lcd.print("Nem: %");
  lcd.print(hum);

  delay(2000);

 

 

}
