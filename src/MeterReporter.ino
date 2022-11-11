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

  while (1) {
    if (WiFi.ready())
      break;
    delay(1000);
  }

  // Add endpoint
  restAPIEndpoints.addEndpoint("status", RestAPIEndpointDef::ENDPOINT_CALLBACK, meterStatus, "", "");

  // Construct server
  pWebServer = new RdWebServer();
  pWebServer->addStaticResources(genResourcesEx, genResourcesExCount);
  pWebServer->addRestAPIEndpoints(&restAPIEndpoints);
  pWebServer->start(webServerPort);

  // Turn off LED to preserve power
  RGB.control(true);
  RGB.color(0, 0, 0);
}

void loop() {
  pWebServer->service();
  readMeter();
  delay(10);
}

void readMeter() {
  if (!Serial1.available()) {
    return;
  }

  meterData = String("");

  while (1) {
    String line = Serial1.readStringUntil('\n');
    meterData.concat(line);
    if (line.startsWith("!")) {
      return;
    }
  }
}

/**
 * Define our own Serial1 buffer so we can have a longer
 * delay in the loop to preserve power
 */
hal_usart_buffer_config_t acquireSerial1Buffer() {
  const size_t bufferSize = 1024 * sizeof(uint16_t);
  hal_usart_buffer_config_t config = {
      .size = sizeof(hal_usart_buffer_config_t),
      .rx_buffer = new (std::nothrow) uint8_t[bufferSize],
      .rx_buffer_size = bufferSize,
      .tx_buffer = new (std::nothrow) uint8_t[bufferSize],
      .tx_buffer_size = bufferSize
  };
  return config;
}
