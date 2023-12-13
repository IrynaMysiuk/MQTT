using System;
namespace FloorControlTester
{
    public class HotspotConfig {
        public String Name { get; set; }
        public String Ip { get; set; }
        public String Mask { get; set; }
        public String Login { get; set; }
        public String Password { get; set; }
    }

    public class WifiConfig {
        public string Ssid { get; set; }
        public string Password { get; set; }
    }
    public class MqttConfig {
        public String ServerPath { get; set; }
        public String Username { get; set; }
        public String Password { get; set; }
        public int Port { get; set; }
    }

    public class FloorConfig
    {
       
        public HotspotConfig Hotspot { get; set; }
        public WifiConfig Wifi { get; set; }
        public MqttConfig Mqtt { get; set; }
    }
}

