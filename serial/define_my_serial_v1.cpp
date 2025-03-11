/*通过串口控制LED灯的亮灭，输入o开灯，输入f关灯*/
#define  led  13
HardwareSerial myserial(1);
void setup(){
  Serial2.begin(115200);
  Serial1.begin(115200);
  Serial.begin(115200);
  myserial.begin(115200, SERIAL_8N1, 19, 20);

  pinMode(led, OUTPUT);
}
String a = "000";
void loop(){
  Serial2.println("hello uart2");
  Serial1.println("T1.1");

  // myserial.println("this is my serial");
  if(Serial1.available()){
    String c = Serial1.readStringUntil('\n');
    Serial.print("recv = ");
    Serial.println(c);
  }
  Serial.println(a);
  delay(500);

}
// serial interrupt
void serialEvent(){
  while(Serial.available()){
    a = Serial.readStringUntil('\n');
    Serial.println("irq is started");
  }
}
