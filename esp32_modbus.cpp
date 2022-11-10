#include <ModbusMaster.h>

uint16_t m_startAddress = 12;//要读取的从站起始地址
uint8_t m_length = 1;//从从站起始地址开始你需要读取的数据的长度
uint8_t result;//串口通信结果，不用明白是什么，只要知道这不是你最终需要的数据就行

// instantiate ModbusMaster object
ModbusMaster node;


void setup()
{
  // use Serial (port 0); initialize Modbus communication baud rate
  Serial.begin(115200);
  Serial2.begin(115200);

  // communicate with Modbus slave ID 2 over Serial (port 0)
  node.begin(2, Serial2);
}


void loop()
{
  result = node.readHoldingRegisters(m_startAddress, m_length);//调用相关函数
  if (result == node.ku8MBSuccess) {//如果通信成功
    
    Serial.print("DATA:");
    for (uint8_t j = 0; j < m_length; j++)
    {
      Serial.print( node.getResponseBuffer(j), DEC );//以DEC（十）进制显示你要的数据
    }
  }
  else {
    
    Serial.print("ERROR:");
    Serial.println(result, HEX);//以HEX（16）进制显示错误信息（E2：你的TX,RX断线，E0：你的485转ttl板子有问题）
  }
delay(500);//延时500毫秒

}
