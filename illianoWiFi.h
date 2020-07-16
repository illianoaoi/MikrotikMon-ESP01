#include <ESP8266WiFi.h>

//ตั้งค่า WiFi
char ssid[] = "@illiano-Floor.2";
char pass[] = "0914395665";

String connectWiFi() {
   WiFi.hostname("espChk-Temp-Tik");
   WiFi.begin(ssid, pass); // สั่งให้เชื่อมต่อกับ AP
   while (WiFi.status() != WL_CONNECTED) //รอจนกว่าจะเชื่อมต่อสำเร็จ
    {
      delay(1000);
      Serial.print("*");
      
      
    }
    Serial.println("");
    Serial.println("WiFi connected"); //แสดงข้อความเชื่อมต่อสำเร็จ
    Serial.print("IP address: ");
    Serial.print(WiFi.localIP()); //แสดงหมายเลข IP NodeMCU ของเรา
    String ip = WiFi.localIP().toString();
    return ip;
}
