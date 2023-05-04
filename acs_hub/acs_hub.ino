#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Wire.h>
#include "WIFI_PASS.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Wire.h>

const char* host = "http://192.168.43.182:8080/";
const char* path = "http://192.168.43.182:8080/api/v1/collect_data";

int tmp = 0;
int hum = 0;

int readTmp() {
    return Serial.read();
}

int readHum() {
    return Serial.read();
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
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
    }
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void sendJson(int tmp, int hum) {
    WiFiClient client;
    HTTPClient http;
    http.begin(client, path);
    http.addHeader("Content-Type", "application/json");

    String json = "{\"id\": 2, \"temperature\": " + String(tmp) + ", \"humidity\": " + String(hum) + "}";
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

}

void serialEvent() {
    if (Serial.available())
    {
        String str = Serial.readString();
        int id = str.substring(0, str.indexOf(' ')).toInt();
        int idata = str.substring(str.indexOf(' ') + 1).toInt();
        Serial.println(id);
        Serial.println(idata);
        Serial.println("Got something");
        if (id == 1) {
            tmp = idata;
        }
        if (id == 2) {
            hum = idata;
        }
        if (tmp != 0 && hum != 0) {
            Serial.println((String)tmp + " " + (String)hum);
            Serial.println("Sending data...");
            sendJson(tmp, hum);
            tmp = 0;
            hum = 0;
        }
    }
}
