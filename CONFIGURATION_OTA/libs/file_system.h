void FFat_file_system_init(){
  #ifdef CFG_DEBUG
  Serial.print(F("Инициализируем файловую система FAT..."));
  #endif
  if (FFat.begin(true)){
      Serial.println(F("Успешно"));
  }else{
      Serial.println(F("Ошибка"));
      while (true) { delay(1000); };
  }
}    

void read_wifi_cfg() {
  File configFile = FFat.open(wifi_cfg_path, "r");
  // Allocate a temporary JsonDocument
  // Don't forget to change the capacity to match your requirements.
  // Use arduinojson.org/v6/assistant to compute the capacity.
  StaticJsonDocument<512> doc;
  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, configFile);
  if (error){
    #ifdef CFG_DEBUG
    Serial.println(F("Failed to read file, using default configuration"));
    #endif
    wifi_cfg.ap = true;    
  }else{
  // Copy values from the JsonDocument to the Config
    wifi_cfg.ssid = doc["ssid"].as<String>();
    wifi_cfg.pwd = doc["pwd"].as<String>();
    wifi_cfg.ap = doc["ap"];

    #ifdef CFG_DEBUG
    Serial.println("Считываем конфигурацию вайфай: ");
    Serial.print("SSID:");
    Serial.println(wifi_cfg.ssid);
    Serial.print("Pasword:");
    Serial.println(wifi_cfg.pwd);
    Serial.print("ap Флаг: ");
    Serial.println(wifi_cfg.ap);
    #endif
  }
  configFile.close();
}

void read_ui_cfg() {
  File configFile = FFat.open(ui_cfg_path, "r");
  StaticJsonDocument<512> doc;
  DeserializationError error = deserializeJson(doc, configFile);
  if (error){
    #ifdef CFG_DEBUG
      Serial.println(F("Failed to read file, using default configuration"));
    #endif
    ui_cfg.web = true;    
  }else{

    ui_cfg.button = doc["button"];
    ui_cfg.web = doc["web"];
    ui_cfg.mqtt = doc["mqtt"];
    ui_cfg.screen = doc["screen"];
    ui_cfg.ap = doc["ap"];

    #ifdef CFG_DEBUG
    Serial.println("Считываем конфигурацию вайфай: ");
    Serial.print("ui_cfg.button:");
    Serial.println(ui_cfg.button);
    Serial.print("ui_cfg.web:");
    Serial.println(ui_cfg.web);
    Serial.print("ui_cfg.mqtt: ");
    Serial.println(ui_cfg.mqtt);
    Serial.print("ui_cfg.screen: ");
    Serial.println(ui_cfg.screen);
    Serial.print("ui_cfg.ap: ");
    Serial.println(ui_cfg.ap);        
    #endif
  }
  configFile.close();

}




boolean save_wifi_config(String ssid, String pwd) {
  File configFile = FFat.open(wifi_cfg_path, "w");
  if (!configFile) {
  //Serial.println(“Failed to open config file for writing”);
  return false;
  }
  StaticJsonDocument<256> doc;
  // Set the values in the document

  
  doc["ssid"] = ssid;
  doc["pwd"] = pwd;
  doc["ap"] = "false";
  
  // Serialize JSON to file
  if (serializeJson(doc, configFile) == 0) {
    Serial.println(F("Failed to write to file"));
  }  

  configFile.close();
  return true;
  
}

/*
void read_wifi_config(Config &config) {
  Serial.println("Чтение конфигурации:");
  File configFile = FFat.open("/src/assets/wifi_cfg.json", "r");

  // Allocate a temporary JsonDocument
  // Don't forget to change the capacity to match your requirements.
  // Use arduinojson.org/v6/assistant to compute the capacity.
  StaticJsonDocument<512> doc;

  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, configFile);
  if (error){
    Serial.println(F("Failed to read file, using default configuration"));
   // config.ssid = "WIFI";
   // config.pwd = "kra12va12";
   // config.ap = false;    
  }else{
  // Copy values from the JsonDocument to the Config
    config.ssid = doc["ssid"].as<String>();
    config.pwd = doc["pwd"].as<String>();
    config.ap = doc["ap"];

    Serial.println("Считываем конфигурацию вайфай: ");
    Serial.print("SSID:");
    Serial.println(config.ssid);
    Serial.print("Pasword:");
    Serial.println(config.pwd);
    Serial.print("ap Флаг: ");
    Serial.println(config.ap);
  }
  // Close the file (Curiously, File's destructor doesn't close the file)
  configFile.close();

}
*/