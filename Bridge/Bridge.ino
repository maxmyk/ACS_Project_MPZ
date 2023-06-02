#include <SoftwareSerial.h>
#include "painlessMesh.h"
#include "WIFI_PASS.h"

SoftwareSerial mySerial(D5, D6);

#define   MESH_PREFIX     "HUB_TEST"
#define   MESH_PASSWORD   "12345678"
#define   MESH_PORT       5555

void receivedCallback( uint32_t from, String &msg );

painlessMesh  mesh;

void setup() {
  Serial.begin(115200);
  mySerial.begin(115200);
  mesh.setDebugMsgTypes( ERROR | STARTUP | CONNECTION );
  mesh.init( MESH_PREFIX, MESH_PASSWORD, MESH_PORT, WIFI_AP_STA, 1 );
  mesh.setRoot(true);
  mesh.setContainsRoot(true);
  mesh.onReceive(&receivedCallback);
}

void loop() {
  mesh.update();
}

void receivedCallback( uint32_t from, String &msg ) {
  Serial.printf("bridge: Received from %u msg=%s\n", from, msg.c_str());
  mySerial.printf("%u;%s\n", from, msg.c_str());
}
