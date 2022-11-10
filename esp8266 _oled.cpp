#include <ESP8266WiFi.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int LED= 16;
const int key_L = 14;
const int key_R = 12;
const int key_C = 13;

int key_L_State = 0; 
int key_R_State = 0; 
int key_C_State = 0; 

int i =0;
int j =0;
int k =0;

void menu(){ 
  display.clearDisplay();
  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(3, 1);
  display.print(F("menu"));
  display.print(F("          "));
  display.print(i);
  display.print(j);
  display.println(k);
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
  
  
  
  }

 void stage(){
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(16, 16);
  display.println(F("stage"));
  
  
  }


 void modbus(){
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(16, 16);
  display.println(F("modbus"));
  
  }


void setup() {
  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();
  delay(2);
  Serial.begin(115200);

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED, OUTPUT);

  pinMode(key_L, INPUT);
  pinMode(key_R, INPUT);
  pinMode(key_C, INPUT);

  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(LED, HIGH);
    
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
  
  }





void testscrolltext(void) {
  display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(64, 16);
  display.println(F("scroll"));
  display.display();      // Show initial text
  delay(100);

  // Scroll in various directions, pausing in-between:
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(100);
  display.startscrollleft(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(100);
  display.startscrolldiagright(0x00, 0x07);
  delay(2000);
  display.startscrolldiagleft(0x00, 0x07);
  delay(2000);
  display.stopscroll();
  delay(100);
}

void loop(){
  
 //digitalWrite(LED, LOW);
 //digitalWrite(LED_BUILTIN, LOW);
 //delay(200);       
 //digitalWrite(LED, LOW);
 //digitalWrite(LED_BUILTIN, HIGH);
 //delay(200);          
 //digitalWrite(LED, HIGH);            
  
  // read the state of the pushbutton value:
  key_L_State = digitalRead(key_L);
  key_R_State = digitalRead(key_R);
  key_C_State = digitalRead(key_C);
  delay(100);
  
 if (key_L_State == HIGH){
    i=i+1;
    menu();
    setting();
    display.display(); 
    }
  
 else if (key_R_State == HIGH){
    j=j+1;
    menu();
    stage();
    display.display(); 
    }
 
 else if (key_C_State == HIGH){
    k=k+1;
    menu();
    control();
    
    display.display(); 
    }

 else if (key_L_State == HIGH,key_R_State == HIGH){
    menu();
    modbus();
    
    display.display(); 
    ; 
    }
}
  
