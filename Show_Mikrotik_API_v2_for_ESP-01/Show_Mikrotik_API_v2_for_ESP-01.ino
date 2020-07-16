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


void setup() {
  //Blynk เชื่อมต่อกับ Server
  Blynk.begin(auth, ssid, pass);

  Serial.begin(115200); //ตั้งค่าใช้งาน serial ที่ baudrate 115200
  String ip = connectWiFi();  // สั่งให้เชื่อมต่อกับ AP
  Blynk.virtualWrite(V0, ip); //ส่งไปที่ Blynk
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
  
  delay(Refesh);
}
