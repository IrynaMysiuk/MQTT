void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin("wifi_name", "wifi_password");
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}
