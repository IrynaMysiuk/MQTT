#include <PubSubClient.h>
#include <WiFi.h>

#include "env/Env.h"

WiFiClient espClient;
PubSubClient client(espClient);



void actionOnTemperature(float temperature) {

    AppConfig* config = Env::Instance()->GetConfigManager()->Config();
  
    float maxT = config->FloorControl.MaxTemperature;
    float minT = config->FloorControl.MinTemperature;

    float openDegree = (temperature-minT)/(maxT-minT)*180-90;

    openDegree = openDegree<-90?-90: (openDegree>90?90:openDegree);

    int openDegreeNumber = (int)openDegree;

    char message[10];

    sprintf(message, "%d", openDegreeNumber);
    client.publish(config->FloorControl.TapTopic.c_str(), message);
    Serial.print("Sending message for tap in topic: ");
    Serial.print(config->FloorControl.TapTopic);
    Serial.print(". Message: ");

    Serial.println(message);

}

void mqttMessageCallback(char* topic, byte* message, unsigned int length) {
    //Serial.println();
    Serial.print("Message arrived on topic: ");
    Serial.print(topic);
    Serial.print(". Message: ");

    String messageTemp;

    for (int i = 0; i < length; i++) {
        messageTemp += (char)message[i];
    }

    Serial.println(messageTemp);
    Serial.println();

    AppConfig* config = Env::Instance()->GetConfigManager()->Config();


    if (strcmp(topic, config->FloorControl.TemperatureTopic.c_str()) == 0 ) {
        Serial.println("processing temperature...");
        float temp = atof(messageTemp.c_str());
         actionOnTemperature(temp);
    }
}

void initMQTT()
{
    AppConfig* config = Env::Instance()->GetConfigManager()->Config();
     
    client.setServer(config->Mqtt.ServerPath.c_str(), config->Mqtt.Port);
    client.setCallback(mqttMessageCallback);
}

void tryReconnect(int numberTries = 1)  {
    if (!client.connected()){
        Env::Instance()->GetLogger()->LogInfoLn("Attempting MQTT connection...");
        AppConfig* config = Env::Instance()->GetConfigManager()->Config();
        if (client.connect("EspFloorController", config->Mqtt.Username.c_str(), config->Mqtt.Password.c_str())){
            Env::Instance()->GetLogger()->LogInfoLn("Connected to MQTT");

            Env::Instance()->GetLogger()->LogInfo("Subscribed to topic: ");
            Env::Instance()->GetLogger()->LogInfoLn(config->FloorControl.TemperatureTopic.c_str());
            client.subscribe(config->FloorControl.TemperatureTopic.c_str());
        } else{
            //TODO:add logger additional methods
            Serial.print("failed to connect to MQTT, rc=");
            Serial.println(client.state());
        }
    }
}

void mqttLoopMessages() {
    if (!client.connected()) {
        tryReconnect();
    }
    if (client.connected()){
        client.loop();
    }
}