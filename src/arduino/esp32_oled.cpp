#include <WiFi.h>
#include <Wire.h>
#include "SSD1306.h"

 
#define SDA 22
#define SCL 23
 
SSD1306 display(0x3c, SDA, SCL);

#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

//#ifndef LED_BUILTIN
//#define LED_BUILTIN 13
//#endif

// define two tasks for Blink & AnalogRead
void Task1( void *pvParameters );
void Task2( void *pvParameters );
void Task3( void *pvParameters );

 
void setup() {
 
  WiFi.mode(WIFI_OFF);//close wifi
  btStop();           //close bluetooth
  delay(10);

  display.init();
  display.clear();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 0, "Hello World");
  display.drawString(0, 32, "--esp32---");
  display.display();

   Serial.begin(115200);
   Serial2.begin(115200);

  
  
  xTaskCreatePinnedToCore(
    Task1
    ,  "Task1"   // A name just for humans
    ,  1024  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL 
    ,  1);//ARDUINO_RUNNING_CORE 1

  xTaskCreatePinnedToCore(
    Task2
    ,  "Task2"
    ,  1024  // Stack size
    ,  NULL
    ,  2  // Priority
    ,  NULL 
    ,  1 );//ARDUINO_RUNNING_CORE 0

    xTaskCreatePinnedToCore(
    Task3
    ,  "Task3"
    ,  1024  // Stack size
    ,  NULL
    ,  2// Priority
    ,  NULL 
    ,  1 );//ARDUINO_RUNNING_CORE 0
}
 
void loop() {}



void Task1(void *pvParameters)  // This is a task.
{
  (void) pvParameters;


 

  for (;;) // A Task shall never return or exit.
  {
    Serial.print("[");
    Serial.print(millis());
    Serial.print("] ");
    Serial.print("task1 running on core: ");
    Serial.println(xPortGetCoreID());
    vTaskDelay(pdMS_TO_TICKS(100)); 
  }
}

void Task2(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  



  for (;;)
  {
    Serial.print("[");
    Serial.print(millis());
    Serial.print("] ");
    Serial.print("task2 running on core: ");
    Serial.println(xPortGetCoreID());
    vTaskDelay(pdMS_TO_TICKS(100));  // one tick delay (15ms) in between reads for stability
  }
}

  void Task3(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  



  for (;;)
  {
    int P = (analogRead(35))/1024*1024;
    Serial.print("[");
    Serial.print(millis());
    Serial.print("] ");
    Serial.print("oled running on core: ");
    Serial.print(xPortGetCoreID());
    Serial.print("------");
    Serial.println(P);
    display.clear();
    display.drawString(0, 0, "------test------");
    display.drawString(0, 32,"adc is "+String (P));
    display.display();

    String rev;
    if(Serial2.available())
  {
    rev=Serial2.readString();
    Serial.println("This is ESP32 (serial0)");
    Serial.print("rev from serial2: ");
    Serial.println(rev);
    }

    vTaskDelay(pdMS_TO_TICKS(200));  // one tick delay (15ms) in between reads for stability
  }
}

