#include <ESP8266WiFi.h>
#include "ESPAsyncWebServer.h"
//#include "DHT.h"
#include <Wire.h>

//#define DHTPIN D1
//#define DHTTYPE DHT11 
//DHT dht(DHTPIN, DHTTYPE);
int humidity, temperature;

const char* ssid = "HUB";
const char* password = "10100101";

AsyncWebServer server(80);

//String readTmp() {
//  return String(dht.readTemperature());
//}
//
//String readHum() {
//  return String(dht.readHumidity());
//}

String readTmp() {
  return String(analogRead(A0));
}

String readHum() {
  return String(digitalRead(D1));
}

void setup(){
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("\nAP IP address: ");
  Serial.println(IP);

  dht.begin();

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", "I'm up and running!");
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readHum().c_str());
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readTmp().c_str());
  });
  server.begin();
}
 
void loop(){}
