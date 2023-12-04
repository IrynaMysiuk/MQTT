void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin("PointNet_05E4", "dfvt55tr");
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}