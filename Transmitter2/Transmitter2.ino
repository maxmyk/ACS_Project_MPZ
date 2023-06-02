
// Code 1 : Sending Text (Transmitter)
// Library: TMRh20/RF24 (https://github.com/tmrh20/RF24/)

#include <SPI.h>
#include "printf.h"
#include "RF24.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

RF24 radio(9, 10);
uint8_t address[][6] = { "HNode", "1Node", "2Node" };
int radioNumber = 2;
bool role = true;
float payload = 0.0;
#define DHTPIN 2
#define DHTTYPE    DHT11
DHT dht(DHTPIN, DHTTYPE);


void setup() {
    Serial.begin(115200);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
    }
    if (!radio.begin()) {
        Serial.println(F("radio hardware is not responding!!"));
        while (1) {}
    }
    Serial.print(F("radioNumber = "));
    Serial.println(radioNumber);
    radio.setPALevel(RF24_PA_LOW);
    radio.setPayloadSize(sizeof(payload));
    radio.openWritingPipe(address[radioNumber]);

    // For debugging info
    printf_begin();             // needed only once for printing details
    //   radio.printDetails();       // (smaller) function that prints raw register values
    radio.printPrettyDetails(); // (larger) function that prints human readable data
    dht.begin();
    //  sensor_t sensor;
    //  dht.temperature().getSensor(&sensor);
    float h = dht.readHumidity();
    float t = dht.readTemperature();

}

void loop() {
    unsigned long start_timer = micros();
    bool report = radio.write(&payload, sizeof(float));
    unsigned long end_timer = micros();
    if (report) {
        Serial.print(F("Transmission successful! "));
        Serial.print(F("Time to transmit = "));
        Serial.print(end_timer - start_timer);
        Serial.print(F(" us. Sent: "));
        Serial.println(payload);
        payload = dht.readHumidity();
    } else {
        Serial.println(F("Transmission failed or timed out"));
    }
    delay(1000);
};
