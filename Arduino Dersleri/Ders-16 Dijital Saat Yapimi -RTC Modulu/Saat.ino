#include <LiquidCrystal.h>                              //LCD kütüphanemizi başlatıyoruz.
#include <virtuabotixRTC.h>                             //RTC kütüphanemizi ekliyoruz.

int CLK_PIN = 6;                                        //6. pini clock pini olarak tanımladık
int DAT_PIN = 7;                                        //7. pini data pini olarak tanımladık
int RST_PIN = 8;                                        //8. pini reset pini olarak tanımladık.
virtuabotixRTC myRTC(CLK_PIN, DAT_PIN, RST_PIN);        // Kütüphanemizi pinlere atıyoruz.4
int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;   //LCD'nin pin değişkenlerini tanımlıyoruz.
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);              //LCD'nin pin bağlantılarını ayarlıyoruz.

void setup() {
  lcd.begin(16, 2);                                     //LCD ekranımızın en-boy oranını ayarlıyoruz.                                
}
void loop() {
  
  myRTC.updateTime();                                   //RTC'den zamanı okuyoruz
  
  lcd.clear();                                          //Başlamadan önce ekranı temizliyoruz.
  lcd.setCursor(0,0);                                   //Ekranın ilk satır ilk sütunundan yazmaya başlıyoruz.
  lcd.print(myRTC.dayofmonth);                          //Günü ekrana bastırıyoruz.
  lcd.print("/");
  lcd.print(myRTC.month);                               //Ayı ekrana bastırıyoruz.
  lcd.print("/");
  lcd.print(myRTC.year);                                //Yılı ekrana bastırıyoruz
  lcd.setCursor(0, 1);                                  //LCD'nin 2. satır 1. sütunundan yazmaya başlıyoruz.
  lcd.print(myRTC.hours);                               //Saati ekrana bastırıyoruz.
  lcd.print(":");
  lcd.print(myRTC.minutes);                             //Dakikayi ekrana bastırıyoruz.   
  lcd.print(":");
  lcd.print(myRTC.seconds);                             //Saniyeyi ekrana bastırıyoruz.
  delay(1000);                                          //1 saniye bekleme.
}


