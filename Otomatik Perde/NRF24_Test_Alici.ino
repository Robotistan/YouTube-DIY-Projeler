#include <Stepper.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"           //Modül ile ilgili kütüphaneleri ekliyoruz

int mesaj[1];
int led = 2;
const uint64_t kanal = 1011;

RF24 alici(9,10);

#define STEPS 4096

Stepper stepper(STEPS, 7, 6, 5, 4);

void setup(void){
 Serial.begin(9600);
 
 alici.begin();
 alici.openReadingPipe(1,kanal);
 alici.startListening();
 pinMode(led, OUTPUT);
 stepper.setSpeed(2);
 }

void loop(void){
 Serial.println("mesaj yok");
 if(alici.available())
 {
    
  alici.read(mesaj, 1);      
  Serial.println(mesaj[0]);
     if (mesaj[0] == 100)
     {

      stepper.step(4096);
      }
      if(mesaj[0] == 200){
     
      stepper.step(-4096);
      }
     
     delay(10);
   }
   delay(300);
 }
