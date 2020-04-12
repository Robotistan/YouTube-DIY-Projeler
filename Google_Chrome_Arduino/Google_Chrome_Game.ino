#include <Servo.h>
#define led  13 //3.Pinde LED olduğunu tanımlıyoruz

Servo myservo;
void setup() {

    pinMode(led,OUTPUT); //LED'in çıkış elemanı olduğunu belirtiyoruz
    Serial.begin(9600); //9600 Baundluk bir seri haberleşme başlatıyoruz
    myservo.attach(9);
}

void loop() {

  int isik = analogRead(A0); //Işık değişkenini A0 pinindeki LDR ile okuyoruz
  int zemin = analogRead(A1);
  Serial.println(zemin); //Okunan değeri seri iletişim ekranına yansıtıyoruz
 

  if(zemin > 500){
  if(isik > 480){ 
    myservo.write(130);
    digitalWrite(13,HIGH);
    delay(100);
    myservo.write(90);
    digitalWrite(13,LOW);
  }
  }
  else{

   if(isik < 480){ 
    myservo.write(130);
    digitalWrite(13,HIGH);
    delay(150);
    myservo.write(90);
    digitalWrite(13,LOW);

    
  }
}}              
