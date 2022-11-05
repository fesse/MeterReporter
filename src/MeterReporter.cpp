/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/home/mathias/projects/MeterReporter/src/MeterReporter.ino"
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

  /**
 /LGF5E360

 0-0:1.0.0(221105140250W)
 1-0:1.8.0(00001071.363*kWh)
 1-0:2.8.0(00000275.038*kWh)
 1-0:3.8.0(00000182.031*kVArh)
 1-0:4.8.0(00000042.767*kVArh)
 1-0:1.7.0(0000.235*kW)
 1-0:2.7.0(0000.000*kW)
 1-0:3.7.0(0000.000*kVAr)
 1-0:4.7.0(0000.222*kVAr)
 1-0:21.7.0(0000.043*kW)
 1-0:22.7.0(0000.000*kW)
 1-0:41.7.0(0000.000*kW)
 1-0:42.7.0(0000.101*kW)
 1-0:61.7.0(0000.293*kW)
 1-0:62.7.0(0000.000*kW)
 1-0:23.7.0(0000.000*kVAr)
 1-0:24.7.0(0000.025*kVAr)
 1-0:43.7.0(0000.000*kVAr)
 1-0:44.7.0(0000.170*kVAr)
 1-0:63.7.0(0000.000*kVAr)
 1-0:64.7.0(0000.026*kVAr)
 1-0:32.7.0(229.3*V)
 1-0:52.7.0(228.6*V)
 1-0:72.7.0(231.3*V)
 1-0:31.7.0(000.2*A)
 1-0:51.7.0(000.8*A)
 1-0:71.7.0(001.2*A)
 !2132
 */

#include "RdWebServer.h"
#include "RdWebServerResources.h"
#include "RestAPIEndpoints.h"

void meterStatus(RestAPIEndpointMsg& apiMsg, String& retStr);
void setup();
void loop();
void readMeter();
#line 50 "/home/mathias/projects/MeterReporter/src/MeterReporter.ino"
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
