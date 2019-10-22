
#include <Arduino.h>
#include <TinyMPU6050.h>

float pos_offset = 10;
float neg_offset = -10;
long angle_x, angle_y, angle_z, offset_x, offset_y, offset_z;
MPU6050 mpu (Wire);


void setup() {

  // Initialization
  mpu.Initialize();

  // Calibration
  Serial.begin(9600);
  Serial.println("=====================================");
  Serial.println("Starting calibration...");
  Serial.println("Calibration complete!");
  Serial.println("Offsets:");
  Serial.print("AccX Offset = ");
  Serial.println(mpu.GetAccXOffset());
  Serial.print("AccY Offset = ");
  Serial.println(mpu.GetAccYOffset());
  Serial.print("AccZ Offset = ");
  Serial.println(mpu.GetAccZOffset());
  Serial.print("GyroX Offset = ");
  Serial.println(mpu.GetGyroXOffset());
  Serial.print("GyroY Offset = ");
  Serial.println(mpu.GetGyroYOffset());
  Serial.print("GyroZ Offset = ");
  Serial.println(mpu.GetGyroZOffset());
  pinMode(14,OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(14, LOW);
  digitalWrite(9, LOW);

  delay(1000);
  for(int i=0; i<200;i++){
   mpu.Execute();
  offset_x = mpu.GetAngX();
  offset_y = mpu.GetAngY();
  offset_z = mpu.GetAngZ();
  }
  Serial.print("offset_x = ");
  Serial.print(offset_x);
  Serial.print("  /  offsetY = ");
  Serial.print(offset_y);
  Serial.print("  /  offsetZ = ");
  Serial.println(offset_z);
  
}

void loop() {

 for(int i=0; i<5;i++){
  mpu.Execute();
  angle_x = mpu.GetAngX();
  angle_y = mpu.GetAngY();
  angle_z = mpu.GetAngZ();
 }

  Serial.print("AngX = ");
  Serial.print(angle_x - offset_x);
  Serial.print("  /  AngY = ");
  Serial.print(angle_y - offset_y);
  Serial.print("  /  AngZ = ");
  Serial.println(angle_z - offset_z);
  

 if ( pos_offset < angle_x - offset_x || neg_offset > angle_x - offset_x || pos_offset < angle_y - offset_y || neg_offset > angle_y - offset_y || pos_offset < angle_z - offset_z || neg_offset > angle_z - offset_z){

  for(int i=0; i<50; i++){
  digitalWrite(14,HIGH);
  digitalWrite(9,LOW);
  delay(50);
  digitalWrite(14,LOW);
  digitalWrite(9,LOW);
  delay(50);
  }   
  delay(5000);  
  mpu.Execute();
  offset_x = mpu.GetAngX();
  offset_y = mpu.GetAngY();
  offset_z = mpu.GetAngZ();

 }  
}
