
// Code 1 : Sending Text (Transmitter)
// Library: TMRh20/RF24 (https://github.com/tmrh20/RF24/)

#include <SPI.h>
#include "printf.h"
#include "RF24.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define defaultPayloadSize 24

RF24 radio(9, 10);
uint8_t address[][6] = { "0Node", "1Node", "2Node", "3Node" };
int radioNumber = 2;
bool role = true;
String payload = "";
#define DHTPIN 2
#define DHTTYPE    DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(115200);
    if (!radio.begin()) {
        Serial.println(F("radio hardware is not responding!!"));
        while (1) {}
    }
    Serial.print(F("radioNumber = "));
    Serial.println((int)radioNumber);
    radio.setPALevel(RF24_PA_MAX);
    radio.setPayloadSize(defaultPayloadSize); // Set payload size correctly
    radio.openWritingPipe(address[radioNumber]);

    // For debugging info
    printf_begin();
    radio.printPrettyDetails();
    dht.begin();
}



void loop() {
    unsigned long start_timer = micros();
    
    float temperature = dht.readTemperature(); // Read temperature
    float humidity = dht.readHumidity(); // Read humidity // Update payload with new sensor values
    payload = "id:" + String(radioNumber) + ";D{T:" + String(temperature) + ",H:" + String(humidity) + "};";
    Serial.println(payload);
    Serial.println(payload.length());
    Serial.println();
    bool report = radio.write((uint8_t *)payload.c_str(), radio.getPayloadSize());
    unsigned long end_timer = micros();

//    Serial.println(sizeof(charPayload));
    Serial.println();
    if (report) { 
        Serial.print(F("Transmission successful! "));
        Serial.print(F("Time to transmit = "));
        Serial.print(end_timer - start_timer);
        Serial.print(F(" us. Sent: "));
        Serial.println(payload);
    } else {
        Serial.println(F("Transmission failed or timed out"));
    }

    delay(1000);
}
