#include <WiFi.h>


#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif



// define two tasks for Blink & AnalogRead
void Task1( void *pvParameters );
void Task2( void *pvParameters );
void Task3( void *pvParameters );


//unsigned long startProducing, endProducing, startConsuming, endConsuming, producingTime, consumingTime;

 
void setup() {
 
  WiFi.mode(WIFI_OFF);//close wifi
  btStop();           //close bluetooth
  delay(10);


   Serial.begin(115200);
   Serial2.begin(115200);


   

   Serial.println( " STARTING TEST FREERTOS ");

  
  
  xTaskCreatePinnedToCore(
    Task1
    ,  "Task1"   // A name just for humans
    ,  1024  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL 
    ,  0);//ARDUINO_RUNNING_CORE 1

  xTaskCreatePinnedToCore(
    Task2
    ,  "Task2"
    ,  1024  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL 
    ,  1 );//ARDUINO_RUNNING_CORE 0

    xTaskCreatePinnedToCore(
    Task3
    ,  "Task3"
    ,  1024  // Stack size
    ,  NULL
    ,  1// Priority
    ,  NULL 
    ,  1 );//ARDUINO_RUNNING_CORE 0
}
 
void loop() {}



void Task1(void *pvParameters)  // This is a task.
{
  (void) pvParameters;


 

  for (;;) // A Task shall never return or exit.
  {
    
    
    vTaskDelay(pdMS_TO_TICKS(200));
    Serial.print("[");
    Serial.print(millis());
    Serial.print("] ");
    Serial.println( "task1 running");
     
  }
}

void Task2(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  



  for (;;)
  {
    
    
    vTaskDelay(pdMS_TO_TICKS(200));
    Serial.print("[");
    Serial.print(millis());
    Serial.print("] ");
    Serial.println( "task2 running");
  }
}

  void Task3(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  



  for (;;)
  {
    
    vTaskDelay(pdMS_TO_TICKS(200));
    Serial.print("[");
    Serial.print(millis());
    Serial.print("] ");
    Serial.println( "task3 running");
  }
}

