#define led 3
#define pot A0


void setup() {

  

}

void loop() {

  int deger = analogRead(pot);
  deger = map(deger,0,1023,0,255);
  analogWrite(led,deger);
  


}
