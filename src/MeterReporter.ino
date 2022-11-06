/*
 * Project MeterReporter
 * Description: Takes Serial data and transform it to a web api
 * Date: 2022-11-05
 */

#include "RdWebServer.h"
#include "RdWebServerResources.h"
#include "RestAPIEndpoints.h"
#include "MeterWebResources.h"

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
  WiFi.selectAntenna(ANT_EXTERNAL);

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
  pWebServer->addStaticResources(genResourcesEx, genResourcesExCount);
  pWebServer->addRestAPIEndpoints(&restAPIEndpoints);
  pWebServer->start(webServerPort);
}

void loop() {
  pWebServer->service();
  readMeter();
}

void readMeter() {
  if (!Serial1.available()) {
    return;
  }

  digitalWrite(D7, 1);

  meterData = String("");

  while (1) {
    String line = Serial1.readStringUntil('\n');
    Log.info(line);
    meterData.concat(line);
    if (line.startsWith("!")) {
      digitalWrite(D7, 0);
      return;
    }
  }
}
