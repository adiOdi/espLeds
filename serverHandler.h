ESP8266WebServer server(80);
void handleRoot() {
  digitalWrite(INBUILT_LED, 0);
  server.send(200, "text/html", htmlText);
  Serial.println("rootsite");
  digitalWrite(INBUILT_LED, 1);
}
void handleForm(){
  digitalWrite(INBUILT_LED, 0);
  for (uint8_t i = 0; i < server.args(); i++) {
    if (server.argName(i) == "n")
    {
      n = server.arg(i).toInt();
    }
    else if (server.argName(i) == "x")
    {
      x = server.arg(i).toFloat();
    }
    else if (server.argName(i) == "y")
    {
      y = server.arg(i).toFloat();
    }
    else if (server.argName(i) == "b")
    {
      b = server.arg(i).toInt();
    }
  }
  server.send(204);
  Serial.printf("params: n:%d x:%f y:%f b:%d\n", n,x,y,b);
  digitalWrite(INBUILT_LED, 1);
}
void handleWifi(){
  digitalWrite(INBUILT_LED, 0);
  for (uint8_t i = 0; i < server.args(); i++) {
    if (server.argName(i) == "ssid")
    {
      server.arg(i).toCharArray(ssid, 32);
    }
    else if (server.argName(i) == "pwd")
    {
      server.arg(i).toCharArray(password, 32);
    }
  }
  saveCredentials();
  server.send(204);
  Serial.printf("WiFi: ssid:%s password:%s\n", ssid, password);
  digitalWrite(INBUILT_LED, 1);
  connectWifi();
}
void handleNotFound() {
  digitalWrite(INBUILT_LED, 0);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) { message += " " + server.argName(i) + ": " + server.arg(i) + "\n"; }
  server.send(404, "text/plain", message);
  Serial.println(message);
  digitalWrite(INBUILT_LED, 1);
}