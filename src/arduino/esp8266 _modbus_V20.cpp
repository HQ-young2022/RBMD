#include <ESP8266WiFi.h>
#include <ModbusMaster.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

SoftwareSerial mySerial(2, 0);



uint16_t temp1;
uint16_t temp2;
uint16_t temp3;
uint16_t temp4;
uint16_t temp5;
uint16_t temp6;
uint16_t temp7;
uint16_t temp8;
uint16_t temp9;
uint16_t temp;

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
    
	 
  node.readHoldingRegisters(99, 1);
  delay (5);
  Serial.println( node.getResponseBuffer(temp1), HEX );
  
  node.readHoldingRegisters(321, 1);
  delay (5);
  Serial.println( node.getResponseBuffer(temp2)/100, DEC );
  
  node.readHoldingRegisters(322, 1);
  delay (5);
  Serial.println( node.getResponseBuffer(temp3)/100, DEC );
  
  node.readHoldingRegisters(200, 1);
  delay (5);
  Serial.println( node.getResponseBuffer(temp4), HEX );
  
  node.readHoldingRegisters(259, 1);
  delay (5);
  Serial.println( node.getResponseBuffer(temp5)/100, DEC );
  
  node.readHoldingRegisters(260, 1);
  delay (5);
  Serial.println( node.getResponseBuffer(temp6)/100, DEC );
  
  node.readHoldingRegisters(219, 1);
  delay (5);
  Serial.println( node.getResponseBuffer(temp7)/100, DEC );

  temp = node.readHoldingRegisters(99, 1);
  
  if (temp == node.ku8MBSuccess) {//??????????????????
    
    Serial.print("DATA:");
    //for (uint8_t d = 0; d < m_length; d++)
    {
      menu(); 
      display.print(F("   "));
      display.println(node.getResponseBuffer(temp1), HEX);
      
      display.display(); 
  
    }
  }
  else {
    Serial.print("[");
    Serial.print(millis());
    Serial.print("] ");
    Serial.print("ERROR:");
    Serial.println(temp, HEX );//???HEX???16??????????????????????????????E2?????????TX,RX?????????E0?????????485???ttl??????????????????
    
    menu(); 
    display.print(F("   "));
    display.println( temp, HEX );
      
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

