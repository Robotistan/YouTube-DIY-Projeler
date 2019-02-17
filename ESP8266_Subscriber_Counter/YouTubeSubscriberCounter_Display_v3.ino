// YouTube Subscriber Counter v2
// by Becky Stern 2018

// Displays your current subscriber count on a seven-segment display
// This version uses two four digit displays to support more than 10k subs

//   based on library sample code by:
//   Giacarlo Bacchio (Gianbacchio on github)
//   Brian Lough (witnessmenow on github)
//   Adafruit (adafruit on github)

// requires the following libraries, search in Library Manager or download from github:


#include <YoutubeApi.h>            // https://github.com/witnessmenow/arduino-youtube-api
#include <ArduinoJson.h>           // https://github.com/bblanchon/ArduinoJson

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#include "LedControl.h"

char ssid[] = "internet adınızı buraya yazın";       // your network SSID (name)
char password[] = "internet şifrenizi buraya yazın";  // your network key

int digit_0 = 0;
int digit_1 = 0;
int digit_2 = 0;
int digit_3 = 0;

int digit_4 = 0;
int digit_5 = 0;
int digit_6 = 0;
int digit_7 = 0;

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 8 is connected to the DataIn 
 pin 7 is connected to LOAD 
 pin 6 is connected to the CLK
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(D8,D6,D7,1);

//------- enter your API key and channel ID here! ------
#define API_KEY "google cloud platformdaki API Key'i buraya yazın."  // your google apps API Token
#define CHANNEL_ID "Kanal ID'sini Buraya Yazın" // kanala girdiğinizde linkteki karışık yazılı kısım

int subscriberCount; // create a variable to store the subscriber count

WiFiClientSecure client;
YoutubeApi api(API_KEY, client);

unsigned long api_mtbs = 1000; //mean time between api requests
unsigned long api_lasttime;   //last time api request has been done


unsigned int counter = 0;

void setup() {

  Serial.begin(115200);
  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);


}


void loop() {

 
    if(api.getChannelStatistics(CHANNEL_ID))
    {
      subscriberCount = api.channelStats.subscriberCount ;
      Serial.println("---------Stats---------");
      Serial.print("Subscriber Count: ");
      Serial.println(subscriberCount);
      Serial.println("------------------------");

    }
     delay(1000);
     
      digit_0 = subscriberCount % 10;
      digit_1 = (subscriberCount / 100) % 100;
      digit_2 = (subscriberCount / 1000) % 1000;
      digit_3 = (subscriberCount / 10000) % 10000;

      digit_4 = (subscriberCount / 100000) % 100000;
      digit_5 = (subscriberCount / 10000000) % 1000000;
      digit_6 = (subscriberCount / 10000000) % 10000000;
      digit_7 = (subscriberCount / 100000000) % 100000000;

   

   lc.clearDisplay(0);

   lc.setChar(0,1,digit_0,false);
   lc.setChar(0,2,digit_1,false);
   lc.setChar(0,3,digit_2,false);
   lc.setChar(0,4,digit_3,false);
   
   lc.setChar(0,5,digit_4,false);
   lc.setChar(0,1,digit_5,false);
   lc.setChar(0,2,digit_6,false);
   lc.setChar(0,3,digit_7,false);
  

   if(digit_0 >0)
   lc.setChar(0,1,digit_0,false);

   if(digit_1 >0)
   lc.setChar(0,2,digit_1,false);

   if(digit_2 >0)
   lc.setChar(0,3,digit_2,false);

   if(digit_3 >0)
   lc.setChar(0,4,digit_3,false);

   if(digit_4 >0)
   lc.setChar(0,5,digit_4,false);

   if(digit_5 >0)
   lc.setChar(0,6,digit_5,false);
   if(digit_6 >0)
   lc.setChar(0,7,digit_6,false);
   
   if(digit_7 >0)
   lc.setChar(0,8,digit_7,false);



     
}
