#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  } 

  // Clear the buffer 这里如果不清理buffer，默认的显示内容为Adafruit类库的LOGO
  display.clearDisplay();

  ShowText();
}

void loop() {
  // put your main code here, to run repeatedly:

} 

void ShowText(void) {
  display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text 2倍字体
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 10); //显示的坐标位置
  display.println(F("Happy day"));
  display.display();      // Show text
}
