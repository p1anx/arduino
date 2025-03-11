#define FREQ 2000
#define RESOLUTION 8
#define LED 13
 
void setup() {
  // put your setup code here, to run once:
  ledcAttach(LED, FREQ, RESOLUTION);
}
 
void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0;i<pow(2,RESOLUTION);i++){
    ledcWrite(LED, i);
    delay(10);
    }
  for(int i=pow(2,RESOLUTION);i>=0;i--){
    ledcWrite(LED, i);
    delay(10);
    }
}

//ledcsetup()和ledcattachpin()已经在3.0 arduino.h移除了
//ref: https://blog.csdn.net/weixin_73690807/article/details/143751376
