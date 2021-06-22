#include <OneWireSTM.h>

// OneWire DS18S20, DS18B20, DS1822 Temperature Example
//
// Based on version by PJRC
//
// The DallasTemperature library can do all this work for you!
// http://milesburton.com/Dallas_Temperature_Control_Library

OneWire  ds(PB10);  // on pin 10 (a 4.7K resistor is necessary)
int Wire_Check()
{
  static int fail_count=0;
  byte type_s;
  byte addr[8];
  int i=0;
  fail_count++;
  if(fail_count>100)  //检测100次
    return 0;
  if ( !ds.search(addr)) {
    Serial.println("ERROR:  No more addresses.");
    Serial.println();
    ds.reset_search();
    delay(250);
    digitalWrite(LED_BUILTIN, HIGH);
    return 1;
  }
  Serial.print("ROM =");
  for( i = 0; i < 8; i++) {
    Serial.write(' ');
    Serial.print(addr[i], HEX);
  }

  if (OneWire::crc8(addr, 7) != addr[7]) {
      Serial.println("ERROR:  CRC is not valid!");
      digitalWrite(LED_BUILTIN, HIGH);
      return 1;
  }
  Serial.println();
  switch (addr[0]) {
    case 0x10:
      Serial.println("Chip = DS18S20");  // or old DS1820
      type_s = 1;
      break;
    case 0x28:
      Serial.println("Chip = DS18B20");
      type_s = 0;
      break;
    case 0x22:
      Serial.println("Chip = DS1822");
      type_s = 0;
      break;
    default:
      Serial.println("Device is not a DS18x20 family device.");
      return 1;
  }
  return 0;
}
void setup(void) {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  while(Wire_Check())
  {
    ;
  }
  digitalWrite(LED_BUILTIN, LOW);
}
byte i;
byte present = 0;
byte type_s;
byte data[12];
byte addr[8];
float celsius, fahrenheit;
int count=0;
int temp=0;
void loop(void) {
  while( !ds.search(addr)) {
    count++;
    if(count>2)
    {
      Serial.println("No more addresses.");
      Serial.println();
      ds.reset_search();
      delay(250);
      digitalWrite(LED_BUILTIN, HIGH);
      count=0;
      return;
    }
  }
  count=0;
  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);        // start conversion, with parasite power on at the end
  
  delay(1000);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.
  
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad

  for ( i = 0; i < 9; i++)            // we need 9 bytes
    data[i] = ds.read();
  // Convert the data to actual temperature
  // because the result is a 16 bit signed integer, it should
  // be stored to an "int16_t" type, which is always 16 bits
  // even when compiled on a 32 bit processor.
  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }
  celsius = (float)raw / 16.0;
  fahrenheit = celsius * 1.8 + 32.0;
  if(celsius!=temp)  //只有温度发生改变时才进行打印
  {
    temp=celsius;   //更新上次温度值
    Serial.print("  Temperature = ");
    Serial.print(celsius);
    Serial.print(" Celsius, ");
    Serial.print(fahrenheit);
    Serial.println(" Fahrenheit");
    digitalWrite(LED_BUILTIN, LOW);  
  }
}
