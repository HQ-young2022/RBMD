
#include <PinButton.h>


PinButton F1_Button(14);
PinButton F2_Button(12);
PinButton F3_Button(13);

int LED_1 = 2;
int LED_2 = 16;

void setup() {
 
  Serial.begin(115200);

  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  
            
}

void loop() {
  
  F1_Button.update();
  F2_Button.update();
  F3_Button.update();

  
  if (F1_Button.isClick()) {
    Serial.println("F1 click");
  }
  if (F1_Button.isSingleClick()) {
    Serial.println("F1 single");
    digitalWrite(LED_1, HIGH);
  }
  if (F1_Button.isDoubleClick()) {
    Serial.println("F1 double");
    digitalWrite(LED_1, LOW);
  }
  if (F1_Button.isLongClick()) {
    Serial.println("F1 long");
  }
  if (F1_Button.isReleased()) {
    Serial.println("F1 up");
  }


   if (F2_Button.isClick()) {
    Serial.println("F2 click");
  }
  if (F2_Button.isSingleClick()) {
    Serial.println("F2 single");
    digitalWrite(LED_2, HIGH);
  }
  if (F2_Button.isDoubleClick()) {
    Serial.println("F2 double");
    digitalWrite(LED_2, LOW);
  }
  if (F2_Button.isLongClick()) {
    Serial.println("F2 long");
  }
  if (F2_Button.isReleased()) {
    Serial.println("F2 up");
  }


   if (F3_Button.isClick()) {
    Serial.println("F3 click");
  }
  if (F3_Button.isSingleClick()) {
    Serial.println("F3 single");
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
  }
  if (F3_Button.isDoubleClick()) {
    Serial.println("F3 double");
  }
  if (F3_Button.isLongClick()) {
    Serial.println("F3 long");
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, HIGH);      
  }
  if (F3_Button.isReleased()) {
    Serial.println("F3 up");
  }
}
