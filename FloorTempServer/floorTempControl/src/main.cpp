#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "Adafruit_Sensor.h"
#include "DHT.h"
#include "AsyncTCP.h"
#include "ESPAsyncWebServer.h"


#include "utils/wifi_tools.h"
#include "env/Env.h"
#include "utils/filesystem/LittlefsFileManager.h"
#include "webServer/webServer.h"
#include "utils/mqtt_tools.h"

Env* env;
LittlefsFileManager* fm;
WebServer* server;

void initEnv() {
  Serial.println("Im here");
  env = Env::Instance();
  env->GetLogger()->ChangeLogLevel(LOG_ALL);
  fm=new LittlefsFileManager(env->GetLogger());
  fm->InitFileSystem(false);

   env->initFileManager(fm); 
   
   Serial.println(fm->ReadFileRaw("/config.json"));

   Serial.println("start config init");
   env->initConfig("/config.json","/defaultconfig.json");
}


/*TESTING PURPOSES BLOCK*/
long lastMsg = 0;
char msg[50];
int value = 0;
int msgCount = 0;
int maxMessages = 10;

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
/*END TESTING PURPOSES BLOCK*/


void setup() {
  Serial.begin(115200);

  //setupWifiAp();
  
  Serial.println("Start app startup...");
  initEnv();
  Serial.println("End env initiation...");
  
  Serial.println("init WiFi connection and/or AP");
  initWiFiOnStartup();

  Serial.println("Start web server init...");
  server = new WebServer(env->GetLogger());
  server->initWebServer();
  Serial.println("Server is up and running");

  Serial.println("Init MQTT");
  initMQTT();


/*TESTING PURPOSES BLOCK*/
  dht.begin();

/*END TESTING PURPOSES BLOCK*/

  delay(2000);
}


void loop() {
  mqttLoopMessages();
  Serial.println("Idling");
  delay(2000);


/*TESTING PURPOSES BLOCK*/
  long now = millis();
  if (now - lastMsg > 5000) {
    if (msgCount < maxMessages) {
      msgCount++;

      char message[100];
      //sprintf(message, "this is test message %d out of %d. Yura don't be silent. Ira, be careful with videos", msgCount, maxMessages);
      //client.publish("test", message);
      sprintf(message, "%d", (int)dht.readTemperature());
      client.publish("floor/temperature", message);
      Serial.print("Sending message: ");
      Serial.println(message);

    } else {
      Serial.println("Limit reached. Skipping sending message");
    }

    lastMsg = now;
  }
  /*END TESTING PURPOSES BLOCK*/

}
