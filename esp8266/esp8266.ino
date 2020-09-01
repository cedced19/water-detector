#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

MDNSResponder mdns;

const int detect =  2;

const char* ssid = "wifi_name";
const char* password = "wifi_pwd";
 
void setup () {
  pinMode(detect, INPUT); 
  pinMode(1, OUTPUT);  
  WiFi.begin(ssid, password);
  digitalWrite(1, LOW);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
  digitalWrite(1, HIGH); 
  WiFi.mode(WIFI_STA);
  WiFi.hostname("esp-water-detector"); 
  WiFi.setAutoReconnect(true);
}

// Timer
unsigned long timer = 0;

void loop () {
  if (WiFi.status() == WL_CONNECTED) {
    if (digitalRead(detect)) { 
      HTTPClient http;  
      http.begin("http://192.168.0.40:7770/water-detected"); // URL to request
      http.GET();                                                                 
      http.end(); 
    } else {
      if(millis() > timer + 300000){
        HTTPClient http;  
        http.begin("http://192.168.0.40:7770/water-detector-connected"); // URL to request
        http.GET();                                                                 
        http.end();
        timer = millis();
      } 
    }
  } else {
    digitalWrite(1, LOW);
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
    }
    digitalWrite(1, HIGH); 
  }
  delay(60000);
}
