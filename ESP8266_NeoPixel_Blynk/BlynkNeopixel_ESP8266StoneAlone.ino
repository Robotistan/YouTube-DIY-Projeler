#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>

#define BLYNK_PRINT Serial

#define PIN 2
#define NUMPIXELS 16

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{

Serial.begin(9600);
Blynk.begin("Eşleme Kodu", "Wi-Fi ID", "Wi-fi Şifresi");
pixels.begin();
}


BLYNK_WRITE(V1)
{
  
Serial.println("Veri Geldi");
int R = param[0].asInt();
int G = param[1].asInt();
int B = param[2].asInt();
Serial.println(R);
Serial.println(G);
Serial.println(B);

for(int i=0;i<NUMPIXELS;i++){
pixels.setPixelColor(i, pixels.Color(R,G,B));
pixels.show();
}

}

void loop()
{
Blynk.run();
Serial.println("Sistem Çalışıyor");

}
