
// Code 1 : Sending Text (Receiver)
// Library: TMRh20/RF24 (https://github.com/tmrh20/RF24/)

#include <SPI.h>
#include "printf.h"
#include "RF24.h"
#include<SoftwareSerial.h>

SoftwareSerial espSerial(2, 3);

RF24 radio(9, 10);
uint8_t address[][6] = { "HNode", "1Node", "2Node" };
int radioNumber = 0;
bool role = false;
float payload = 0.0;

void setup() {
    Serial.begin(115200);
    espSerial.begin(115200);
    if (!radio.begin()) {
        Serial.println(F("radio hardware is not responding!!"));
        while (1) {}
    }
    Serial.print(F("radioNumber = "));
    Serial.println((int)radioNumber);
    radio.setPALevel(RF24_PA_LOW);
    radio.setPayloadSize(sizeof(payload));
    //  radio.openWritingPipe(address[radioNumber]);
    radio.openReadingPipe(1, address[1]);
    radio.openReadingPipe(2, address[2]);
    radio.startListening();

    // For debugging info
    printf_begin();             // needed only once for printing details
    //   radio.printDetails();       // (smaller) function that prints raw register values
    radio.printPrettyDetails(); // (larger) function that prints human readable data

}

void loop() {
    uint8_t pipe;
    if (radio.available(&pipe)) {              // is there a payload? get the pipe number that recieved it
        uint8_t bytes = radio.getPayloadSize();  // get the size of the payload
        radio.read(&payload, bytes);             // fetch payload from FIFO
        Serial.print(F("Received "));
        Serial.print(bytes);  // print the size of the payload
        Serial.print(F(" bytes on pipe "));
        Serial.print(pipe);  // print the pipe number
        Serial.print(F(": "));
        Serial.println(payload);  // print the payload's value
        String str = String(pipe) + String(" ") + String(payload);
        espSerial.println(str);
    }
};