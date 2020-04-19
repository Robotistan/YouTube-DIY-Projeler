#include <SPI.h>
#include <RFID.h>
#include <Keyboard.h>

#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN,RST_PIN);

int buzzer = 7;

void setup() {
  pinMode(buzzer,OUTPUT);
  digitalWrite(buzzer,LOW);
  SPI.begin();
  rfid.init();
  Keyboard.begin();
  Serial.println();

}

void loop() {

  if(rfid.isCard()){
    if(rfid.readCardSerial()){
      if(rfid.serNum[0] == 64
      && rfid.serNum[1] == 150
      && rfid.serNum[2] == 49
      && rfid.serNum[3] == 131
      && rfid.serNum[4] == 100
      ){
        digitalWrite(buzzer,HIGH);
        delay(100);
        digitalWrite(buzzer,LOW);
        delay(100);
        digitalWrite(buzzer,HIGH);
        delay(100);
        digitalWrite(buzzer,LOW);
        Keyboard.press(KEY_RETURN);
        delay(50);
        Keyboard.releaseAll();
        delay(200);

        Keyboard.print("Bilgisayar Şifresiniz Buraya Girin :) ");
        Keyboard.press(KEY_RETURN);
        delay(50);
        Keyboard.releaseAll();
        delay(200);
        
      }
    }
  }
rfid.halt();
}
