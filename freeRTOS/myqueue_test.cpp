#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

QueueHandle_t msgQueue;

void send_task(void *param){
  char recv_msg;
  while(1){
    while(Serial.available()> 0){
      recv_msg = Serial.read();
      xQueueSend(msgQueue, &recv_msg, portMAX_DELAY);
    }
    vTaskDelay(1000);//important
    // Serial.println("wait for input");
  }

}
void recv_task(void *param){
  char recv_msg1;
  while(1){
    if(xQueueReceive(msgQueue, &recv_msg1, portMAX_DELAY)){
      // Serial.print("input data = ");
      Serial.print(recv_msg1);
    }
  }

}

void setup(){
  Serial.begin(115200);
  msgQueue = xQueueCreate(10, 8);
  if(msgQueue == NULL){
    Serial.println("failed to create queue");
  }
  xTaskCreate(recv_task, "recv task", 1024, NULL, 1, NULL);
  xTaskCreate(send_task, "send task", 1024, NULL, 1, NULL);
}
void loop(){

}
