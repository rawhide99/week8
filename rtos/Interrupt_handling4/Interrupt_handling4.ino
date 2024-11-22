#include <Arduino_FreeRTOS.h>

#define INTR_PIN_1 2
#define INTR_PIN_2 3  

volatile bool interruptFlag1 = false;
volatile bool interruptFlag2 = false;

void Task1(void* pvParameters);
void Task2(void* pvParameters);

void ISR_Interrupt1() 
{
  Serial.println("Interrupt 1 triggered");
  interruptFlag1 = true;
}

void ISR_Interrupt2() 
{
  Serial.println("Interrupt 2 triggered");
  interruptFlag2 = true;
}

void setup() 
{
  // Initialize serial communication
  Serial.begin(9600);
  delay(100);
  Serial.println("Setup started");
  
  // Set up interrupts
  pinMode(INTR_PIN_1, INPUT_PULLUP);
  pinMode(INTR_PIN_2, INPUT_PULLUP);
  
  // Attach interrupt service routines (ISRs)
  attachInterrupt(digitalPinToInterrupt(INTR_PIN_1), ISR_Interrupt1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(INTR_PIN_2), ISR_Interrupt2, CHANGE);

  // Create FreeRTOS tasks
  xTaskCreate(Task1, "Task1", 64, NULL, 2, NULL); // Task 1 has higher priority
  xTaskCreate(Task2, "Task2", 64, NULL, 1, NULL); // Task 2 has lower priority

  // Start the FreeRTOS scheduler
  vTaskStartScheduler();
  sei();
}

void loop() 
{
  // Empty loop because tasks are handled by FreeRTOS
}

// Task 1 - Handle Interrupt 1
void Task1(void* pvParameters) 
{
  while (1) 
  {
    if (interruptFlag1) 
    {
      Serial.println("Handling Interrupt 1");
      interruptFlag1 = false; // Reset flag after handling
    }
    vTaskDelay(100); // Prevent CPU overload
  }
}

// Task 2 - Handle Interrupt 2
void Task2(void* pvParameters) 
{
  while (1) 
  {
    if (interruptFlag2) 
    {
      Serial.println("Handling Interrupt 2");
      interruptFlag2 = false; // Reset flag after handling
    }
    vTaskDelay(100); // Prevent CPU overload
  }
}

