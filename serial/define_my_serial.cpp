/*通过串口控制LED灯的亮灭，输入o开灯，输入f关灯*/
#define  led  13
//uart1 serial1 rx:19 tx:20
HardwareSerial myserial(1);
void setup(){
  Serial2.begin(115200);
  Serial1.begin(115200);
  Serial.begin(115200);
  myserial.begin(115200, SERIAL_8N1, 19, 20);//19 and 20 define serial gpio rx and tx

  pinMode(led, OUTPUT);
}

void loop(){
  Serial2.println("hello uart2");
  Serial1.println("hello uart1");
  Serial.println("hello uart");
  myserial.println("this is my serial");
  delay(500);

}
