/*
 * Project MeterReporter
 * Description:
 * Author:
 * Date:
 */

 /* Particle Photon with MAC 3c:e1:a1:5b:7b:6b statically mapped to 192.168.1.202
  * Status of the Meter is accessed through
  * http://192.168.1.202/status
  */

#include "RdWebServer.h"
#include "RdWebServerResources.h"
#include "RestAPIEndpoints.h"

SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(AUTOMATIC);

SerialLogHandler logHandler(LOG_LEVEL_INFO);

int webServerPort = 80;

RestAPIEndpoints restAPIEndpoints;
RdWebServer* pWebServer = NULL;

String meterData = String("");

void meterStatus(RestAPIEndpointMsg& apiMsg, String& retStr) {
  retStr = meterData;
}

void setup() {
  // RX pin on the Photon
  Serial1.begin(115200, SERIAL_8N1);

  pinMode(D7, OUTPUT);
  digitalWrite(D7, 0);

  delay(3000);
  Log.info("Meter status reporter");

  while (1) {
    if (WiFi.ready())
      break;
    delay(5000);
    Log.warn("Waiting for WiFi");
  }

  // Add endpoint
  restAPIEndpoints.addEndpoint("status", RestAPIEndpointDef::ENDPOINT_CALLBACK, meterStatus, "", "");

  // Construct server
  pWebServer = new RdWebServer();
  pWebServer->addRestAPIEndpoints(&restAPIEndpoints);
  pWebServer->start(webServerPort);
}

void loop() {
  pWebServer->service();
  readMeter();
}

void readMeter() {
  if (Serial1.available() == -1) {
    return;
  }

  digitalWrite(D7, 1);

  while (1) {
    String line = Serial1.readString();
    Log.info(line);
    if (line.startsWith("!")) {
      digitalWrite(D7, 0);
      return;
    }
    meterData.concat(line);
  }
}
