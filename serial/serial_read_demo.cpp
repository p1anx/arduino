void setup(){
  Serial.begin(115200);
}
void loop(){
  // Serial.println("hello queue");
  while(Serial.available() > 0){
    char c = Serial.read();
    Serial.print(c);
  }
}
