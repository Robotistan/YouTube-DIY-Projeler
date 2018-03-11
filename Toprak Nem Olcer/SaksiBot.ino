#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();


#define nem_pin A3

const int prob = A0;
int olcum = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Toprak Su testi");
  matrix.begin(0x70);  // pass in the address
  matrix.setRotation(1); //yüz yamulmasın diye
}

static const uint8_t PROGMEM emojiSaskin[] = {
  B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10011001,
  B10100101,
  B01011010,
  B00111100
};

static const uint8_t PROGMEM emojiMutlu[] = {

  B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10111101,
  B10100101,
  B01011010,
  B00111100

};

static const uint8_t PROGMEM emojiUzgun[] = {

  B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10011001,
  B10100101,
  B01000010,
  B00111100
};

void loop() {
  

  if(digitalRead(nem_pin) ==0){
  matrix.drawBitmap(0, 0, emojiMutlu, 8, 8, LED_ON);
    matrix.writeDisplay();
    Serial.println("uzgun");
    matrix.clear();
    
  }
  else{
     matrix.drawBitmap(0, 0, emojiUzgun, 8, 8, LED_ON);
    matrix.writeDisplay();
    Serial.println("uzgun");
    matrix.clear();

    
  }

  delay(1000);
  
   
  
  

}
