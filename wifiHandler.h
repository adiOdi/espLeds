#include <EEPROM.h>
char ssid[32] = "";
char password[32] = "";
bool wifiAP = false; //wifi or ap
void loadCredentials() {
  EEPROM.begin(512);
  EEPROM.get(0, ssid);
  EEPROM.get(0+sizeof(ssid), password);
  char ok[2+1];
  EEPROM.get(0+sizeof(ssid)+sizeof(password), ok);
  EEPROM.end();
  if (String(ok) != String("OK")) {
    ssid[0] = 0;
    password[0] = 0;
  }
  Serial.println("Recovered credentials:");
  Serial.println(ssid);
  Serial.println(strlen(password)>0?"********":"<no password>");
}

/** Store WLAN credentials to EEPROM */
void saveCredentials() {
  EEPROM.begin(512);
  EEPROM.put(0, ssid);
  EEPROM.put(0+sizeof(ssid), password);
  char ok[2+1] = "OK";
  EEPROM.put(0+sizeof(ssid)+sizeof(password), ok);
  EEPROM.commit();
  EEPROM.end();
}

void connectWifi(){
  Serial.println("connecting to wifi");
  WiFi.softAPdisconnect();
  WiFi.disconnect();
  loadCredentials();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  wifiAP=true;
}

void setupAP(){
  Serial.println("creating AP");
  WiFi.disconnect();
  WiFi.mode(WIFI_AP);
  WiFi.softAP("espLed", "milkismurder");
  wifiAP=false;
}

void checkWifi(){
  if(!wifiAP){ //if in AP mode
    connectWifi();
  }
}