#include "ESP8266WiFi.h"
#include <U8g2lib.h>
U8G2_SSD1306_128X64_NONAME_F_3W_SW_SPI u8g2(U8G2_R2, /* clock=*/ 1, /* data=*/3, /* cs=*/ 10);
float wifirssi;
int switchon=1000;
int BTN=0;
#define ENCODER_BTN      4
#define WAKE_PIN        16

void setup() {
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(ENCODER_BTN), checkButton, CHANGE);
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  u8g2.begin();
  delay(100);
  Serial.println("Setup done");
}

void loop() {
  Serial.println("scan start");
  analogWrite(WAKE_PIN, switchon);
  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0) {
    Serial.println("no networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      u8g2.clearBuffer();          // clear the internal memory
      u8g2.setFont( u8g2_font_crox2h_tr);
      u8g2.setCursor(0, 15);
      u8g2.print(WiFi.SSID(i));
 
      u8g2.setCursor(70, 50);
      u8g2.print(WiFi.RSSI(i));
       u8g2.setCursor(90, 50);
      u8g2.print("db");


      wifirssi = WiFi.RSSI(i);
      yield();
      Serial.print(wifirssi);
      int  widthwifi = map(wifirssi, -90, -30, 1,5);
      for(int j=0;j<=widthwifi;j++)
      {
//      u8g2.drawCircle(20,70,j*6, U8G2_DRAW_UPPER_RIGHT);
        u8g2.drawBox(10+(j*7),60-(j*5),5,10+(j*5));
      }
      u8g2.sendBuffer();          // transfer internal memory to the display
      delay(1000);  
      
    }
  }
  Serial.println("");
  // Wait a bit before scanning again
//  delay(5000);
  switch(get_button()){
        case 1:
          switchon =0;
          break;
        }  
}
