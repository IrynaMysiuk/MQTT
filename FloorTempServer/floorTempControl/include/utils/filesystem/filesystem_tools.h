#include "SPIFFS.h"

bool initFileSystem(bool formatOnFail=false) {
    if (!SPIFFS.begin(formatOnFail)) {
        Serial.println("An Error has occured while mounting SPIFFS");
        return false;
    }
    else {
        Serial.println("Successfully mounted");
    }

    return true;
}

String readFileContents(String filename) {
    String fullFilePath = "/"+ filename;
    File file = SPIFFS.open(fullFilePath);
    if (!file){
        Serial.println("Failed to open file for reading: " + filename);
        return "no content as an  error";
    }

    String fileContents = file.readString();
    file.close();
    return fileContents;
}
 /*
void setup() {
  Serial.begin(9600);
  
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  
  File file = SPIFFS.open("/text.txt");
  if(!file){
    Serial.println("Failed to open file for reading");
    return;
  }
  
  Serial.println("File Content:");
  while(file.available()){
    Serial.write(file.read());
  }
  file.close();
}

*/