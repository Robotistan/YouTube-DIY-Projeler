int esikDegeri = 400;               //Gaz eşik değerini belirliyoruz.    
int buzzerPin = 9;                  //Buzzerın takılacağı pin
int deger;                          //Sensörden okunan değer

void setup() {
  pinMode(buzzerPin, OUTPUT);       //Buzzer pinimizi çıkış olarak ayarlıyoruz.
}

void loop() {
  deger = analogRead(A0);           //Sensörden analog değer okuyoruz.
  if(deger > esikDegeri){           //Sensörden okunan değer eşik değerinden büyükse çalışır.
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
    delay(100);
  }
  else{                             //Sensörden okunan değer eşik değerinin altındaysa çalışır.
    digitalWrite(buzzerPin, LOW);
  }
}


