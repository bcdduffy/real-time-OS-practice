#include "scheduler.h"

TaskHandle_t xHandle1 = NULL;
TaskHandle_t xHandle2 = NULL;
TaskHandle_t xHandle3 = NULL;
TaskHandle_t xHandle4 = NULL;
TaskHandle_t xHandle5 = NULL;

enum resources {R1, R2};



// the loop function runs over and over again forever
void loop() {}


static void testFunc1( void *pvParameters )
{
  Serial.println("Task1Start");
  vTaskDelay( pdMS_TO_TICKS(1000) );
  Serial.println("Task1Crit__R1__start");
	
  vSchedulerResourceWait(R1);
  vTaskDelay( pdMS_TO_TICKS(1000) );
	

  Serial.println("Task2Crit__R1__END");
  vSchedulerResourceSignal(R1);
  // back to normal execution
  vTaskDelay( pdMS_TO_TICKS(1000) );
  Serial.println("Task1END");
}

static void testFunc2( void *pvParameters )
{
  Serial.println("Task2Start");
  vTaskDelay( pdMS_TO_TICKS(1000) );
  Serial.println("Task2Crit__R2__start");
	
  vSchedulerResourceWait(R2);
  vTaskDelay( pdMS_TO_TICKS(1000) );
	

  Serial.println("Task2Crit__R2__END");
  vSchedulerResourceSignal(R2);
  // back to normal execution
  vTaskDelay( pdMS_TO_TICKS(1000) );
  Serial.println("Task2END");
}

static void testFunc3( void *pvParameters )
{
  Serial.println("Task3Start");
  vTaskDelay( pdMS_TO_TICKS(2000) );
  Serial.println("Task3END");
}

static void testFunc4(void *pvParameters) {
   volatile int i, j;
  // normal execution
  Serial.println("Task4Start");
  vTaskDelay( pdMS_TO_TICKS(1000) );
  Serial.println("Task4CritR1start");
	
  vSchedulerResourceWait(R1);
  vTaskDelay( pdMS_TO_TICKS(1500) );
	
  Serial.println("Task4Crit__R2__start");
  vSchedulerResourceWait(R2);
  vTaskDelay( pdMS_TO_TICKS(1500) );
	
  Serial.println("Task4Crit__R2__END");
  vSchedulerResourceSignal(R2);

  vTaskDelay( pdMS_TO_TICKS(1000) );

  Serial.println("Task4Crit__R1__END");
  vSchedulerResourceSignal(R1);
  // back to normal execution
  vTaskDelay( pdMS_TO_TICKS(1000) );
  Serial.println("Task4END");
}

static void testFunc5( void *pvParameters )
{
  Serial.println("Task5Start 0");
  vTaskDelay( pdMS_TO_TICKS(1000) );
  Serial.println("Task5Crit__R2__start 1000");
	
  vSchedulerResourceWait(R2);
  vTaskDelay( pdMS_TO_TICKS(4000) );
	

  Serial.println("Task5Crit__R2__END 4000");
  vSchedulerResourceSignal(R2);
  // back to normal execution
  vTaskDelay( pdMS_TO_TICKS(1000) );
  Serial.println("Task5END 5000");
}



int main( void )
{
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }
	char c1 = 'a';
	char c2 = 'b';
  	char c3 = 'c';
    	char c4 = 'd';
      char c5 = 'e';			

	vSchedulerInit();
  Serial.println();
    Serial.println();

  Serial.println();


  vSchedulerPeriodicTaskCreate(testFunc1, "t1", configMINIMAL_STACK_SIZE, &c1, 5, &xHandle1, pdMS_TO_TICKS(7000), pdMS_TO_TICKS(21000), pdMS_TO_TICKS(3000), pdMS_TO_TICKS(21000));
	vSchedulerPeriodicTaskCreate(testFunc2, "t2", configMINIMAL_STACK_SIZE, &c2, 4, &xHandle2, pdMS_TO_TICKS(5000), pdMS_TO_TICKS(22000), pdMS_TO_TICKS(3000), pdMS_TO_TICKS(22000));
  vSchedulerPeriodicTaskCreate(testFunc3, "t3", configMINIMAL_STACK_SIZE, &c3, 3, &xHandle3, pdMS_TO_TICKS(4000), pdMS_TO_TICKS(23000), pdMS_TO_TICKS(2000), pdMS_TO_TICKS(23000));
  vSchedulerPeriodicTaskCreate(testFunc4, "t4", configMINIMAL_STACK_SIZE, &c4, 2, &xHandle4, pdMS_TO_TICKS(2000), pdMS_TO_TICKS(24000), pdMS_TO_TICKS(6000), pdMS_TO_TICKS(24000));
  vSchedulerPeriodicTaskCreate(testFunc5, "t5", configMINIMAL_STACK_SIZE, &c5, 1, &xHandle5, pdMS_TO_TICKS(0), pdMS_TO_TICKS(25000), pdMS_TO_TICKS(6000), pdMS_TO_TICKS(25000));


  //vSetResourceCeiling(R1, 3);


  	


//void vSchedulerPeriodicTaskCreate(pvTaskCode, pcName, uxStackDepth, pvParameters, uxPriority, pxCreatedTask, xPhaseTick, xPeriodTick, xMaxExecTimeTick, xDeadlineTick)

	vSchedulerStart();
  //xHandle
	/* If all is well, the scheduler will now be running, and the following line
	will never be reached. */
	
	for( ;; );
}

