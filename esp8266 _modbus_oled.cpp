#include <ESP8266WiFi.h>
#include <ModbusMaster.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

SoftwareSerial mySerial(2, 0);


uint16_t m_startAddress = 99;//要读取的从站起始地址
uint8_t m_length = 1;//从从站起始地址开始你需要读取的数据的长度
uint8_t result;//串口通信结果，不用明白是什么，只要知道这不是你最终需要的数据就行


// instantiate ModbusMaster object
ModbusMaster node;


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int key_L = 14;
const int key_R = 12;
const int key_C = 13;

int key_L_State = 0; 
int key_R_State = 0; 
int key_C_State = 0; 





void menu(){ 
  display.clearDisplay();
  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(3, 1);
  display.print(F("menu"));

  display.drawLine(1, 0, 27, 0, SSD1306_WHITE);
  display.drawLine(0, 1, 0, 9, SSD1306_WHITE);
  display.drawLine(28, 1, 28, 10, SSD1306_WHITE);
  display.drawLine(1, 10, 128, 10, SSD1306_WHITE);
  }
  
 void setting(){
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(16, 16);
  display.println(F("setting"));
  display.display();      // Show initial text
  
  
  }
  
 void control(){
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(16, 16);
  display.println(F("control"));
  display.display(); 
  
  
  }

 void stage(){
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(16, 16);
  display.println(F("stage"));
  display.display(); 
  
  }




 
void setup() {
 
  WiFi.mode(WIFI_OFF);//close wifi
  delay(10);


  pinMode(key_L, INPUT);
  pinMode(key_R, INPUT);
  pinMode(key_C, INPUT);


    
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.display();
  delay(1000); // Pause for 2 seconds

  
  display.clearDisplay();
  
  Serial.println("-----------wifi is sleep-----------");

  
  
 

  // Invert and restore display, pausing in-between
  display.invertDisplay(true);
  delay(500);
  display.invertDisplay(false);
  delay(500);

  display.clearDisplay();
 
  //testscrolltext();    // Draw scrolling text
  
	
   Serial.begin(115200,SERIAL_8N1);
   mySerial.begin(19200,SWSERIAL_8E1);

	// communicate with Modbus slave ID 2 over Serial (port 0)
  node.begin(6, mySerial);

   

   Serial.println( " STARTING TEST modbus ");

  
}
 
void loop() {
    
	 
	result = node.readHoldingRegisters(m_startAddress, m_length);//调用相关函数
  if (result == node.ku8MBSuccess) {//如果通信成功
    
    Serial.print("DATA:");
    for (uint8_t d = 0; d < m_length; d++)
    {
      Serial.println( node.getResponseBuffer(d), HEX );//以DEC（十）进制显示你要的数据
      
      menu(); 
      display.print(F("   "));
      display.println( node.getResponseBuffer(d), HEX );
      
      display.display(); 
  
    }
  }
  else {
    Serial.print("[");
    Serial.print(millis());
    Serial.print("] ");
    Serial.print("ERROR:");
    Serial.println(result, HEX);//以HEX（16）进制显示错误信息（E2：你的TX,RX断线，E0：你的485转ttl板子有问题）
    
    menu(); 
    display.print(F("   "));
    display.println( result, HEX );
      
    display.display(); 
  }
  
  	// read the state of the pushbutton value:
  key_L_State = digitalRead(key_L);
  key_R_State = digitalRead(key_R);
  key_C_State = digitalRead(key_C);
   
  
 if (key_L_State == HIGH){
    delay (5);
    node.writeSingleRegister(99, 1151);
    
    }
  
 else if (key_R_State == HIGH){
    delay (5);
    node.writeSingleRegister(99, 1278);
    delay (5);
    node.writeSingleRegister(200, 0);
    
    }
 
 else if (key_C_State == HIGH){
    delay (5);
    node.writeSingleRegister(200, 1);
    
    }


  delay(100);
  
  }

