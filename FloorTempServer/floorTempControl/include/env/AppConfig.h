#include <Arduino.h>

struct HotspotConfig {
    public:
    String Name;
    String Ip;
    String Mask;
    String Login;
    String Password;
};

struct WifiConfig {
    String Ssid;
    String Password;
};

struct MqttConfig {
  String ServerPath;
  String Username;
  String Password;
  int Port;
};

struct FloorControlConfig{
    String TemperatureTopic;
    String TapTopic;
    int MinTemperature;
    int MaxTemperature;
};


struct AppConfig{
    HotspotConfig Hotspot;
    WifiConfig Wifi;
    MqttConfig Mqtt;
    FloorControlConfig FloorControl;
};
