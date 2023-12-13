#include "DHT.h"

struct TempAndHummidity{
    float Temperature;
    bool isFahrenheit;
    float Hummidity;
    float HeatIndex;
};

class TempHummiditySensorReader {
    private:
        DHT* _dht = NULL;

    public:
        TempHummiditySensorReader(int dhtPin, int dhtType){
            _dht = new DHT(dhtPin, dhtType);
        }

        ~TempHummiditySensorReader() {
            if (_dht!= NULL)
                delete _dht;
        }

        void initSensors() {
             _dht->begin();
        }

        float readTemperature(bool isFahrenheit = false) {
            return _dht->readTemperature(isFahrenheit);
        }

        float readHummidity(){
            return _dht->readHumidity();
        }

        TempAndHummidity readTemperatureAndHummidity(bool isFahrenheit = false){
            //TODO: add implementation
            return TempAndHummidity();
        }
};