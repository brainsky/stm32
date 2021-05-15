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
	
	
	//�ڶ�����vTaskGetInfo()��ʹ��
	TaskHandle_t TaskHandle;	
	TaskStatus_t TaskStatus;
	
	//��������eTaskGetState()ʹ��
	eTaskState TaskState;
	
	//��һ����xTaskGetSystemState()��ʹ��
	printf("/*******xTaskGetSystemState()**********/\r\n");
	ArraySize= uxTaskGetNumberOfTasks();		//��ȡ��������
	StatusArray= pvPortMalloc(ArraySize*sizeof(TaskStatus_t));//�ڴ�����
	if(StatusArray!=NULL)					//�ڴ�����ɹ�
	{
		ArraySize= uxTaskGetSystemState((TaskStatus_t* 	)StatusArray, 	//������Ϣ�洢����
									   (UBaseType_t		)ArraySize, 	//������Ϣ�洢�����С
								       (uint32_t*		)&TotalRunTime);//����ϵͳ����ʱ��
		printf("TaskName\t\tPriority\t\tTaskNumber\t\t\r\n");
		for(x=0;x<ArraySize;x++)
		{
			//��ӡ��Ϣ
			printf("%s\t\t%d\t\t\t%d\t\t\t\r\n",				
					StatusArray[x].pcTaskName,
					(int)StatusArray[x].uxCurrentPriority,
					(int)StatusArray[x].xTaskNumber);
			
		}
	}
	vPortFree(StatusArray);	//�ͷ��ڴ�
	printf("/**************************����**************************/\r\n");
	printf("����KEY_UP����\r\n\r\n\r\n");
//	while(KEY_Scan(0)!=WKUP_PRES) delay_ms(10);		//�ȴ�����KEY_UP����
	
	
	printf("/***********vTaskGetInfo()����*************/\r\n");
	TaskHandle = xTaskGetHandle("ledTwoTask");			//������������ȡ���
	//��ȡ��������Ϣ
	vTaskGetInfo((TaskHandle_t	)TaskHandle, 		//������
				 (TaskStatus_t*	)&TaskStatus, 		//������Ϣ�ṹ��
				 (BaseType_t	)pdTRUE,			//����ͳ�������ջ��ʷ��Сʣ������С
			     (eTaskState	)eInvalid);			//����״̬
	//��ӡ
	printf("������:                %s\r\n",TaskStatus.pcTaskName);
	printf("������:              %d\r\n",(int)TaskStatus.xTaskNumber);
	printf("����״̬:              %d\r\n",TaskStatus.eCurrentState);
	printf("�������ȼ�:        %d\r\n",(int)TaskStatus.uxCurrentPriority);
	printf("��������ȼ�:          %d\r\n",(int)TaskStatus.uxBasePriority);
	printf("�����ջ����ַ:        %#x\r\n",(int)TaskStatus.pxStackBase);
	printf("�����ջ����ַ:        %#x\r\n",(int)TaskStatus.pxStackBase);
	printf("�����ջ��ʷ��Сʣ������С:%d\r\n",TaskStatus.usStackHighWaterMark);
	printf("/**************************?����?***************************/\r\n");
	printf("����KEY_UP����\r\n\r\n\r\n");
//while(KEY_Scan(0)!=WKUP_PRES) delay_ms(10);		//�ȴ�����KEY_UP����
	

	
	printf("/***********eTaskGetState()����*************/\r\n");
	TaskHandle= xTaskGetHandle("ledTwoTask");		//������������ȡ���
	TaskState= eTaskGetState(TaskHandle);			//��ȡ����״̬
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
	printf("����״ֵ̬:%d,��Ӧ����״̬��:%s\r\n",TaskState,TaskInfo);
	printf("/*************************����**************************/\r\n");
	printf("����KEY_UP����\r\n\r\n\r\n");
	//while(KEY_Scan(0)!=WKUP_PRES) delay_ms(10);		//�ȴ�����KEY_UP����
	
	//���Ĳ�vTaskList()��ʹ��	
	printf("/*************vTaskList()����************/\r\n");
	vTaskList(InfoBuffer);							//��ȡ����������Ϣ
	printf("%s\r\n",InfoBuffer);					//��ӡ������Ϣ
	printf("/*************************����**************************/\r\n");
	
	vTaskSuspend(topTaskInfoHandle);
	
//}
	//while(1){}
}

