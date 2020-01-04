// Servo Motor'un Sinyal Ucunu D8'e bağlamanız gerekiyor. 


#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>                        //Gerekli kütüphanelerimizi ekliyoruz.
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

char token[] = "adrN6SwtQOqdFLmD8GMg9xy-AWq5QKBA";
char agAdi[] = "Robotistan";                     //Blynk uygulamasının bize vermiş olduğu token ve bağlanmak istediğimiz wifi ve şifresini char komutu ile belirliyoruz.
char agSifre[] = "bmc34RbT124";
int buton ;                                     // okuma yapacağımız nem değerini deger değişkeni olarak belirliyoruz.

#define sensor A0                               // Sensor okuma yapacağımız pini burada belirliyoruz. 
Servo servo;

BLYNK_WRITE(V1) {

buton = param.asInt();

}

void setup() {
  
  
  Serial.begin(9600);          //Blynk ve ESP iletişimi için serial monitörü başlatıyoruz.
  servo.attach(15);
  Blynk.begin(token, agAdi, agSifre);  // blynk uygulaması ve ESP bağlantısı sağlanması açısından Blynk.begin komutu içerisine token ve ag adı,şifremizi yazıyoruz.
  
}

void loop() {
    if(buton == 1){ 
      servo.write(120);
      delay(800);
      servo.write(90);
    }
    else {

      servo.write(90);
    }
  Blynk.run();                   //Blynk uygulamasını bağlatıyoruz.
 

}
