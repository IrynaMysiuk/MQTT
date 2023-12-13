#ifndef _LOGGER_H_

#define _LOGGER_H_

#include <Arduino.h>

#define LOG_ERROR_ONLY 1
#define LOG_ERROR_AND_WARNING 2
#define LOG_ERROR_AND_WARNING_AND_INFO 3
#define LOG_ALL 4

class Logger {
    private:
        int _logLevel;
    public:
        void ChangeLogLevel(int newLevel) {
            _logLevel = newLevel;
        }
        
        Logger(unsigned long baud=115200, int level=LOG_ALL) {
            Serial.begin(baud);
            this->_logLevel = level;
        }

        void LogTraceLn(const char* message) {
            if (_logLevel==LOG_ALL) {
                Serial.println(message);
            }
        }

        void LogTrace(const char* message) {
            if (_logLevel==LOG_ALL) {
                Serial.print(message);
            }
        }

        void LogInfoLn(const char* message) {
            if (_logLevel>=LOG_ERROR_AND_WARNING_AND_INFO) {
                Serial.println(message);
            }
        }

        void LogInfo(const char* message) {
            if (_logLevel>=LOG_ERROR_AND_WARNING_AND_INFO) {
                Serial.print(message);
            }
        }

        void LogWarningLn(const char* message) {
            if (_logLevel>=LOG_ERROR_AND_WARNING) {
                Serial.println(message);
            }
        }

        void LogWarningInfo(const char* message) {
            if (_logLevel>=LOG_ERROR_AND_WARNING) {
                Serial.print(message);
            }
        }


        void LogErrorLn(const char* message) {
            if (_logLevel>=LOG_ERROR_ONLY) {
                Serial.println(message);
            }
        }

        void LogError(const char* message) {
            if (_logLevel>=LOG_ERROR_ONLY) {
                Serial.print(message);
            }
        }

};


#endif