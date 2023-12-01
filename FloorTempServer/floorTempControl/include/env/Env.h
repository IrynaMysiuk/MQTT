#ifndef _ENV_H_

#define _ENV_H_
/*
    Primary contrainer for state of the application
*/
#include "ConfigManager.h"
#include "Logger.h"
#include "../utils/filesystem/FileManager.h"
#include "FS.h"

class Env {
    private:
        static Env* _instance;
        ConfigManager* _configManager = nullptr;
        Logger* _logger = nullptr;
        FileManager* _fileManager = nullptr;
       
    //properties
    public:
        static Env* Instance();
        ConfigManager* GetConfigManager() {
            if (_configManager == nullptr) {
                _logger->LogError("Config manager is not initialized before accessing it");
            }
            return _configManager;
        }
        Logger* GetLogger() {
            return _logger;
        }
         

    protected:
        Env(){
            _logger = new Logger();
        }
        ~Env() {
            /*if (_instance!=nullptr){
                delete Env::_instance;
                _instance = NULL;
            }*/
        }

    public:
        void initFileManager(FileManager* fileManager) {
            _fileManager = fileManager;
        }

        void initConfig(const char* configPath, const char* defaultConfigPath) {
            Serial.println("Im here 2");
            if (_configManager == nullptr) {
               _logger->LogInfoLn("starting init config manager");
                _configManager = new ConfigManager(_fileManager, _logger);
                _logger->LogInfoLn("start reading config");
                if(!_configManager->initConfig(configPath)){
                    _logger->LogInfoLn("config doesn't exists. Init by default");
                    bool b= _configManager->initConfig(defaultConfigPath);
                    _logger->LogInfoLn("saving config from default one");
                    _configManager->saveConfig(configPath);
                }
                _logger->LogInfoLn("configuration load completed");
            } else{
                _logger->LogInfoLn("config manager is initiated");
            }
        }
};

Env* Env::_instance = nullptr;

Env* Env::Instance(){
            if (Env::_instance ==nullptr){
                Env::_instance = new Env();
            }
            return Env::_instance;
        }

#endif