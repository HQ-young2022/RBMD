#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_IL3820_V2_296X128_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 18, /* data=*/ 20, /* cs=*/ 17, /* dc=*/ 6, /* reset=*/ 3);  // L432 ePaper Display, lesser flickering and faster speed, enable 16 bit mode for this display!

void setup(void) {
  Serial.begin(115200);
  u8g2.begin();
  u8g2.enableUTF8Print();    // enable UTF8 support for the Arduino print() function
  u8g2.setFont(u8g2_font_wqy16_t_chinese3);  // use chinese3 for all the glyphs of "你好世界"
  u8g2.setFontDirection(0);
}

void loop(void) {
  u8g2.clearBuffer();                                        // clear the internal memory
  u8g2.setCursor(0, 15);
  Serial.println("test...");
  u8g2.print("Hello World!");
  u8g2.setCursor(0, 40);
  u8g2.print("世界你好");    // Chinese "Hello World" 
  u8g2.sendBuffer();      
  delay(3000);  
}
