#include <WiFi.h>
#include <ModbusMaster.h>


//Input/Output Pin
const int i00pin = 25; //Connect to Push Button
const int i01pin = 26; //Connect to Push Button
const int i02pin = 27; //Connect to Push Button

const int o00pin =  32; //Connect to Relay
const int o01pin =  33; //Connect to Relay


//Variable Name for Input/Output
boolean i00;
boolean i01;
boolean i02;

boolean o00;
boolean o01;





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

//*************************************************************************************************


void plc_c_1() {
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

void plc_c_2() {
    Serial.print("[");
    Serial.print(millis());
    Serial.print("] ");
    Serial.println( "task2 running");
}

void plc_c_3() {
  //The duty cycle of PLC http://program-plc.blogspot.com/2010/02/scan-time-of-plc.html

  //1.Input processing
  i00 = digitalRead(i00pin);
  i01 = digitalRead(i01pin);
  i02 = digitalRead(i02pin);
  o00 = digitalRead(o00pin);
  o01 = digitalRead(o01pin);

  
  //2.Program execution
  //(I:0/0 OR O:0/0 ) AND NOT I:0/2
  if ((i00 || o00) && !i02) {       
    o00 = true;  
  }else {
    o00 = false; 
  }  
  
  //((O:0/0 AND I:0/1 ) OR O:0/1) AND NOT I:0/2
  if (((o00 && i01) || o01) && !i02) {       
    //delay(100);
    vTaskDelay(pdMS_TO_TICKS(20));
    o01 = true;  
  }else {
    o01 = false; 
  }
  
  
  //3.Output processing
  digitalWrite(o00pin, o00); 
  digitalWrite(o01pin, o01);
    Serial.print("[");
    Serial.print(millis());
    Serial.print("] ");
    Serial.println( "task3 running");
}


//************************************************************************************************************

void setup() {
 
  WiFi.mode(WIFI_OFF);//close wifi
  btStop();           //close bluetooth
  delay(10);


   Serial.begin(115200);
   Serial2.begin(115200);

	// communicate with Modbus slave ID 2 over Serial (port 0)
  node.begin(2, Serial2);

   

   Serial.println( " STARTING TEST FREERTOS ");



//Input Pin Setup
  pinMode(i00pin, INPUT); 
  pinMode(i01pin, INPUT);
  pinMode(i02pin, INPUT);
  


  //Output Pin Setup
  pinMode(o00pin, OUTPUT);  
  pinMode(o01pin, OUTPUT);
  




  
  
  xTaskCreatePinnedToCore(
    Task1
    ,  "Task1"   // A name just for humans
    ,  2048 // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
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
 

//-----------------------------------------------------------------------------//
//---------------------Do not try do anything under hear-----------------------//
//-----------------------------------------------------------------------------//

void loop() {}



void Task1(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  for (;;) // A Task shall never return or exit.
  {
    vTaskDelay(pdMS_TO_TICKS(20));
    plc_c_1();
	}
}
     
void Task2(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  for (;;)
  {
    vTaskDelay(pdMS_TO_TICKS(200));
    plc_c_2();
  }
}

  void Task3(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  for (;;)
  {
    vTaskDelay(pdMS_TO_TICKS(200));
    plc_c_3();
  }
}

