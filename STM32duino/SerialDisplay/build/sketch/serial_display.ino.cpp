#include <Arduino.h>
#line 1 "d:\\Learn\\Arduino\\STM32duino\\SerialDisplay\\serial\\serial_display\\serial_display.ino"
/*
 * @Author: liguiyin
 * @Date: 2019-12-01 10:35:53
 * @LastEditTime: 2019-12-01 14:10:53
 * @Description: README
 * @FilePath: \SerialDisplay\serial\test1.ino
 */
/*串口接收数据最大长度*/
#define _SER_RECBUFSIZE 512
char serial_recive[_SER_RECBUFSIZE] ="";  /*串口数据接收字符串*/
int status=0;
/*
  读取串口输入(单个字节延迟2ms)
*/
int Serial_Read(char* result)
{
  int single = 0;
  while(Serial.available() > 0)
  {
    single = Serial.read();
    delay(2);
    if(single == '\n')
    {
      *(result++) = '\0';
      Serial.flush();
      return 0;
    }
    if(single != '\r')
      *(result++) = single;
  }
}

/*
  清空串口接收缓冲区
*/
void Serial_BuffClear()
{
    for(int i = 0 ; i < _SER_RECBUFSIZE ;i++)
    {
        serial_recive[i] = 0x00 ;
    }
}


void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
}
void loop()
{
  while(Serial_Read(serial_recive) == 0)
  {
    if(strlen(serial_recive) > 0)
    {
      Serial.println(serial_recive);
      digitalWrite(LED_BUILTIN, status);
      Serial_BuffClear();
      status=!status;
    }
  }
}

