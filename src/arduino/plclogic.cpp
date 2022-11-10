//Input/Output Pin
const int i00pin = 1; //Connect to Push Button
const int i01pin = 2; //Connect to Push Button
const int i02pin = 3; //Connect to Push Button
const int i03pin = 4; //Connect to Push Button
const int i04pin = 5; //Connect to Push Button
const int i05pin = 6; //Connect to Push Button
const int i06pin = 7; //Connect to Push Button
const int i07pin = 8; //Connect to Push Button
const int i08pin = 9; //Connect to Push Button
const int i09pin = 10; //Connect to Push Button
const int i10pin = 11; //Connect to Push Button
const int i11pin = 12; //Connect to Push Button
const int o00pin =  13; //Connect to Relay
const int o01pin =  14; //Connect to Relay
const int o02pin =  15; //Connect to Relay
const int o03pin =  16; //Connect to Relay
const int o04pin =  17; //Connect to Relay
const int o05pin =  18; //Connect to Relay
const int o06pin =  19; //Connect to Relay
const int o07pin =  20; //Connect to Relay

//Variable Name for Input/Output
boolean i00;
boolean i01;
boolean i02;
boolean i03;
boolean i04;
boolean i05;
boolean i06;
boolean i07;
boolean i08;
boolean i09;
boolean i10;
boolean i11;
boolean o00;
boolean o01;
boolean o02;
boolean o03;
boolean o04;
boolean o05;
boolean o06;
boolean o07;

void setup() {
  //Input Pin Setup
  pinMode(i00pin, INPUT); 
  pinMode(i01pin, INPUT);
  pinMode(i02pin, INPUT);
  pinMode(i03pin, INPUT); 
  pinMode(i04pin, INPUT);
  pinMode(i05pin, INPUT);
  pinMode(i06pin, INPUT); 
  pinMode(i07pin, INPUT);
  pinMode(i08pin, INPUT);
  pinMode(i09pin, INPUT); 
  pinMode(i10pin, INPUT);
  pinMode(i11pin, INPUT);


  //Output Pin Setup
  pinMode(o00pin, OUTPUT);  
  pinMode(o01pin, OUTPUT);
  pinMode(o02pin, OUTPUT);  
  pinMode(o03pin, OUTPUT);
  pinMode(o04pin, OUTPUT);  
  pinMode(o05pin, OUTPUT);
  pinMode(o06pin, OUTPUT);  
  pinMode(o07pin, OUTPUT);
   
}

void loop()
{
  //The duty cycle of PLC http://program-plc.blogspot.com/2010/02/scan-time-of-plc.html

  //1.Input processing
  i00 = digitalRead(i00pin);
  i01 = digitalRead(i01pin);
  i02 = digitalRead(i02pin);
  o00 = digitalRead(o00pin);
  o01 = digitalRead(o01pin);

  
  //2.Program execution
  //(I:0/0 OR O:0/0 ) AND NOT I:0/2
  if ((i00 || o00) && !i02) {       
    o00 = true;  
  }else {
    o00 = false; 
  }  
  
  //((O:0/0 AND I:0/1 ) OR O:0/1) AND NOT I:0/2
  if (((o00 && i01) || o01) && !i02) {       
    delay(100);
    o01 = true;  
  }else {
    o01 = false; 
  }
  
  
  //3.Output processing
  digitalWrite(o00pin, o00); 
  digitalWrite(o01pin, o01);
}



