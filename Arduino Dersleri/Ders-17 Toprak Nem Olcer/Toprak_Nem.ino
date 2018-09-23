int sensorPin = 9;                  //Sensörün takılacağı pin 
int buzzerPin = 8;                  //Buzzerın takılacağı pin
int veri;                           //Sensörden okunan verinin tutulacağı değişken

void setup() {
  pinMode(sensorPin, INPUT);        //Sensörün takılacağı pini INPUT olarak ayarlıyoruz.
  pinMode(buzzerPin, OUTPUT);       //Buzzerın takılacağı pini OUTPUT olarak ayarlıyoruz.
}
void loop() {
  veri = digitalRead(sensorPin);    //Sensörden dijital okuma yapıyoruz.
  if(veri == true){            //Sensör verisi eşik değerini geçerse if içerisindeki kodlar uygulanır.
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
    delay(100);
  }
  else{                             //Sensör verisi eşik değerinden küçük olursa if içerisindeki kodlar uygulanır.
    digitalWrite(buzzerPin, LOW);
  }
}


