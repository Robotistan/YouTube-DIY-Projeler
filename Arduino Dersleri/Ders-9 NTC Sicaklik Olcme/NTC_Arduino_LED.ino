#include <math.h>

#define led 2


void setup() {
  Serial.begin(9600);
  pinMode(led,OUTPUT);
}


double Termistor(int analogOkuma){

 double sicaklik;
 sicaklik = log(((10240000 / analogOkuma) - 10000));
 sicaklik = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * sicaklik * sicaklik)) * sicaklik);
 sicaklik = sicaklik - 273.15;
 return sicaklik;
}


void loop() {

  
  int deger = analogRead(A0);
  double sicaklik = Termistor(deger);
  Serial.println(sicaklik);

  if(sicaklik > 30){
    digitalWrite(led,HIGH);
  }
  else{
    digitalWrite(led,LOW);
  }

  delay(250);
  
  

}
