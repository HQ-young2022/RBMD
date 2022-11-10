#include <IRremote.h>
int RECV_PIN = 2;  //红外接收模块连接在2脚
IRrecv irrecv(RECV_PIN);
decode_results results;
void setup()
{
   Serial.begin(9600);
   irrecv.enableIRIn();
}
void loop()
{
   if (irrecv.decode(&results))
   {
     dump(&results);
     irrecv.resume();
   }
}
void dump(decode_results *results)
{
   int count = results->rawlen;
   Serial.print("Raw (");
   Serial.print(count,DEC);
   Serial.print("): ");
  for (int i = 0; i < count; i++)
   {
    //if ((i % 2)==1){
      Serial.print((int)results->rawbuf[i]*USECPERTICK,DEC);
    //}
    //else{
    //Serial.print(-(int)results->rawbuf[i]*USECPERTICK,DEC);
    //}
     Serial.print(",");
   }
   Serial.println("");
}
