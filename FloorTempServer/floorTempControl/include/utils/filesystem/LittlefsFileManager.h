#ifndef _LITTLEFS_FILE_MANAGER_H_

#define _LITTLEFS_FILE_MANAGER_H_

#include <Arduino.h>
#include "LittleFS.h"
#include "FS.h"

#include "FileManager.h"
#include "../../env/Logger.h"


//TODO: probably, could be just one file manager for all file systems. 
//Need to research
class LittlefsFileManager : public FileManager
{
   
public:
    LittlefsFileManager(Logger* logger): FileManager(logger) {
        this->_logger = logger;
    }

    bool InitFileSystem(bool formatOnFail = false) override {
        if(!LittleFS.begin(formatOnFail)) {
            _logger->LogError("An Error occured while mounting LittleFS");
            return false;
        }
        _fs = &LittleFS;
        return true;
    }

};


#endif