#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const int detect =  2;

const char* ssid = "wifi_name";
const char* password = "wifi_pwd";
 
void setup () {
  pinMode(detect, INPUT);  
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
 
}

void loop () {
  if (WiFi.status() == WL_CONNECTED) {
    if (digitalRead(detect)) { 
      HTTPClient http;  
   
      http.begin("http://192.168.0.47:8000/detected"); // URL to request
      http.GET();                                                                 
   
      http.end(); 
    }
  }
  delay(10000); // delay between two detections 
}
