/********************************************************
  Nirun Leeyagart
  https://www.facebook.com/illianoaoi
  leeyagart@gmail.com

  Monitor mikrotik Temp, CPU, WAN1 และสั่งเปิดปิดพัดลมตามอุณภูมิที่ต้องการ
  Version 1.0
  Release Date : 16/07/2020
********************************************************/

#include <Arduino.h>
#include <Wire.h>
#include <BlynkSimpleEsp8266.h>
#include "config.h"
#include "illianoWiFi.h"
#include "getAPI.h"
#define RELAY 0 //รีเลย์เป็นขา 0
#define LED 2 //ไฟ LED เป็นขา 2
unsigned char status_RELAY = 0;

void setup() {
  //Blynk เชื่อมต่อกับ Server
  Blynk.begin(auth, ssid, pass);

  Serial.begin(115200); //ตั้งค่าใช้งาน serial ที่ baudrate 115200
  String ip = connectWiFi();  // สั่งให้เชื่อมต่อกับ AP
  Blynk.virtualWrite(V0, ip); //ส่งเลขไอพีไปที่ Blynk

    ///////// Relay ////////////
    pinMode(RELAY, OUTPUT);
    pinMode(LED, OUTPUT);
    digitalWrite(LED, HIGH);  //ปิดไฟ LED
    digitalWrite(RELAY, LOW); //ปิดรีเลย์
    Blynk.virtualWrite(V5, "ปิด"); //ส่งไปที่ Blynk
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

  if (Temp >= onRelay)
  {
    status_RELAY = 1;
    digitalWrite(RELAY, HIGH);  //เปิดรีเลย์
    Serial.println("RELAY ON");
    Blynk.virtualWrite(V5, "เปิด"); //ส่งไปที่ Blynk
    digitalWrite(LED, LOW); //เปิดไฟ LED
  }
  else if (Temp <= offRelay)
  {
    status_RELAY = 0;
    digitalWrite(RELAY, LOW); //ปิดรีเลย์
    Serial.println("RELAY OFF");
    Blynk.virtualWrite(V5, "ปิด"); //ส่งไปที่ Blynk
    digitalWrite(LED, HIGH);  //ปิดไฟ LED
  }
  
  delay(Refesh);
}
