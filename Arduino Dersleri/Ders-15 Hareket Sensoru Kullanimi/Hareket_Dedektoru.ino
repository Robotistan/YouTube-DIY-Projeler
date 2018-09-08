#include <Servo.h>                //Servo kütüphanemizi ekliyoruz.

int pirPin = 8;                   //Sensörü takacağımız pin
int servoPin = 9;                 //Servoyu takacağımız pin
int hareket;                      //Sensörden aldığımız veri
Servo motor;                      //Servo motor değişkeni


void setup() {
  motor.attach(servoPin);         //Servomuzu 9. pin ile ilişkilendiriyoruz.
  pinMode(pirPin, INPUT);         //Sensör pinimizi giriş olarak ayarlyoruz.

}

void loop() {
  hareket = digitalRead(pirPin);  //Sensörden okuma yapıyoruz.
  
  if(hareket == HIGH){            //Hareketlilik var ise içerideki komutlar uygulanır.
    motor.write(150);
    delay(250);
    motor.write(30);
    delay(250);
    motor.write(150);
    delay(250);
    motor.write(30);
    delay(250);
    motor.write(150);
    delay(250);
    motor.write(30);
    delay(250);
    motor.write(90);
  }
  else{                           //Hareketlilik yok ise içerideki komutlar uygulanır.
    motor.write(90);
    
  }
}



