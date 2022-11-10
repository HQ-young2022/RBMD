#include <ESP8266WiFi.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_AHTX0.h>

Adafruit_AHTX0 aht;

const int LED= 16;

Adafruit_BMP280 bmp; // use I2C interface
Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();
Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();

void setup() {

  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  
  //WiFi.mode(WIFI_OFF);
  //WiFi.forceSleepBegin();
  delay(10);
  
  Serial.begin(115200);
  while ( !Serial ) delay(100);   // wait for native usb
  Serial.println(F("BMP280 Sensor event test"));

  Serial.println("Adafruit AHT10/AHT20 demo!");

  if (! aht.begin()) {
    Serial.println("Could not find AHT? Check wiring");
    while (1) delay(10);
  }
  Serial.println("AHT10 or AHT20 found");

  unsigned status;
  //status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  status = bmp.begin();
  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    Serial.print("SensorID was: 0x"); Serial.println(bmp.sensorID(),16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

  bmp_temp->printSensorDetails();
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

/*
Arduino中数据类型转换 float/double转换为char 亲测好使,dtostrf()函数
       
格式如下：

char* dtostrf(double _val,signed char _width, unsigned char prec, char* _s)

参数说明：

_val:要转换的float或者double值。

_转换后整数部分长度。

_prec：转换后小数部分长度。

_s:保存到该char数组中。



示例如下：
float  f=3.1415;
char   c[];
dtostrf(f,1,2,c);
Serial.println(c);
此时从Arduino自带串口监视器中将输出3.14，即成功实现了数据类型转换。
数据转换之后，我们可以对字符串进行一个拼接。如下，将实现字符串的拼接


float  f=3.1415;
char   c[];
dtostrf(f,1,2,c);
Serial.println(c);
//定义一个字符串
char s[]="///sensor1///ly///sensor1///PM2.5///100.70///";
//进行字符串拼接操作
strcat(s,c);
Serial.println(s);
此时将在Arduino自带串口监视器中将输出///sensor1///ly///sensor1///PM2.5///100.70///3.14，即成功实现了字符串的拼接。
特别说明：Arduino中可以直接调用C语言中的strcat()函数来实现对字符串的拼接。
 */

  float  f=temp.temperature;
  char   c[30];
  dtostrf(f,2,1,c);
  //Serial.println(c);

  //定义一个字符串
  char s[]=" *C / ";
  //进行字符串拼接操作
  strcat(c,s);
  Serial.print(c);

  float  g=humidity.relative_humidity;
  char   d[30];
  dtostrf(g,2,1,d);
  //Serial.println(d);

  //定义一个字符串
  char t[]="% rH";
  //进行字符串拼接操作
  strcat(d,t);
  Serial.println(d);

  char* ssid = strcat(c,d);
  const char* password = "password";

  WiFi.softAP(ssid,password);
 
  
  sensors_event_t temp_event, pressure_event;
  bmp_temp->getEvent(&temp_event);
  bmp_pressure->getEvent(&pressure_event);
  
  Serial.print(F("Temperature = "));
  Serial.print(temp_event.temperature);
  Serial.println(" *C");

  Serial.print(F("Pressure = "));
  Serial.print(pressure_event.pressure);
  Serial.println(" hPa");

  Serial.println();
  delay(10000);
}
