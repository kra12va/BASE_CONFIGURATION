/*
Прототип конфигуратораz:\GitHub\BASE_CONFIGURATION\CONFIGURATION_OTA\libs\configurator.h z:\GitHub\BASE_CONFIGURATION\CONFIGURATION_OTA\libs\file_system.h z:\GitHub\BASE_CONFIGURATION\CONFIGURATION_OTA\libs\wifi_connection.h
ver 1.0 
Работает АП - ок
Файловая система - ок
FTP сервер - ок
ОТА загрузка любой прошивки - ок
ОТА загрузка файловой системы - проверить
подключение к вайфай в ручном режиме -

button      - кнопочное управление (не реализовано)
web         - веб управление реализовано на половину
mqtt        - не реализовано
screen      - экранное управление не реализовано
android     - приложение ANDROID не реализовано
iOS         - приложение iOS не реализовано


Базовай прошивка: первой подключение к вайфай,  базовая настройка ПУСТОЙ МК (от производителя), для дальнейшего
залития прошивки "Умного устройства"
*/

#define DEBUG  // Раскоментировать при отладке
#include "Arduino.h"
#include <WiFi.h>
#include <WiFiAP.h>
#include <ArduinoJson.h>
#include "FS.h"
#include "FFat.h"
#include <TimerMs.h>
// (период, мс), (0 не запущен / 1 запущен), (режим: 0 период / 1 таймер)
TimerMs listen_bnt_tmr(150, 1, 0);


#include <WebServer.h>
WebServer HTTP(80);

#include <SimpleFTPServer.h>
FtpServer ftpSrv;  //set #define FTP_DEBUG in ESP8266FtpServer.h to see ftp verbose on serial

#include <ElegantOTA.h>  // прошивка по воздуху
unsigned long ota_progress_millis = 0; // для обновления по воздуху

#include "libs/configurator.h"




void setup() {

  Serial.begin(115200);
  
  listen_bnt_tmr.start();

  configurator MK;
  MK.set_wifi_cfg_ssid("ssid");

  // Обработка HTTP-запросов
  HTTP_init();  
  FTP_server_init();
  ElegantOTA_init();
}

void loop() {
  HTTP.handleClient();
  ftpSrv.handleFTP();  //make sure in loop you call handleFTP()!!


}

