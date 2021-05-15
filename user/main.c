#include "FreeRTOS.h"
#include "task.h"
#include "led.h"
#include "usart.h"
#include "stdio.h"
#include "task_display.h"

#define taskBASICPRIORITY        1
#define ledOnePRI               (taskBASICPRIORITY+1)
#define ledOneTaskSize 					(configMINIMAL_STACK_SIZE)

#define ledTwoPRI               (taskBASICPRIORITY+2)
#define ledTwoTaskSize 					(configMINIMAL_STACK_SIZE)

#define topTaskPRI 							(taskBASICPRIORITY+3)
#define topTaskSize 					(configMINIMAL_STACK_SIZE)

/**
 * LED1 ����
 */
static void ledOneTask(void *pvParameters);


/**
 * LED2 ����
 */
static void ledTwoTask(void *pvParameters);

/**
 * LED ��ʼ������
 */
extern void LED_Init(void);


/**
 * ��ѯfreertosϵͳ������
 */
extern void top_task(void *pvParameters);

//extern int printf(const char *format, ...);
TaskHandle_t topTaskInfoHandle;


int main(void){

	
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
	
	LED_Init();
	
	USART_Config(9600);
	//setLedOneState(Bit_SET);
	
	//taskENTER_CRITICAL();
	
	//printf("\r\n main start\r\n");
	//����LED1����
	xTaskCreate( ledOneTask, "ledOneTask", ledOneTaskSize, NULL, ledOnePRI, NULL );
	//����LED2����
	xTaskCreate( ledTwoTask, "ledTwoTask", ledTwoTaskSize, NULL, ledTwoPRI, NULL );
	
	//�鿴�����������
	xTaskCreate( top_task, "top_task", topTaskSize, NULL, topTaskPRI, &topTaskInfoHandle);
	
	vTaskStartScheduler();
	
	
	
	//taskEXIT_CRITICAL();
}

void ledOneTask(void *pvParameters){

	while(1){
			
			GPIO_WriteBit(GPIOA, GPIO_Pin_8,  Bit_RESET);
		  vTaskDelay(100 / portTICK_PERIOD_MS);
		  GPIO_WriteBit(GPIOA, GPIO_Pin_8,  Bit_SET);
		  vTaskDelay(100 / portTICK_PERIOD_MS);
		
		
	}
	
}


void ledTwoTask(void *pvParameters){

	while(1){
			printf("\r\nledTwoTask\r\n");
		  GPIO_WriteBit(GPIOD, GPIO_Pin_2,  Bit_RESET);
		  vTaskDelay(50 / portTICK_PERIOD_MS);
		  GPIO_WriteBit(GPIOD, GPIO_Pin_2,  Bit_SET);
		  vTaskDelay(50 / portTICK_PERIOD_MS);
	}
	
}


