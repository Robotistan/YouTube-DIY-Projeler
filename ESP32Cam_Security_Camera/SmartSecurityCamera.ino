/*************************************************************************************************************************************************
 *  Proje Üreticisi          : Sefer Döngel, Robotistan
 *  Proje Adı                : DIY Akıllı Güvenlik Kamerası
 *  Proje Açıklaması         : Bu projede fake bir güvenlik kamerasından;
 *                             hareket algıladığında anlık fotoğraf çekip, çektiği fotoğrafı hem üzerindeki SD karta kaydeden hem de tanımlı mail 
 *                             adreslerine mail olarak ileten wifi bağlantılı akıllı bir güvenlik kamerası yapıyoruz.
 *                             Proje hakkında daha fazla bilgi için Robotistan kanalında yayınlanan videoyu izleyip daha fazla bilgi sahibi olabilirsiniz.
 *  Robotistan Youtube Kanalı: https://www.youtube.com/robotistan
 *  Şahsi Youtube Kanalım    : https://www.youtube.com/c/seferdongel
 *************************************************************************************************************************************************/

  /********************************************************************************************************************
 *  Kart Özellikleri
 *  Board           : "ESP32 Wrover Module"
 *  Upload Speed    : "921600"
 *  Flash Frequency : "80MHz"
 *  Flash Mode      : "QIO"
 *  Partition Scheme: "Hue APP (3MB No OTA/1MB SPIFFS)"
 *  Core Debug Level: "None"
 *  COM Port        : Her bağlantıda farklı olabilir.
 *********************************************************************************************************************/
 
#include "esp_camera.h"
#include "FS.h"
#include "SPI.h"
#include "SD.h"
#include "EEPROM.h"
#include "driver/rtc_io.h"
#include "ESP32_MailClient.h"

//Uygulama modelini AI THINKER olarak seçiyoruz.
//#define CAMERA_MODEL_WROVER_KIT
//#define CAMERA_MODEL_ESP_EYE
//#define CAMERA_MODEL_M5STACK_PSRAM
//#define CAMERA_MODEL_M5STACK_WIDE
#define CAMERA_MODEL_AI_THINKER

#include "camera_pins.h"

#define ID_ADDRESS            0x00
#define COUNT_ADDRESS         0x01
#define ID_BYTE               0xAA
#define EEPROM_SIZE           0x0F

uint16_t nextImageNumber = 0;

#define WIFI_SSID             "xxxxxxxxxxxxxxx"                    // Kameranın bağlanacağı wifi SSID girilmeli.
#define WIFI_PASSWORD         "xxxxxxxxxxxxxxx"                   // Kameranın bağlanacağı wifi şifresi girilmeli.

#define emailSenderAccount    "xxxxx@xxxx.com"                    // e-mail gönderimi için gmail port 465 (SSL) kullanılıyorsa, "daha az güvenli uygulama erişimi" aktif edilmeli. https://myaccount.google.com/lesssecureapps?pli=1
#define emailSenderPassword   "xxxxxxxxxxxxxx"                    // e-mail şifresi.

#define emailRecipient        "xxxxx@xxxx.com"   //#define komutu ile birden fazla alıcı tanımlanabilir.

//E-posta gönderme veri nesnesi, gönderilecek yapılandırma ve verileri içerir.
SMTPData smtpData;

//E-posta gönderme durumunu almak için geri arama işlevi.
void sendCallback(SendStatus info);

void setup() 
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting...");

  pinMode(4, INPUT);              //LED flash için GPIO pini ataması yapıyoruz.
  digitalWrite(4, LOW);
  rtc_gpio_hold_dis(GPIO_NUM_4);  //Uyku moduna geçmeden önce etkinleştirilmişse pin tutmayı devre dışı bırakıyoruz.

  //WiFi Bağlantısı
  Serial.print("Connecting to AP");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(200);
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
    
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  
 
  if(psramFound())
  {
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else 
  {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

#if defined(CAMERA_MODEL_ESP_EYE)
  pinMode(13, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
#endif

  //Güvenlik Kamerasını başlatıyoruz.
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) 
  {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  //Kamera parametrelerini ayarlıyoruz.
  sensor_t * s = esp_camera_sensor_get();
  s->set_contrast(s, 2);    //min=-2, max=2
  s->set_brightness(s, 2);  //min=-2, max=2
  s->set_saturation(s, 2);  //min=-2, max=2
  delay(100);               //wait a little for settings to take effect
  
  //SD kartı mount ediyoruz.
  Serial.println("Mounting SD Card...");
  MailClient.sdBegin(14,2,15,13);

  if(!SD.begin())
  {
    Serial.println("Card Mount Failed");
    return;
  }

  // EEPROM'u başlatıyoruz.
  if (!EEPROM.begin(EEPROM_SIZE))
  {
    Serial.println("Failed to initialise EEPROM"); 
    Serial.println("Exiting now"); 
    while(1);   //Bir hata oluştuysa bu satırda bekleniyor.  
  }

/*
  EEPROM.get(COUNT_ADDRESS, nextImageNumber);
  Serial.println(nextImageNumber);
  nextImageNumber += 1;
  EEPROM.put(COUNT_ADDRESS, nextImageNumber);
  EEPROM.commit();
  while(1);
  */
  
  /*ERASE EEPROM BYTES START*/
  /*
  Serial.println("Erasing EEPROM...");
  for(int i = 0; i < EEPROM_SIZE; i++)
  {
    EEPROM.write(i, 0xFF);
    EEPROM.commit();
    delay(20);
  }
  Serial.println("Erased");
  while(1);
  */
  /*ERASE EEPROM BYTES END*/  

  if(EEPROM.read(ID_ADDRESS) != ID_BYTE)    //Eğer geçerli bir resim numarası değilse
  {
    Serial.println("Initializing ID byte & restarting picture count");
    nextImageNumber = 0;
    EEPROM.write(ID_ADDRESS, ID_BYTE);  
    EEPROM.commit(); 
  }
  else                                      // resim numarasını geçerli olana kadar bir sonrakini alarak değiştiriyoruz.
  {
    EEPROM.get(COUNT_ADDRESS, nextImageNumber);
    nextImageNumber +=  1;    
    Serial.print("Next image number:");
    Serial.println(nextImageNumber);
  }

  // Yeni bir fotoğraf karesi alınıyor.
  camera_fb_t * fb = NULL;
    
  // Kameranın frame buffer bilgisi alınıyor.
  fb = esp_camera_fb_get();
  if (!fb) 
  {
    Serial.println("Camera capture failed");
    Serial.println("Exiting now"); 
    while(1);   // Bir hata oluştuysa bu satırda bekleniyor.
  }

  //Fotoğraf SD karta kaydediliyor.
  //Fotoğraf için veri yolu ve isim oluşturuluyor.
  String path = "/IMG" + String(nextImageNumber) + ".jpg";
    
  fs::FS &fs = SD;

  //Yeni bir dosya oluşturuluyor.
  File file = fs.open(path.c_str(), FILE_WRITE);
  if(!file)
  {
    Serial.println("Failed to create file");
    Serial.println("Exiting now"); 
    while(1);   //Bir hata oluştuysa bu satırda bekleniyor.    
  } 
  else 
  {
    file.write(fb->buf, fb->len); 
    EEPROM.put(COUNT_ADDRESS, nextImageNumber);
    EEPROM.commit();
  }
  file.close();

  //Kameranın frame buffer bilgisi gönderiliyor.
  esp_camera_fb_return(fb);
  Serial.printf("Image saved: %s\n", path.c_str());

  //E-posta gönderimi
  Serial.println("Sending email...");
  //E-posta ana bilgisayarını, bağlantı noktasını, hesabı ve şifresini ayarlıyoruz. 
  smtpData.setLogin("smtp.gmail.com", 587, emailSenderAccount, emailSenderPassword);
  
  //E-posta göndericisinin ismi ve e-mail adresi bilgisini ayarlıyoruz.
  smtpData.setSender("ESP32-CAM", emailSenderAccount);
  
  //E-posta önceliğini Normal olarak ayarlıyoruz. Öncelikli yapmak için High yapılabilir.
  smtpData.setPriority("Normal");

  //E-postanın konusunu belirliyoruz.
  smtpData.setSubject("Motion Detected - ESP32-CAM");
    
  //E-posta metninin yapısını text ya da html olarak düzenliyoruz.
  smtpData.setMessage("<div style=\"color:#003366;font-size:20px;\">Image captured and attached.</div>", true);

  //E-postanın gönderileceği alıcıları tanımlıyoruz. Birden fazla alıcı tanımlanabilir.
  smtpData.addRecipient(emailRecipient);
  //smtpData.addRecipient(emailRecipient2);
  
  //E-postaya SD karttan fotoğraf ekliyoruz.
  smtpData.addAttachFile(path);
  
  //Ekli dosyayı(fotoğrafı) okuyabilmek için hafıza tipini SD olarak ayarlıyoruz.
  smtpData.setFileStorageType(MailClientStorageType::SD);
  
  smtpData.setSendCallback(sendCallback);
  
  //E-posta gönderimini başlatıyoruz. 
  if (!MailClient.sendMail(smtpData))
    Serial.println("Error sending Email, " + MailClient.smtpErrorReason());

  //E-posta gönderimi tamamlandıktan sonra bir sonraki gönderim için nesnedeki tüm verileri temizliyoruz.
  smtpData.empty();

  pinMode(4, OUTPUT);              //LED flash için GPIO pini tanımlıyoruz.
  digitalWrite(4, LOW);            //Led flashı kapatıyoruz
  rtc_gpio_hold_en(GPIO_NUM_4);    //Enerji tasarrufu için LED flash'ı uyku modunda kapatıyoruz.
  Serial.println("Entering deep sleep mode");
  Serial.flush(); 
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_13, 0);   //PIN 13 LOW olduğunda aktif moda geçiyoruz.
  delay(10000);                                   //PIR sensörün sağlıklı okuma yapabilmesi için 10 sn zaman tanıyoruz.
  esp_deep_sleep_start();
}

void loop() 
{


}

//E-posta gönderim durumunu izliyoruz.
void sendCallback(SendStatus msg)
{
  //Anlık durum bilgisini seri port ekranında görüntülüyoruz.
  Serial.println(msg.info());

  //E-posta başarılı bir şekilde gönderildiyse seri port ekranına bilgi yazıyoruz.
  if (msg.success())
  {
    Serial.println("E-posta gönderimi başarılı. Şimdi onlar düşünsün :)");
  }
}
