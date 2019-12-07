// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10); // RX, TX
char data;
int ss = 255;

AF_DCMotor motor_1(1);
AF_DCMotor motor_2(2);
AF_DCMotor motor_3(3);
AF_DCMotor motor_4(4);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");
  mySerial.begin(9600);

  // turn on motor
  motor_1.setSpeed(ss);
  motor_2.setSpeed(ss);
  motor_3.setSpeed(ss);
  motor_4.setSpeed(ss);
 
  motor_1.run(RELEASE);
  motor_2.run(RELEASE);
  motor_3.run(RELEASE);
  motor_4.run(RELEASE);
}

void ileri(){
  
 motor_1.setSpeed(ss);
 motor_2.setSpeed(ss);
 motor_3.setSpeed(ss);
 motor_4.setSpeed(ss);
 
 motor_1.run(BACKWARD);
 motor_2.run(FORWARD);
 motor_3.run(BACKWARD);
 motor_4.run(FORWARD);

  
}

void geri(){


  
 motor_1.setSpeed(ss);
 motor_2.setSpeed(ss);
 motor_3.setSpeed(ss);
 motor_4.setSpeed(ss);
 
 motor_1.run(FORWARD);
 motor_2.run(BACKWARD);
 motor_3.run(FORWARD);
 motor_4.run(BACKWARD);

  
}

void sol(){

 motor_1.setSpeed(ss);
 motor_2.setSpeed(ss);
 motor_3.setSpeed(ss);
 motor_4.setSpeed(ss);
 
 motor_1.run(FORWARD);
 motor_2.run(FORWARD);
 motor_3.run(BACKWARD);
 motor_4.run(BACKWARD);

 
  
}

void sag(){

 motor_1.setSpeed(ss);
 motor_2.setSpeed(ss);
 motor_3.setSpeed(ss);
 motor_4.setSpeed(ss);
 
 motor_1.run(BACKWARD);
 motor_2.run(BACKWARD);
 motor_3.run(FORWARD);
 motor_4.run(FORWARD);
  
  
}

void dur(){

 
  motor_1.run(RELEASE);
  motor_2.run(RELEASE);
  motor_3.run(RELEASE);
  motor_4.run(RELEASE);
  
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
