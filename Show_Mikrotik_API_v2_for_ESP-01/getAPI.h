#include <ESP8266HTTPClient.h>

HTTPClient http;

String getTemp()  {
  http.begin("http://192.168.0.99/MikrotikAPIv2.php?get=health&cate=temp"); //HTTP
        int httpCode = http.GET();
        if (httpCode > 0) {
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);
            if (httpCode == HTTP_CODE_OK) {
                String temp = http.getString();
                return temp;
                
            }
        }
        else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }
  http.end();
}
String getCPU()  {
  http.begin("http://192.168.0.99/MikrotikAPIv2.php?get=resource&cate=cpu-load"); //HTTP
        int httpCode = http.GET();
        if (httpCode > 0) {
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);
            if (httpCode == HTTP_CODE_OK) {
                String cpu_load = http.getString();
                return cpu_load;
                
            }
        }
        else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }
  http.end();
}

String getdownload()  {
  http.begin("http://192.168.0.99/MikrotikAPIv2.php?get=monitor-wan1&cate=download"); //HTTP
        int httpCode = http.GET();
        if (httpCode > 0) {
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);
            if (httpCode == HTTP_CODE_OK) {
                String temp = http.getString();
                return temp;
                
            }
        }
        else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }
  http.end();
}

String getupload()  {
  http.begin("http://192.168.0.99/MikrotikAPIv2.php?get=monitor-wan1&cate=upload"); //HTTP
        int httpCode = http.GET();
        if (httpCode > 0) {
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);
            if (httpCode == HTTP_CODE_OK) {
                String temp = http.getString();
                return temp;
                
            }
        }
        else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }
  http.end();
}
