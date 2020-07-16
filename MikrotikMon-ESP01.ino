/********************************************************
  Nirun Leeyagart
  https://www.facebook.com/illianoaoi

  Monitor mikrotik Temp, CPU, WAN1 และสั่งเปิดปิดพัดลมตามอุณภูมิที่ต้องการ
********************************************************/

#include <Arduino.h>
#include <Wire.h>
#include <BlynkSimpleEsp8266.h>
#include "config.h"
#include "illianoWiFi.h"
#include "getAPI.h"
#define RELAY 0
#define LED 2
unsigned char status_RELAY = 0;

BLYNK_WRITE(V7)
{
  int pinValue = param.asInt(); 
  
  if (pinValue == 1)
  {
    status_RELAY = 1;
    digitalWrite(RELAY, HIGH);
    Serial.println("RELAY ON");
    WidgetLED led1(V5);
    led1.on();
    digitalWrite(LED, HIGH);
    
  }
  else if (pinValue == 0)
  {
    status_RELAY = 0;
    digitalWrite(RELAY, LOW);
    Serial.println("RELAY OFF");
    WidgetLED led1(V5);
    led1.off();
    digitalWrite(LED, LOW);
  }
  
}


void setup() {
  //Blynk เชื่อมต่อกับ Server
  Blynk.begin(auth, ssid, pass);

  Serial.begin(115200); //ตั้งค่าใช้งาน serial ที่ baudrate 115200
  String ip = connectWiFi();  // สั่งให้เชื่อมต่อกับ AP
  Blynk.virtualWrite(V0, ip); //ส่งไปที่ Blynk

    ///////// Relay ////////////
    pinMode(RELAY, OUTPUT);
    pinMode(LED, OUTPUT);
    digitalWrite(LED, HIGH);
    Blynk.virtualWrite(V7, 0);
    WidgetLED led1(V5);
    led1.off();
    ////////////////////////////
  
  delay(5000);
}

void loop() {  
  Blynk.run();
  Serial.println(getTemp());
  Serial.println(getCPU());

  Blynk.virtualWrite(V1, getTemp()); //ส่งไปที่ Blynk
  Blynk.virtualWrite(V2, getCPU()); //ส่งไปที่ Blynk
  Blynk.virtualWrite(V3, getdownload()); //ส่งไปที่ Blynk
  Blynk.virtualWrite(V4, getupload()); //ส่งไปที่ Blynk

  int Temp = getTemp().toInt();

  if (Temp >= 33)
  {
    status_RELAY = 1;
    digitalWrite(RELAY, HIGH);
    Serial.println("RELAY ON");
    WidgetLED led1(V5);
    led1.on();
    digitalWrite(LED, HIGH);
    Blynk.virtualWrite(V7, 1);
    
  }
  else if (Temp <= 32)
  {
    status_RELAY = 0;
    digitalWrite(RELAY, LOW);
    Serial.println("RELAY OFF");
    WidgetLED led1(V5);
    led1.off();
    digitalWrite(LED, LOW);
    Blynk.virtualWrite(V7, 0);
    
  }
  
  delay(Refesh);
}
