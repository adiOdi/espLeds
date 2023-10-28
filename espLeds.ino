#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <math.h>
#include "Simpletimer.h"

#define INBUILT_LED 2
#include "html.h"
#include "ledHandler.h"
#include "wifiHandler.h"
#include "serverHandler.h"
// #include "buttonHandler.h"


//3v3 - red | rx - brown
//rst - gr* | io0 - black   *only to reset
//en - red  | io2 -
//tx - white| gnd - blue

Simpletimer timer1{};
Simpletimer APtimer{};

int notConnectedCount=0;

void setup(void) {
  // setup status LED
  pinMode(INBUILT_LED, OUTPUT);
  digitalWrite(INBUILT_LED, 1);

  // setupButtons();

  Serial.begin(115200);

  // Initialize LED Strip
  setupStrip();
  timer1.register_callback(draw);
  APtimer.register_callback(checkWifi);

  // setup Network
  loadCredentials();
  if(ssid==0){
    setupAP();
  } else {
    connectWifi();
  }
  if (MDNS.begin("esp8266")) { Serial.println("MDNS responder started"); }

  // setup Server
  server.on("/", handleRoot);
  server.on("/formhandler", handleForm);
  server.on("/wifi", handleWifi);
  server.on("/generate_204", handleWifi);  //Android captive portal. Maybe not needed. Might be handled by notFound handler.
  server.on("/fwlink", handleWifi);  //Microsoft captive portal. Maybe not needed. Might be handled by notFound handler.
  //server.on("/length", handleLength);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  // handle Wifi timeout
  while (WiFi.status() != WL_CONNECTED && wifiAP) {
    notConnectedCount++;
    if(notConnectedCount>20){
      setupAP();
    }
    delay(500);
    Serial.print(".");
  }
  notConnectedCount=0;

  server.handleClient();
  MDNS.update();
  timer1.run(5);
  APtimer.run(60000);
}
