#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
//#include "DHT.h"
#include <WiFiClient.h>
#include <Wire.h>

//#define DHTPIN D1
//#define DHTTYPE DHT11
//DHT dht(DHTPIN, DHTTYPE);
int humidity, temperature;

const char* ssid = "iPhone 13 Pro Max";
const char* password = "12312312345";

const char* host = "http://172.20.10.2:8080/";
const char* path = "http://172.20.10.2:8080/api/v1/collect_data";


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


void setup() {
  Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

// data = {
//        "id": id, // we will use EEPROM to store unique ID
//        "temperature": readTmp(),
//        "volume": readTmp(),
//        "humidity": readHum(),
//    }

void sendJson() {
  WiFiClient client;
  HTTPClient http;
  http.begin(client, path);
  http.addHeader("Content-Type", "application/json");
  String json = "{\"id\": 1, \"temperature\": " + readTmp() + ", \"volume\": " + readTmp() + ", \"humidity\": " + readHum() + "}";
  Serial.println(json);
  int httpCode = http.POST(json);
  String payload = http.getString();
  Serial.println(httpCode);
  Serial.println(http.errorToString(httpCode).c_str());
  Serial.println(payload);
  http.end();
}

void loop() {
  sendJson();
  delay(5000);
}
