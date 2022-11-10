
#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <Adafruit_AHTX0.h>

long previousTime =0;
long interval =6000;

const int buttonPin_1 = 14;
const int buttonPin_2 = 12;
const int buttonPin_3 = 13;

const int LED_1 = 2;
const int LED_2 = 16;

int i =0;

int buttonState1 = 0; 
int buttonState2 = 0; 
int buttonState3 = 0; 

//#define SDA 0
//#define SCL 2

Adafruit_AHTX0 aht;

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif



//U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 21, /* data=*/ 20, /* reset=*/ U8X8_PIN_NONE);   // Adafruit Feather M0 Basic Proto + FeatherWing OLED
U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // Adafruit Feather ESP8266/32u4 Boards + FeatherWing OLED
//U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);  // Adafruit ESP8266/32u4/ARM Boards + FeatherWing OLED
//U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL, /* data=*/ SDA);   // pin remapping with ESP8266 HW I2C
//U8G2_SSD1306_128X32_WINSTAR_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL, /* data=*/ SDA);   // pin remapping with ESP8266 HW I2C


// wqy fonts are available in different sizes, wqy12-16


//#define FONT u8g2_font_wqy14_t_chinese1
#define FONT u8g2_font_wqy14_t_gb2312b



void setup(void) {

 //Wire.begin(SDA,SCL);
  pinMode(LED_1, OUTPUT);
  digitalWrite(LED_1, HIGH);
  pinMode(LED_2, OUTPUT);
  digitalWrite(LED_2, HIGH);

  pinMode(buttonPin_1, INPUT);
  pinMode(buttonPin_2, INPUT);
  pinMode(buttonPin_3, INPUT);
  
  //WiFi.mode(WIFI_OFF);
  //WiFi.forceSleepBegin();
  delay(10);
  
  Serial.begin(115200);
  while ( !Serial ) delay(100);   // wait for native usb
  Serial.println("Adafruit AHT10/AHT20 demo!");

  if (! aht.begin()) {
    Serial.println("Could not find AHT? Check wiring");
    while (1) delay(10);
  }
  Serial.println("AHT10 or AHT20 found");

  

 
 u8g2.begin();  
  

  /* select a font */
  
  u8g2.enableUTF8Print();
  u8g2.setFont(FONT);
  
  
}



void loop(void) {

  buttonState1 = digitalRead(buttonPin_1);
  buttonState2 = digitalRead(buttonPin_2);
  buttonState3 = digitalRead(buttonPin_3);

  if (buttonState1 == HIGH) {
    // turn LED on:
    digitalWrite(LED_1, LOW);
  } else {
    // turn LED off:
    digitalWrite(LED_1, HIGH);
  }

  if (buttonState2 == HIGH) {
    // turn LED on:
    digitalWrite(LED_2, LOW);
  } else {
    // turn LED off:
    digitalWrite(LED_2, HIGH);
  }

  if (buttonState1 & buttonState2 == HIGH) {
    i=0;}
  if (buttonState3 == HIGH) {
    i=i+1;
  } 
  
  
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
  Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.println(" *C");
  Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");
  Serial.println();

  float  f=temp.temperature;
  char   c[30];
  dtostrf(f,2,2,c);

  float  g=humidity.relative_humidity;
  char   d[30];
  dtostrf(g,2,2,d);
  
  
  
  
  
  u8g2.setFontDirection(0);
  u8g2.firstPage();
  do {
    u8g2.setCursor(0, 15);
    u8g2.print("温度: ");
    u8g2.print(c);
    u8g2.print("  °C");
    u8g2.setCursor(0, 30);
    u8g2.print("湿度: "); 
    u8g2.print(d); 
    u8g2.print(" %rh");
    u8g2.print(" ");
    u8g2.print(i); 

    
  } while ( u8g2.nextPage() );
  delay(100);   
  
  char s[]=" °C / ";
  strcat(c,s);
  Serial.print(c);

  char t[]=" %rh";
  strcat(d,t);
  Serial.println(d);
  
  Serial.println();

  char* ssid = strcat(c,d);
  const char* password = "password";

  unsigned long currentTime=millis();
  if(currentTime-previousTime > interval){
    previousTime=currentTime;
    WiFi.softAP(ssid,password);
    Serial.println(ssid);
  }
  
 
    
  
  
}
