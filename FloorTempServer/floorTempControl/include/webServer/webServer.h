#ifndef _WEB_SERVER_H_

#define _WEB_SERVER_H_

#include "AsyncTCP.h"
#include "ESPAsyncWebServer.h"
#include "WiFi.h"
#include "LittleFS.h"

#include "env/Env.h"

class WebServer
{
    AsyncWebServer *_server;
    Logger *_logger;
    // AsyncWebSocket ws("/ws"); // access at ws://[esp ip]/ws
    // AsyncEventSource events("/events"); // event source (Server-Sent events)

public:
    WebServer(Logger *logger, int port = 80) : _logger(logger)
    {
        _server = new AsyncWebServer(port);
    }

    void initWebServer()
    {
        // attach AsyncWebSocket
        // ws.onEvent(onEvent);
        // server->addHandler(&(this->ws));

        // attach AsyncEventSource
        // server->addHandler(&(this->events));

        // Process Vuejs app files
        _server->on("/", HTTP_ANY, [](AsyncWebServerRequest *request)
                    { 
                    Serial.println("resolving index.html");
                    request->send(LittleFS, "/index.html"); });

        _server->on("^(\\/assets\\/.+)$", HTTP_GET, [](AsyncWebServerRequest *request)
                    { 
                    Serial.printf("looking assets %s",request->pathArg(0));
                    Serial.println(request->url());
                    request->send(LittleFS,request->pathArg(0)); });


        _server->on("/api/reboot", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
            Serial.println("reboot executed");
            request->send(200, "text/html","ok!");
            ESP.restart(); });

        _server->on("/api/config", HTTP_GET, WebServer::onGetConfig);
    
        addPostConfig();

        // attach filesystem root at URL /fs
        _server->serveStatic("/fs", LittleFS, "/");

        // Process not found(404)
        _server->onNotFound([](AsyncWebServerRequest *request)
                            {
                            
            Serial.printf("page not found ", request->url());
            request->send(404); });
        // _server->onFileUpload(onUpload);
        // _server->onRequestBody(onBody);

        _server->begin();
    }

    void addPostConfig();

public:
    // static request handlers
    static void onGetConfig(AsyncWebServerRequest *request);

};

void WebServer::addPostConfig()
{
    _server->on(
        "/api/config/save", HTTP_POST,
        [](AsyncWebServerRequest *request) {},
        [](AsyncWebServerRequest *request, const String &filename, size_t index, uint8_t *data, size_t len, bool final) {},
        [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
        {
            Serial.printf("len: %d %d; data: %s", len, total, data);
            String str;
            str.reserve(len+1); // prepare space for the buffer and extra termination character '\0'
            for (int i = 0; i<len; ++i) {
                str += (char)data[i]; // typecast because String takes uint8_t as something else than char
            }
            Serial.printf("incoming save config: %s", str);
            Env::Instance()->GetConfigManager()->loadConfigFromJsonString(str, true);
            request->send(200);
        });
}

void WebServer::onGetConfig(AsyncWebServerRequest *request)
{
    request->send(200, "application/json",
                  Env::Instance()->GetConfigManager()->configAsJsonString());
}

#endif