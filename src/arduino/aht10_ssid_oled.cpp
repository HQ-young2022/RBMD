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
#include <Wire.h>
#include <Adafruit_AHTX0.h>

//#define SDA 0
//#define SCL 2

Adafruit_AHTX0 aht;

const int LED= 16;

void setup() {
  //Wire.begin(SDA,SCL);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  
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

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.display();
  delay(1000); // Pause for 2 seconds

  // Invert and restore display, pausing in-between
  display.invertDisplay(true);
  delay(500);
  display.invertDisplay(false);
  delay(500);

  display.clearDisplay();


  
}

void loop() {

  digitalWrite(LED, LOW);
 
  delay(100);       
 
  digitalWrite(LED, HIGH);

  
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
  Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.println(" *C");
  Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");
  Serial.println();

  float  f=temp.temperature;
  char   c[30];
  dtostrf(f,2,2,c);
  //Serial.println(c);

  float  g=humidity.relative_humidity;
  char   d[30];
  dtostrf(g,2,2,d);

  display.clearDisplay();

  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println(F("temperature"));
  display.setCursor(70,0);
  display.println(F("humidity"));
  
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,16);
  display.println(c);
  display.setCursor(68,16);
  display.println(d);
  display.display();      // Show initial text
  delay(100);
  
  
  char s[]=" *C / ";
  strcat(c,s);
  Serial.print(c);

  
  char t[]="% rH";
  strcat(d,t);
  Serial.println(d);
  
  Serial.println();

  

  char* ssid = strcat(c,d);
  const char* password = "password";

  WiFi.softAP(ssid,password);

 


  
 
  delay(6000);
}
