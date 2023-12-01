#include "LittleFS.h"

void initLittleFS(bool formatOnFail = false) {
    if (!LittleFS.begin()) {
          Serial.println("An Error has occurred while mounting LittleFS");
        return;
    }
}

String readLittleFsFileContents(String filename) {
    String fullFilePath = "/"+ filename;
    File file = LittleFS.open(fullFilePath);
    if (!file){
        Serial.println("Failed to open file for reading: " + filename);
        return "no content as an  error";
    }

    String fileContents = file.readString();
    file.close();
    return fileContents;
}

 /* File file = LittleFS.open("/text.txt", "r");
  if(!file){
    Serial.println("Failed to open file for reading");
    return;
  }
  
  Serial.println("File Content:");
  while(file.available()){
    Serial.write(file.read());
  }
  file.close();
}*/