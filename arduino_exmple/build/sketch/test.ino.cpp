#include <Arduino.h>
#line 1 "d:\\Learn\\Arduino\\arduino_exmple\\test\\test.ino"
#line 1 "d:\\Learn\\Arduino\\arduino_exmple\\test\\test.ino"
void setup();
#line 6 "d:\\Learn\\Arduino\\arduino_exmple\\test\\test.ino"
void loop();
#line 1 "d:\\Learn\\Arduino\\arduino_exmple\\test\\test.ino"
void setup(){
    pinMode(14, OUTPUT);
    Serial.begin(115200);
}

void loop(){
    Serial.println("arduino 66666");
    digitalWrite(14, HIGH);
    delay(1000);
    digitalWrite(14, LOW);
    delay(1000);
}

