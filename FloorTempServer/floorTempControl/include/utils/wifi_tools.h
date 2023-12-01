#include <Wifi.h>
#include "env/Env.h"



bool initWiFiConnection(const char* ssid, const char* password, int maxTries = 10, bool setupMode=true) {
  if (setupMode){
  WiFi.mode(WIFI_STA);
  }

  WiFi.disconnect();

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  int counter =0;
  
  while (WiFi.status() != WL_CONNECTED && counter<maxTries) {
    Serial.print('.');
    delay(1000);
    counter++;
  }
  Serial.println();
  if (WiFi.status()!= WL_CONNECTED) {
    
    Serial.println("Connection to STA failed");
    return false;
  }
  Serial.print("Connection to STA is successful. STA WiFi IP address: ");
  Serial.println(WiFi.localIP());
  return true;
}


void initWiFiAp(AppConfig* config, bool initMode = true) {
  if (initMode){
    WiFi.mode(WIFI_AP);
  }

  WiFi.softAP(config->Hotspot.Name, config->Hotspot.Password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
}

void initWiFiApAndSta(AppConfig* config) {
  WiFi.disconnect();
  WiFi.mode(WIFI_AP_STA);

  initWiFiConnection(config->Wifi.Ssid.c_str(), config->Wifi.Password.c_str(), 5, false);

  initWiFiAp(config, false);


}

void initWiFiOnStartup() {
  Env* env = Env::Instance();
  AppConfig* config = env->GetConfigManager()->Config();

  if (!initWiFiConnection(config->Wifi.Ssid.c_str(), config->Wifi.Password.c_str(), 5)){ 
    initWiFiAp(config);
  } else {
    initWiFiApAndSta(config);
  }
}

