
// Code 1 : Sending Text (Receiver)
// Library: TMRh20/RF24 (https://github.com/tmrh20/RF24/)

#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

RF24 radio(9, 8); // CE, CSN
const byte address[] = { 0xCC,0xCE,0xCC,0xCE,0xCC };

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
};

void loop() {
  if (radio.available()) {
    char txt[32] = "";
    radio.read(&txt, sizeof(txt));
    if(txt == "1")
    Serial.println(txt);
  };
};
