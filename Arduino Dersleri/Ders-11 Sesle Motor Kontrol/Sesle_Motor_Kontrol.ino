

#define SensorPin 3
#define MotorPin 5 
int MotorDurum = LOW;

void setup() {
 
  pinMode(SensorPin, INPUT);
  pinMode(MotorPin, OUTPUT);
}

void loop() {
  

  if( digitalRead(SensorPin) ){

    if(MotorDurum == LOW){

      MotorDurum = HIGH;
    }
    else{

      MotorDurum = LOW;
    }

    digitalWrite(MotorPin, MotorDurum);

  }
  delay(50);
  

}
