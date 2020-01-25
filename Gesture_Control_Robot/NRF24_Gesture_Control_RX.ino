/* JoyStick modulu icin alici kodu
 - BAGLANTILAR: nRF24L01 Modulu:
   1 - GND
   2 - VCC 3.3V !!! 5V DEGIL
   3 - CE to Arduino pin 6
   4 - CSN to Arduino pin 8
   5 - SCK to Arduino pin 13
   6 - MOSI to Arduino pin 11
   7 - MISO to Arduino pin 12
   8 - KULLANILMIYOR
 */
//-----( Gereken kutuphaneleri ekliyoruz )-----
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
/*-----( Sabitleri ve pin numaralarini belirtiyoruz )-----*/
#define CE_PIN 9
#define CSN_PIN 10

 const uint64_t pipe = 0xE8E8F0F0E1LL; // Pipe tanimliyoruz


/*-----( Nesneleri belirt )-----*/
RF24 radio(CE_PIN, CSN_PIN); // Radio olustur
/*-----( Degiskenleri belirt )-----*/
int joystick[2];  // Joystick'in ve 4 adet butonun okunmasini tutan 6lı element dizisi
int speedRight = 0;
int speedLeft = 0;
int  xAxis, yAxis;
int xMapped, yMapped;
// joystickteki 4 adet buton degiskeni
int buttonUp;
int buttonRight;
int buttonDown;
int buttonLeft;

void setup()
{
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
    


  Serial.begin(9600);
  Serial.println("Nrf24L01 Alici Baslatiliyor"); 
  
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();

  
}

void loop()
{
  if ( radio.available() )
  {
      radio.read( joystick, sizeof(joystick) );
      xAxis = joystick[0];
      yAxis = joystick[1];


    if (yAxis < -20) {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);

    digitalWrite(4, LOW);
    digitalWrite(7, HIGH);
 
    
      speedRight  = map(yAxis, -20, -60, 0, 255);
      speedLeft   = map(yAxis, -20, -60, 0, 255);
  }

  else if (yAxis > 20) {
 
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(7, LOW);
 
  
    speedRight  = map(yAxis, 20, 60, 0, 255);
    speedLeft   = map(yAxis, 20, 60, 0, 255);

    
  }
  else {
    speedRight  = 0;
    speedLeft   = 0;
  }

  if (xAxis < -20) {

    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);

    digitalWrite(4, LOW);
    digitalWrite(7, HIGH);
   
    int xMapped = map(xAxis, -20, -60, 0, 255);
    speedLeft = speedLeft - xMapped;
    speedRight = speedRight + xMapped;
    if (speedLeft < 0) {
      speedLeft = 0;
    }
    if (speedRight > 255) {
      speedRight = 255;
    }
  }
  else if (xAxis > 20) {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);

    digitalWrite(4, HIGH);
    digitalWrite(7, LOW);
   
    int xMapped = map(xAxis, 20, 60, 0, 255);
    speedLeft = speedLeft + xMapped;
    speedRight = speedRight - xMapped;
    if (speedLeft > 255) {
      speedLeft = 255;
    }
    if (speedRight < 0) {
      speedRight = 0;
    }


      }   
    analogWrite(5,speedRight);
    analogWrite(6,speedLeft);
      
     
      Serial.print("X = ");
      Serial.print(xAxis);
      Serial.print(" Y = ");  
      Serial.print(yAxis);
      Serial.print(" Speed X = ");  
      Serial.print(speedRight);
      Serial.print(" SpeedY = ");  
      Serial.println(speedLeft);
      
      }}
