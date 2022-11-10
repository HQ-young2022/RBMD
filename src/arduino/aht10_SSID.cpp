#include <ESP8266WiFi.h>
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

  
  char s[]=" *C / ";
  strcat(c,s);
  Serial.print(c);

  float  g=humidity.relative_humidity;
  char   d[30];
  dtostrf(g,2,2,d);
  
  
  char t[]="% rH";
  strcat(d,t);
  Serial.println(d);
  
  Serial.println();

  char* ssid = strcat(c,d);
  const char* password = "password";

  WiFi.softAP(ssid,password);
 
  delay(6000);
}
