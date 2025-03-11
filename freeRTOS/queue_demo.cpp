#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#define QUEUE_LENGTH 10

// 消息结构体
typedef struct {
  int value;
  char message[50];
} Message;

// 消息队列
QueueHandle_t messageQueue;

// 发送任务
void senderTask(void *pvParameters) {
  Message message;
  for (int i = 0; i < 10; i++) {
    message.value = i;
    sprintf(message.message, "Message %d", i);
    xQueueSend(messageQueue, &message, portMAX_DELAY);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
  vTaskDelete(NULL);
}

// 接收任务
void receiverTask(void *pvParameters) {
  Message message;
  while (1) {
    if (xQueueReceive(messageQueue, &message, portMAX_DELAY)) {
      Serial.print("Received message: ");
      Serial.print(message.value);
      Serial.print(" - ");
      Serial.println(message.message);
    }
  }
}

void setup() {
  Serial.begin(115200);

  // 创建消息队列
  messageQueue = xQueueCreate(QUEUE_LENGTH, sizeof(Message));
  if (messageQueue == NULL) {
    Serial.println("Failed to create message queue.");
    while (1);
  }

  // 创建发送任务
  xTaskCreate(senderTask, "Sender Task", 2048, NULL, 1, NULL);

  // 创建接收任务
  xTaskCreate(receiverTask, "Receiver Task", 2048, NULL, 1, NULL);
}

void loop() {
  // Nothing to do in loop
}

