#include "task_display.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stdio.h"
#include "string.h"
#include "stm32f10x.h"


char InfoBuffer[1000];
char TaskInfo[10];

extern TaskHandle_t topTaskInfoHandle;

void top_task(void *pvParameters){
	//while(1){
	u32 TotalRunTime;
	UBaseType_t ArraySize,x;
	TaskStatus_t *StatusArray;
	
	
	//第二步：vTaskGetInfo()的使用
	TaskHandle_t TaskHandle;	
	TaskStatus_t TaskStatus;
	
	//第三步：eTaskGetState()使用
	eTaskState TaskState;
	
	//第一步：xTaskGetSystemState()的使用
	printf("/*******xTaskGetSystemState()**********/\r\n");
	ArraySize= uxTaskGetNumberOfTasks();		//获取任务数量
	StatusArray= pvPortMalloc(ArraySize*sizeof(TaskStatus_t));//内存申请
	if(StatusArray!=NULL)					//内存申请成功
	{
		ArraySize= uxTaskGetSystemState((TaskStatus_t* 	)StatusArray, 	//任务信息存储数组
									   (UBaseType_t		)ArraySize, 	//任务信息存储数组大小
								       (uint32_t*		)&TotalRunTime);//保存系统运行时间
		printf("TaskName\t\tPriority\t\tTaskNumber\t\t\r\n");
		for(x=0;x<ArraySize;x++)
		{
			//打印信息
			printf("%s\t\t%d\t\t\t%d\t\t\t\r\n",				
					StatusArray[x].pcTaskName,
					(int)StatusArray[x].uxCurrentPriority,
					(int)StatusArray[x].xTaskNumber);
			
		}
	}
	vPortFree(StatusArray);	//释放内存
	printf("/**************************结束**************************/\r\n");
	printf("按下KEY_UP按键\r\n\r\n\r\n");
//	while(KEY_Scan(0)!=WKUP_PRES) delay_ms(10);		//等待按下KEY_UP按键
	
	
	printf("/***********vTaskGetInfo()函数*************/\r\n");
	TaskHandle = xTaskGetHandle("ledTwoTask");			//根据任务名获取句柄
	//获取此任务信息
	vTaskGetInfo((TaskHandle_t	)TaskHandle, 		//任务句柄
				 (TaskStatus_t*	)&TaskStatus, 		//任务信息结构体
				 (BaseType_t	)pdTRUE,			//允许统计任务堆栈历史最小剩余量大小
			     (eTaskState	)eInvalid);			//运行状态
	//打印
	printf("任务名:                %s\r\n",TaskStatus.pcTaskName);
	printf("任务编号:              %d\r\n",(int)TaskStatus.xTaskNumber);
	printf("任务状态:              %d\r\n",TaskStatus.eCurrentState);
	printf("任务优先级:        %d\r\n",(int)TaskStatus.uxCurrentPriority);
	printf("任务基优先级:          %d\r\n",(int)TaskStatus.uxBasePriority);
	printf("任务堆栈基地址:        %#x\r\n",(int)TaskStatus.pxStackBase);
	printf("任务堆栈基地址:        %#x\r\n",(int)TaskStatus.pxStackBase);
	printf("任务堆栈历史最小剩余量大小:%d\r\n",TaskStatus.usStackHighWaterMark);
	printf("/**************************?áê?***************************/\r\n");
	printf("按下KEY_UP按键\r\n\r\n\r\n");
//while(KEY_Scan(0)!=WKUP_PRES) delay_ms(10);		//等待按下KEY_UP按键
	

	
	printf("/***********eTaskGetState()函数*************/\r\n");
	TaskHandle= xTaskGetHandle("ledTwoTask");		//根据任务名获取句柄
	TaskState= eTaskGetState(TaskHandle);			//获取任务状态
	memset(TaskInfo,0,10);						
	switch((int)TaskState)
	{
		case 0:
			sprintf(TaskInfo,"Running");
			break;
		case 1:
			sprintf(TaskInfo,"Ready");
			break;
		case 2:
			sprintf(TaskInfo,"Suspend");
			break;
		case 3:
			sprintf(TaskInfo,"Delete");
			break;
		case 4:
			sprintf(TaskInfo,"Invalid");
			break;
	}
	printf("任务状态值:%d,对应任务状态是:%s\r\n",TaskState,TaskInfo);
	printf("/*************************结束**************************/\r\n");
	printf("按下KEY_UP按键\r\n\r\n\r\n");
	//while(KEY_Scan(0)!=WKUP_PRES) delay_ms(10);		//等待按下KEY_UP按键
	
	//第四步vTaskList()的使用	
	printf("/*************vTaskList()函数************/\r\n");
	vTaskList(InfoBuffer);							//获取所有任务信息
	printf("%s\r\n",InfoBuffer);					//打印所有信息
	printf("/*************************结束**************************/\r\n");
	
	vTaskSuspend(topTaskInfoHandle);
	
//}
	//while(1){}
}

