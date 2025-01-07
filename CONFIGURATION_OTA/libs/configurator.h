class configurator {
  
  #define PIN_WFIF_AP_BTN 13 // Пин кнопки для принудительной настроки МК
  #define CFG_DEBUG  // Раскоментировать при отладке
  #include "libs/file_system.h" // Работа с файловой системой FFat
  #include "libs/wifi_connection.h" // Работа с файловой системой FFat
  public:
    configurator() {
      #ifdef CFG_DEBUG
      Serial.println("Отработал конструктор конфигаратора.");
      #endif
      pinMode(PIN_WFIF_AP_BTN, INPUT_PULLUP);      
      FFat_file_system_init();    // Инициируем файловую систему
      read_wifi_cfg();            // Считывай конфигурацию подключения к WiFi
      read_ui_cfg();              // Считывай конфигурацию методов взаимодействия с пользователем

      if (!digitalRead(PIN_WFIF_AP_BTN)){
        Serial.println("Нажата кнопка принудительной настройки МК, создаю точку доступа ");
        wifi_AP_DEFAULT_run();
      }else{
        if(wifi_cfg.ap){
          wifi_AP_run();
        }else{
          wifi_run(); // Подключаюсь к Вайфай сети
        }  
      }

     
    }

    void set_wifi_cfg_ssid(String ssid){
      wifi_cfg.ssid = ssid;
      #ifdef DEBUG
      Serial.println("Установлен SSID вашего вайфай соединения" + wifi_cfg.ssid);  
      #endif      
    }

  private:
    
  // Пароль к течке доступа по умолчанию
    const char *ssid = "i-ESP32";
    const char *password = "11223344";

    // Конфигурация подключения WiFi МК
    String wifi_cfg_path = "/src/assets/base_cfg/wifi_cfg.json";
    struct Connection_wifi_cfg {
      String ssid;        // Срока, хранит значение SSID вайфай
      String pwd;         //строка, хранит значение пароля к вайфай
      boolean ap = true;  //true - режим точки доступа, false - режим подключения клиентом к вайфай
    };   
    Connection_wifi_cfg wifi_cfg;  // Конфигурация подключения WiFi МК

    // Конфигурация типов UI МК
    String ui_cfg_path = "/src/assets/base_cfg/ui_cfg.json";
    struct Connection_ui_cfg {
      boolean button;         // Взаимодействие через кнопки 
      boolean web;            // Взаимодействие через веб-сервер
      boolean mqtt;           // Взаимодействие через MQTT сервер
      boolean screen;         // Взаимодействие через экран
      boolean ap;             // Взаимодействие через приложение на телефоне Android, iOS
    };   
    Connection_ui_cfg ui_cfg;  // Конфигурация типов UI МК   

    
};