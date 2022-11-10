#include "config.h"

//Input/Output Pin
const int i00pin = 1; //Connect to Push Button
const int i01pin = 2; //Connect to Push Button
const int i02pin = 3; //Connect to Push Button

const int o00pin =  13; //Connect to Relay
const int o01pin =  14; //Connect to Relay


//Variable Name for Input/Output

boolean i1001;
boolean i1002;
boolean i1003;
boolean i1004;
boolean i1005;
boolean i1006;
boolean i1007;
boolean i1008;
boolean i1009;
boolean i1010;
boolean i1011;
boolean i1012;
boolean i1013;
boolean i1014;
boolean i1015;
boolean i1016;
boolean i1017;
boolean i1018;
boolean i1019;

boolean i4001;
boolean i4002;
boolean i4003;
boolean i4004;
boolean i4005;

//for input
boolean i00;
boolean i01;
boolean i02;
boolean i03;

//for out
boolean o00;
boolean o01;

//for time
int     i3001;
int     i3002;
int     i3003;
int     i3004;
int     i3005;
int     i3006;
int     i3007;
int     i3008;
int     i3009;
int     i3010;



void setup() {
  // put your setup code here, to run once:
//Input Pin Setup
  pinMode(i00pin, INPUT); 
  pinMode(i01pin, INPUT);
  pinMode(i02pin, INPUT);

//set
i1001=i00;
i1002=i01;

  //Output Pin Setup
  pinMode(o00pin, OUTPUT);  
  pinMode(o01pin, OUTPUT);
  
   
}

void loop() {
  // put your main code here, to run repeatedly:
//1.Input processing
  i00 = digitalRead(i00pin);
  i01 = digitalRead(i01pin);
  i02 = digitalRead(i02pin);
  o00 = digitalRead(o00pin);
  o01 = digitalRead(o01pin);

  
  //2.Program execution
  //logic or
  if (i1001 || i1002 || i1003 || i1004) {       
    delay(i3001);
    i4001 = true;  
  }else {
    i4001 = false; 
  }  
  
  //logic and
  if (i1005 && i1006 && i1007 && i1008) {       
    delay(i3002);
    i4002 = true;  
  }else {
    i4002 = false; 
  }
  
  //logic nor
  if ((!i1009) || (!i1010) || (!i1011) || (!i1012)) {       
    delay(i3003);
    i4003 = true;  
  }else {
    i4003 = false; 
  }  
  
  //logic nand
  if ((!i1013) && (!i1014) && (!i1015) && (!i1016)) {       
    delay(i3004);
    i4004 = true;  
  }else {
    i4004 = false; 
  }
  
  
  //3.Output processing
  digitalWrite(o00pin, i4003); 
  digitalWrite(o01pin, i4005);
}
