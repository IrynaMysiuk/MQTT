#ifndef _FILE_MANAGER_H_

#define _FILE_MANAGER_H_

#include <Arduino.h>
#include "FS.h"
#include "../../env/Logger.h"

class FileManager
{
protected: 
    Logger* _logger;
    fs::FS* _fs = nullptr;

    FileManager(Logger* logger) {
        this->_logger = logger;
    }

public:
    virtual bool InitFileSystem(bool formatOnFail = false);

    virtual void WriteFileRaw(const char *filepath, String &contents)
    {
        if(!isFileSystemReady()){
            return;
        }

        File file = _fs->open(filepath, FILE_WRITE);
        if (!file)
        {
            _logger->LogErrorLn(("Failed to open file for writing: "+ String(filepath)).c_str());
            return;
        }
        if (!file.print(contents))
        {
            _logger->LogErrorLn(("Failed to write file contents: "+ String(filepath)).c_str());
        }
        file.close();
    }

    virtual String ReadFileRaw(const char *filepath)
    {
        if (!isFileSystemReady()){
            return "";
        }

        File file = _fs->open(filepath);
        if (!file)
        {
            String errorMessage = "Failed to open file for reading: ";
            errorMessage += filepath;
            _logger->LogErrorLn(errorMessage.c_str());
            return "";
        }
        String fileContents = file.readString();
        file.close();
        return fileContents;
    }
/*
    virtual bool RemoveFile(const char* filepath ) {
        if(!isFileSystemReady()) {
            return false;
        }
        return _fs->remove(filepath);
    }*/

private:
    bool isFileSystemReady() {
        if (_fs == nullptr){
            _logger->LogWarningLn("Filesystem is not initiated");
            return false;
        }
        return true;
    }
};

#endif