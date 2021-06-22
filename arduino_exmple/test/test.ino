//≥ı º≈‰÷√Œ Ã‚£∫https://blog.csdn.net/acktomas/article/details/102815385
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
