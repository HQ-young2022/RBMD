/*
  Modbus-Arduino Example - Test Holding Register (Modbus IP ESP8266)
  Configure Holding Register (offset 100) with initial value 0xABCD
  You can get or set this holding register
  Original library
  Copyright by André Sarmento Barbosa
  http://github.com/andresarmento/modbus-arduino

  Current version
  (c)2017 Alexander Emelianov (a.m.emelianov@gmail.com)
  https://github.com/emelianov/modbus-esp8266
*/

#ifdef ESP8266
 #include <ESP8266WiFi.h>
#else //ESP32
 #include <WiFi.h>
#endif
#include <ModbusIP_ESP8266.h>

// Modbus Registers Offsets
const int TEST0_HREG = 100;
const int TEST1_HREG = 101;
const int TEST2_HREG = 102;
const int TEST3_HREG = 103;
const int TEST4_HREG = 104;
const int TEST5_HREG = 105;
const int TEST6_HREG = 106;
const int TEST7_HREG = 107;


//ModbusIP object
ModbusIP mb;
  
void setup() {
  Serial.begin(115200);
 
  WiFi.begin("your_ssid", "your_password");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  mb.server();
  mb.addHreg(TEST0_HREG, 0xABC8);
  mb.addHreg(TEST1_HREG, 0xABC7);
  mb.addHreg(TEST2_HREG, 0xABC6);
  mb.addHreg(TEST3_HREG, 0xABC5);
  mb.addHreg(TEST4_HREG, 0xABC4);
  mb.addHreg(TEST5_HREG, 0xABC3);
  mb.addHreg(TEST6_HREG, 0xABC2);
  mb.addHreg(TEST7_HREG, 0xABC1);
}
 
void loop() {
   //Call once inside loop() - all magic here
   mb.task();
   delay(10);
}
