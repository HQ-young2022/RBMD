#include <WiFi.h>
#include <ModbusMaster.h>

uint16_t m_startAddress = 12;//要读取的从站起始地址
uint8_t m_length = 1;//从从站起始地址开始你需要读取的数据的长度
uint8_t result;//串口通信结果，不用明白是什么，只要知道这不是你最终需要的数据就行

// instantiate ModbusMaster object
ModbusMaster node;


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

	// communicate with Modbus slave ID 2 over Serial (port 0)
  node.begin(2, Serial2);

   

   Serial.println( " STARTING TEST FREERTOS ");

  
  
  xTaskCreatePinnedToCore(
    Task1
    ,  "Task1"   // A name just for humans
    ,  1024  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL 
    ,  1);//ARDUINO_RUNNING_CORE 1

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
    
    
    vTaskDelay(pdMS_TO_TICKS(20));
    
	  
	  
	result = node.readHoldingRegisters(m_startAddress, m_length);//调用相关函数
  if (result == node.ku8MBSuccess) {//如果通信成功
    
    Serial.print("DATA:");
    for (uint8_t j = 0; j < m_length; j++)
    {
      Serial.print( node.getResponseBuffer(j), DEC );//以DEC（十）进制显示你要的数据
    }
  }
  else {
    Serial.print("[");
    Serial.print(millis());
    Serial.print("] ");
    Serial.print( "task1 running  --  ");
    Serial.print("ERROR:");
    Serial.println(result, HEX);//以HEX（16）进制显示错误信息（E2：你的TX,RX断线，E0：你的485转ttl板子有问题）
  }

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

