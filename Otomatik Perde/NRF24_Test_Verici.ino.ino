//#include  <SPI.h> 
#include "nRF24L01.h"
#include "RF24.h"     //Modül ile ilgili kütüphaneleri ekliyoruz

int mesaj[1];      //mesaj isminde bir dizi tanımlıyoruz
RF24 verici(9,10);     //kütüphane tarafından kullanılacak pinleri tanımlıyoruz
const uint64_t kanal = 1011; //kanalı tanımlıyoruz  
int buton = 7;      //butonun bağlı olduğu dijital pin

#define buton_a 2
#define buton_k 3

void setup(void)
{
 verici.begin();       //nrf yi başlatıyoruz
 verici.openWritingPipe(kanal);  //kanal id sı tanımlanıyor
 Serial.begin(9600);
 pinMode(buton_a, INPUT_PULLUP);
 pinMode(buton_k, INPUT_PULLUP);
} 


void loop(void)
{

if(digitalRead(buton_a) == 0){

  mesaj[0] = 100; 
 verici.write(mesaj, 1);   //mesaj değişkeni yollanıyor
 Serial.println("mesaj gönderildi");
  delay(200);
  
}

 if(digitalRead(buton_k) == 0){

  mesaj[0] = 200; 
 verici.write(mesaj, 1);   //mesaj değişkeni yollanıyor
 Serial.println("mesaj gönderildi");
  delay(200);
  
}
 }
