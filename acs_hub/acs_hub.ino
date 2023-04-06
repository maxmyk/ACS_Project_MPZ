#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "DHT.h"
#include <WiFiClient.h>
#include <Wire.h>
#include "WIFI_PASS.h"

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
int humidity, temperature;

const char* host = "http://192.168.43.182:8080/";
const char* path = "http://192.168.43.182:8080/api/v1/collect_data";

int readTmp() {
  return dht.readTemperature();
}

int readHum() {
  return dht.readHumidity();
}

void setup() {
  Serial.begin(9600);
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

void sendJson() {
  WiFiClient client;
  HTTPClient http;
  http.begin(client, path);
  http.addHeader("Content-Type", "application/json");
  int tmp = readTmp(), hum = readHum();
  if(isnan(tmp) && isnan(hum)){
    tmp = 0;
    hum = 0;
  }
  String json = "{\"id\": 2, \"temperature\": " + String(tmp) + ", \"volume\": " + String(tmp) + ", \"humidity\": " + String(hum) + "}";
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
  delay(2500);
}
