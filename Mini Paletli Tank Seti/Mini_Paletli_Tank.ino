#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX
char data;

#define sol_motor_1 4
#define sol_motor_2 5
#define sag_motor_1 2
#define sag_motor_2 3

 
void setup() {
pinMode(5,OUTPUT);   //Sol Motor 2
pinMode(2,OUTPUT);   //Sol Motor 1
pinMode(3,OUTPUT);   //Sağ Motor 1
pinMode(4,OUTPUT);   //Sağ Motor 2

Serial.begin(9600);
mySerial.begin(9600);

Serial.println("Setup is Done!");
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
