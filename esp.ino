#define alarm 5 //pin D1 on node esp
void setup() {
  Serial.begin(115200);
  pinMode(alarm, OUTPUT);
}

void loop() {
 int RxBuffer = 0;
 if(Serial.available()){
    RxBuffer = Serial.read();
 }
 if(RxBuffer == '1')
  {
    digitalWrite(alarm,HIGH);
    Serial.println("turn on alarm");
  }
  else if (RxBuffer == '0')
  {
    digitalWrite(alarm,LOW);
    Serial.println("turn off alarm");
  }
 
}
