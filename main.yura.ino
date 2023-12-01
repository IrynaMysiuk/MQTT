
#include <WiFi.h>
#include <PubSubClient.h>
#include "wifi.connect.h"
#include <ESP32Servo.h>

//Servo
Servo myServo;
int servoPin = 13;

// WiFi
const char *ssid = "Virus";         // Enter your WiFi name
const char *password = "pokemon7";  // Enter WiFi password

// MQTT Broker
const char *mqtt_broker = "perfect-politician.cloudmqtt.com";
const char *topic = "Feia_test";
const char *mqtt_username = "gelphadi";
const char *mqtt_password = "oYMgWJETz_0N";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);


void setup() {
    // Set software serial baud to 115200;
    Serial.begin(115200);
    // Connecting to a WiFi network
    WiFi.begin(ssid, password);
   
    Serial.println("Connected to the Wi-Fi network");
    //connecting to a mqtt broker
    client.setServer(mqtt_broker, mqtt_port);
    client.setCallback(callback);
    while (!client.connected()) {
        String client_id = "esp32-client-";
        client_id += String(WiFi.macAddress());
        Serial.printf("The client %s connects to the public MQTT broker\n", client_id.c_str());
        if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
            Serial.println("Public EMQX MQTT broker connected");
        } else {
            Serial.print("failed with state ");
            Serial.print(client.state());
            delay(2000);
        }
    }
    // Publish and subscribe
    client.publish(topic, "Hi, I'm ESP32 ^^");
    client.subscribe(topic);
}

void callback(char *topic, byte *payload, unsigned int length) {
  client.subscribe(topic);
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    for (int i = 0; i < length; i++) {
        Serial.print((char) payload[i]);
    }
    Serial.println();
    Serial.println("-----------------------");
}

void loop() {
  client.publish(topic, "hi there");
  client.subscribe(topic);
  client.loop();
}
