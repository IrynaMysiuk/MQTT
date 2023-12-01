#ifndef _CONFIG_MANAGER_H_

#define _CONFIG_MANAGER_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "env/AppConfig.h"
#include "utils/filesystem/FileManager.h"
#include "env/Logger.h"

class ConfigManager
{
private:
    AppConfig *_config = nullptr;
    FileManager *_fileManager;
    Logger *_logger;

    // Properties
public:
    AppConfig *Config()
    {
        return _config;
    };

public:
    ConfigManager(FileManager* fileManager, Logger* logger) : _fileManager(fileManager), _logger(logger)
    {
        _config = new AppConfig();
    }
    ~ConfigManager()
    {
        if (_config != nullptr)
        {
            delete _config;
            _config = nullptr;
        }
    }

    bool initConfig(const char *configPath)
    {
        _logger->LogInfoLn("starting read file");
        String fileContents = _fileManager->ReadFileRaw(configPath);

        if (strcmp(fileContents.c_str(), "")==0)
        {
            return false;
        }

        _logger->LogInfoLn("starting deserialization");
       

        return loadConfigFromJsonString(fileContents);
    }

    void saveConfig(const char *filePath)
    {
        String jsonContents = configAsJsonString();

        if (strcmp(jsonContents.c_str(), "")!=0){
              _fileManager->WriteFileRaw(filePath, jsonContents);
        }
    }

    String configAsJsonString() {
        DynamicJsonDocument doc(1024);

        doc.createNestedObject("hotspot");
        doc["hotspot"]["name"] = _config->Hotspot.Name;
        doc["hotspot"]["ip"] = _config->Hotspot.Ip;
        doc["hotspot"]["mask"] = _config->Hotspot.Mask;
        doc["hotspot"]["login"] = _config->Hotspot.Login;
        doc["hotspot"]["password"] = _config->Hotspot.Password;
        _logger->LogInfoLn(_config->Hotspot.Name.c_str());
        _logger->LogInfoLn(_config->Hotspot.Ip.c_str());

        JsonObject wifi = doc.createNestedObject("wifi");
        doc["wifi"]["ssid"] = _config->Wifi.Ssid;
        doc["wifi"]["password"] = _config->Wifi.Password;

        doc.createNestedObject("mqtt");
        doc["mqtt"]["serverPath"]= _config->Mqtt.ServerPath;
        doc["mqtt"]["username"]= _config->Mqtt.Username;
        doc["mqtt"]["password"]= _config->Mqtt.Password;
        doc["mqtt"]["port"]= _config->Mqtt.Port;

        doc.createNestedObject("floorControl");
        doc["floorControl"]["temperatureTopic"]= _config->FloorControl.TemperatureTopic;
        doc["floorControl"]["tapTopic"]= _config->FloorControl.TapTopic;
        doc["floorControl"]["minTemperature"]= _config->FloorControl.MinTemperature;
        doc["floorControl"]["maxTemperature"]= _config->FloorControl.MaxTemperature;



        String jsonContents;
        // Serialize JSON to file
        if (serializeJson(doc, jsonContents) == 0)
        {
            _logger->LogErrorLn("Failed to serialize config JSON");
            return "";
        }

        return jsonContents;
    }

    bool loadConfigFromJsonString(String configJson, bool saveToFile=false){
        StaticJsonDocument<1024> doc;

        DeserializationError error = deserializeJson(doc, configJson.c_str(),DeserializationOption::NestingLimit(5));
        if (error.c_str() != "Ok")
        {
            _logger->LogError("failed to deserialize config: ");
            _logger->LogErrorLn(error.c_str());
            return false;
        }

        // Hotspot config
        _config->Hotspot.Name = String(doc["hotspot"]["name"] | "");
        _config->Hotspot.Ip = String(doc["hotspot"]["ip"] | "");
        _config->Hotspot.Mask = String(doc["hotspot"]["mask"]| "");
        _config->Hotspot.Login = String(doc["hotspot"]["login"]| "");
        _config->Hotspot.Password = String(doc["hotspot"]["password"]| "");
        // WifiConfig
        _config->Wifi.Ssid = String(doc["wifi"]["ssid"]| "");
        _config->Wifi.Password = String(doc["wifi"]["password"]| "");
        // MqttConfig
        _config->Mqtt.ServerPath = String(doc["mqtt"]["serverPath"]| "");
        _config->Mqtt.Username = String(doc["mqtt"]["username"]| "");
        _config->Mqtt.Password = String(doc["mqtt"]["password"]| "");
        _config->Mqtt.Port = doc["mqtt"]["port"] | 443;
        //FloorControlConfig
        _config->FloorControl.TemperatureTopic=String(doc["floorControl"]["temperatureTopic"]| "");
        _config->FloorControl.TapTopic = String(doc["floorControl"]["tapTopic"]| "");
        _config->FloorControl.MinTemperature = doc["floorControl"]["minTemperature"] | 20;
        _config->FloorControl.MaxTemperature = doc["floorControl"]["maxTemperature"] | 30;
        

        if(saveToFile){
            //TODO: file name should be initiated more properly
            saveConfig("/config.json");
            Serial.println(_fileManager->ReadFileRaw("/config.json"));
        }
    

        return true;
    }
};

#endif