vscode头文件报错：
1）右下角linux改成arduino；
2）第三方库从/root复制到/home/Arduino/libraries；

**编译选择arduino pro

esp32 Serial2 G16 -->485TXD
              G17 -->485RXD
*/
#ifndef RX1
#define RX1 9
#endif

#ifndef TX1
#define TX1 10
#endif

#ifndef RX2
#define RX2 16
#endif

#ifndef TX2
#define TX2 17
#endif
/*
              
esp32 can G4 G5  /src/ACAN_ESP32_Settings.h
*/
#ifdef ARDUINO
    public: gpio_num_t mTxPin = GPIO_NUM_5 ;
    public: gpio_num_t mRxPin = GPIO_NUM_4 ;
#endif
/*


freertos 启动失败修改stack size 1024 >>>>2048



