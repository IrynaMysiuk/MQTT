#include "WiFi.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include "wifi_connect.h"
#include "DHTesp.h"
DHTesp dht;

const char *ssid = "your_wifi_name"; 
const char *password = "your_wifi_password"; 

const char *mqtt_broker = "perfect-politician.cloudmqtt.com";
const char *topic = "Feia_test";
const char *mqtt_username = "gelphadi";
const char *mqtt_password = "oYMgWJETz_0N";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  initWiFi();
  delay(100);
  client.setServer(mqtt_broker, mqtt_port);

  client.setCallback(callback);  //upload

  while (!client.connected()) {
    String client_id = "esp32-client-";
    client_id += String(WiFi.macAddress());

    Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("Public emqx mqtt broker connected");
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }

  Serial.println("Setup done");
  dht.setup(27, DHTesp::DHT11);
  Serial.println();
  delay(1000);
}

void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  Serial.println("-----------------------");
}

void loop() {
  float temperature = dht.getTemperature();
  float humidity = dht.getHumidity();

  Serial.print("Temperature: ");
  Serial.println(temperature);
  Serial.print("Humidity: ");
  Serial.println(humidity);

  delay(2000);
  String messageTemp;

  char message[100];
  sprintf(message, "%f", temperature);
  client.publish("floor/temperature", message);
  Serial.print("Sending message for tap: ");
  Serial.println(message);

  client.publish(topic, "MY TEMPERATURE");
  client.subscribe(topic);
  client.subscribe("test");
  client.loop();
  delay(2000);
}
