#include <Arduino_FreeRTOS.h>
#include <stdlib.h>

TaskHandle_t taskHandle_a = NULL;
TaskHandle_t taskHandle_b = NULL;
TaskHandle_t taskHandle_c = NULL;
TaskHandle_t taskHandle_d = NULL;

// Task A: Periodic Data Buffer Allocation
void task_a(void *pvParams)
{
  Serial.println("Task A started.");
  for (;;)
  {
    void *buffer = pvPortMalloc(512);
    if (buffer)
    {
      Serial.println("Task A: memory allocated of 512 bytes.");
      vTaskDelay(pdMS_TO_TICKS(100));
      vPortFree(buffer);
      Serial.println("Task A: Memory freed.");
    }
    else
    {
      Serial.println("Task A: Memory allocation failed.");
    }
    vTaskDelay(pdMS_TO_TICKS(50));
  }
}

// Task B: Random Size Allocation
void task_b(void *pvParams)
{
  Serial.println("Task B started.");
  for (;;)
  {
    size_t alloc_mem = rand() % 1024;
    void *buffer = pvPortMalloc(alloc_mem);
    if (buffer)
    {
      char logBuffer[50];
      sprintf(logBuffer, "Task B: memory allocated of %u bytes.", alloc_mem);
      Serial.println(logBuffer);
      vTaskDelay(pdMS_TO_TICKS(100));
      vPortFree(buffer);
      Serial.println("Task B: Memory freed.");
    }
    else
    {
      Serial.println("Task B: Memory allocation failed.");
    }
    vTaskDelay(pdMS_TO_TICKS(50));
  }
}

// Task C: Frequent Small Allocations
void task_c(void *pvParams)
{
  Serial.println("Task C started.");
  for (;;)
  {
    void *block = pvPortMalloc(128);
    if (block)
    {
      Serial.println("Task C: memory allocated of 128 bytes.");
      vTaskDelay(pdMS_TO_TICKS(100)); // 100 ms delay
      vPortFree(block);
      Serial.println("Task C: Memory freed.");
    }
    else
    {
      Serial.println("Task C: Memory allocation failed.");
    }
    vTaskDelay(pdMS_TO_TICKS(50));
  }
}

// Task D: Persistent Large Allocation
void task_d(void *pvParams)
{
  Serial.println("Task D started.");
  void *largeBlock = pvPortMalloc(4096);
  if (largeBlock)
  {
    Serial.println("Task D: Memory allocated (4096 bytes).");
    for (;;)
    {
      vTaskDelay(pdMS_TO_TICKS(1000));
    }
    vPortFree(largeBlock); // Cleanup (unreachable in this example)
    Serial.println("Task D: Memory freed.");
  }
  else
  {
    Serial.println("Task D: Memory allocation failed.");
  }
}

void setup() 
{
  Serial.begin(9600);
  delay(1000);   // Let serial communication establish
  Serial.flush();  // Ensure any pending serial data is transmitted
  Serial.println("Setup complete");
  
  // Create tasks
  xTaskCreate(task_a, "task_a", 2048, NULL, 1, &taskHandle_a);
  //xTaskCreate(task_b, "task_b", 1024, NULL, 1, &taskHandle_b);
  //xTaskCreate(task_c, "task_c", 1024, NULL, 1, &taskHandle_c);
  //xTaskCreate(task_d, "task_d", 1024, NULL, 1, &taskHandle_d);
}


void loop()
{
  // Nothing here
}
