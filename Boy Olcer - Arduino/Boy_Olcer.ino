#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);

#define echoPin 7
#define trigPin 8
#define buton 6

long sure, uzaklik, olcum, boy; 

void setup() {

  Serial.begin(9600);
  
  pinMode(echoPin, INPUT);
  pinMode(trigPin,OUTPUT);
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Boy Olcer");
  lcd.setCursor(3,1);
  lcd.print("Robotistan");
  delay(1500);
  
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  sure = pulseIn(echoPin, HIGH);
  uzaklik = sure / 29.1 / 2;

  Serial.print("Uzaklık");
  Serial.println(uzaklik);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Kalibrasyon");
  lcd.setCursor(0,1);
  lcd.print("Yapildi");
  delay(500);
  

}

void loop() {

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Boyunuzu olcmek");
  lcd.setCursor(0,1);
  lcd.print("icin tusa basin");

  delay(200);

  
  if(digitalRead(buton) == 1){

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Olculuyor");
  delay(1000);  

 digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  sure = pulseIn(echoPin, HIGH);
  olcum = sure / 29.1 / 2;

  boy = uzaklik-olcum;
  Serial.println(boy);

  lcd.setCursor(0,1);
  lcd.print(boy);
  lcd.print(" cm");

  delay(5000);

  }
  

}
