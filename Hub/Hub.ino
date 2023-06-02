//************************************************************
// https://gitlab.com/painlessMesh/painlessMesh/wikis/bridge-between-mesh-and-another-network
//************************************************************
#include "painlessMesh.h"
#include "WIFI_PASS.h"

#define   MESH_PREFIX     "HUB_TEST"
#define   MESH_PASSWORD   "12345678"
#define   MESH_PORT       5555

#define   STATION_PORT     8080
uint8_t   station_ip[4] =  {192,168,1,103};

void receivedCallback( uint32_t from, String &msg );

painlessMesh  mesh;

void setup() {
  Serial.begin(115200);
  mesh.setDebugMsgTypes( ERROR | STARTUP | CONNECTION );
  // IMPORTANT!!! Channel set to 6. Make sure to use the same channel for your mesh and for you other
  mesh.init( MESH_PREFIX, MESH_PASSWORD, MESH_PORT, WIFI_AP_STA, 6);
  mesh.stationManual(STATION_SSID, STATION_PASSWORD, STATION_PORT, station_ip);
  mesh.setRoot(true);
  mesh.setContainsRoot(true);
  mesh.onReceive(&receivedCallback);
}

void loop() {
  mesh.update();
}

void receivedCallback( uint32_t from, String &msg ) {
  Serial.printf("bridge: Received from %u msg=%s\n", from, msg.c_str());
}
