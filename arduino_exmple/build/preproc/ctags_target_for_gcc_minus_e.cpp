# 1 "d:\\Learn\\Arduino\\arduino_exmple\\test\\test.ino"
void setup(){
    pinMode(14, 0x1);
    Serial.begin(115200);
}

void loop(){
    Serial.println("arduino 66666");
    digitalWrite(14, 0x1);
    delay(1000);
    digitalWrite(14, 0x0);
    delay(1000);
}
