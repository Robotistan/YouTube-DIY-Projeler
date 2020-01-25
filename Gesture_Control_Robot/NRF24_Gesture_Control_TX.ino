/* 
   1 - GND
   2 - VCC 3.3V !!! 5V DEGIL
   3 - CE Arduino pin 9
   4 - CSN Arduino pin 10
   5 - SCK Arduino pin 13
   6 - MOSI Arduino pin 11
   7 - MISO Arduino pin 12
   8 - KULLANILMIYOR

*/

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);

#define CE_PIN   9
#define CSN_PIN 10

const uint64_t pipe = 0xE8E8F0F0E1LL; // Pipe tanimliyoruz

RF24 radio(CE_PIN, CSN_PIN); // Radio yaratiyoruz

int joystick[2];  // Joystick'in ve 4 adet butonun okunmasini tutan 6lı element dizisi


void setup() {

  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);
  radio.stopListening();
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  

}

void loop() {
    mpu6050.update();

    joystick[0] = mpu6050.getAngleX();
    joystick[1] = mpu6050.getAngleY();
  
    radio.write( joystick, sizeof(joystick) );
    delay(20);


}  
