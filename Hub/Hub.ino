#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <SoftwareSerial.h>
#include "WIFI_PASS.h"

SoftwareSerial mySerial(D5, D6);

const char* host = "http://192.168.1.103:8080/";
const char* path = "http://192.168.1.103:8080/api/v1/collect_data";

void setup() {
    Serial.begin(115200);
    mySerial.begin(115200);
    Serial.println("Booting");
    WiFi.mode(WIFI_STA);
    WiFi.begin(STATION_SSID, STATION_PASSWORD);
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("Connection Failed! Rebooting...");
        delay(5000);
        ESP.restart();
    }
    Serial.println("Ready");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void sendJson(int hub_id, int id, float tmp, float hum) {
    WiFiClient client;
    HTTPClient http;
    http.begin(client, path);
    http.addHeader("Content-Type", "application/json");
    String json = "{\"hub_id\": "+String(hub_id)+", \"id\": "+String(id)+", \"temperature\": " + String(tmp) + ", \"humidity\": " + String(hum) + "}";
    Serial.println(json);
    int httpCode = http.POST(json);
    String payload = http.getString();
    Serial.println(httpCode);
    Serial.println(http.errorToString(httpCode).c_str());
    Serial.println(payload);
    http.end();

    delay(500);
}

void loop() {
    if (mySerial.available())
    {
        String str = mySerial.readStringUntil('\n');
        Serial.println(str);
        parseData(str);
    }
}

struct SensorData {
  int id;
  float temperature;
  float humidity;
};

void parseData(const String& data) {
  int startIndex = 0;
  int endIndex;

  int hub_id = data.substring(0, data.indexOf(';')).toInt();

  while (true) {
    int idStart = data.indexOf("id:", startIndex);
    if (idStart == -1) {
      break;  // No more IDs found
    }

    int idEnd = data.indexOf(";", idStart);
    if (idEnd == -1) {
      break;  // Invalid format
    }

    String idString = data.substring(idStart + 3, idEnd);
    int id = idString.toInt();

    endIndex = data.indexOf("id:", idEnd);
    if (endIndex == -1) {
      endIndex = data.length();
    }

    String section = data.substring(idEnd + 1, endIndex);

    SensorData sensorData;
    sensorData.id = id;

    int temperatureStart = section.indexOf("T:");
    int temperatureEnd = section.indexOf(",", temperatureStart);
    if (temperatureStart != -1 && temperatureEnd != -1) {
      String temperatureString = section.substring(temperatureStart + 2, temperatureEnd);
      sensorData.temperature = temperatureString.toFloat();
    }

    int humidityStart = section.indexOf("H:");
    int humidityEnd = section.indexOf("}", humidityStart);
    if (humidityStart != -1 && humidityEnd != -1) {
      String humidityString = section.substring(humidityStart + 2, humidityEnd);
      sensorData.humidity = humidityString.toFloat();
    }

    // Do something with the sensorData struct
    Serial.print("ID: ");
    Serial.print(sensorData.id);
    if (temperatureStart != -1 && temperatureEnd != -1) {
      Serial.print(", Temperature: ");
      Serial.print(sensorData.temperature);
    }
    if (humidityStart != -1 && humidityEnd != -1) {
      Serial.print(", Humidity: ");
      Serial.print(sensorData.humidity);
    }
    Serial.println();

    sendJson(hub_id, sensorData.id, sensorData.temperature, sensorData.humidity);

    startIndex = endIndex;
  }
}
