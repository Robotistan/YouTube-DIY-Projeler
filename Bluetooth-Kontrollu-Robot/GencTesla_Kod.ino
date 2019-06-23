#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10); // RX, TX
char data;

#define sol_motor_1 A2
#define sol_motor_2 A1
#define sag_motor_1 A3
#define sag_motor_2 A4
#define trig 4
#define echo 3
#define sol_motor_en 6
#define sag_motor_en 5
 
void setup() {
pinMode(A1,OUTPUT);   //Sol Motor 2
pinMode(A2,OUTPUT);   //Sol Motor 1
pinMode(A3,OUTPUT);   //Sağ Motor 1
pinMode(A4,OUTPUT);   //Sağ Motor 2
pinMode(5,OUTPUT);   //Sağ Motor EN
pinMode(6,OUTPUT);   //Sol Motor EN
pinMode(4,OUTPUT);   //TrigPin
pinMode(3,INPUT);   //EchoPin
analogWrite(5,80);
analogWrite(6,80);


Serial.begin(9600);
mySerial.begin(9600);
}

void ileri(){

  digitalWrite(sol_motor_1, LOW);
  digitalWrite(sol_motor_2, HIGH);
  digitalWrite(sag_motor_1, HIGH);
  digitalWrite(sag_motor_2, LOW);
  
}

void geri(){


  digitalWrite(sol_motor_1, HIGH);
  digitalWrite(sol_motor_2, LOW);
  digitalWrite(sag_motor_1, LOW);
  digitalWrite(sag_motor_2, HIGH);

  
}

void sol(){

  

  digitalWrite(sol_motor_1, HIGH);
  digitalWrite(sol_motor_2, LOW);
  digitalWrite(sag_motor_1, HIGH);
  digitalWrite(sag_motor_2, LOW);
  
}

void sag(){
  
    digitalWrite(sol_motor_1, LOW);
  digitalWrite(sol_motor_2, HIGH);
  digitalWrite(sag_motor_1, LOW);
  digitalWrite(sag_motor_2, HIGH);
  
}

void dur(){

  digitalWrite(sol_motor_1, LOW);
  digitalWrite(sol_motor_2, LOW);
  digitalWrite(sag_motor_1, LOW);
  digitalWrite(sag_motor_2, LOW);
  
}
 
void loop() {

   long duration, distance;
  digitalWrite(trig, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = (duration/2) / 29.1;

  
if(mySerial.available()){
  data = mySerial.read();
  Serial.println(data);
}
 
if(data == 'F'){            
 ileri();
}
 
else if(data == 'B'){      
  geri();
}
 
else if(data == 'L'){      
  sol();
}
 
else if(data == 'R'){     
 sag();
}
 
else if(data == 'S'){      
  dur();
}

}
