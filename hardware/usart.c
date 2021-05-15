#include "usart.h"
#include "stdio.h"

void USART_Config(u32 baudrate){
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	USART_InitTypeDef USART_InitStructure;
	
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//使能USART1, PA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9;//PA9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //设置复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //设置50Mhz
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA9,Tx发送数据
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;//PA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //设置浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA10，作为接收数据 Rx
	
	USART_InitStructure.USART_BaudRate = baudrate;
	
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1; //1位停止位
	USART_InitStructure.USART_Parity = USART_Parity_No; //无奇偶校验
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART1, &USART_InitStructure);
	
	//#if EN_USART1_RX
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	//#endif
	USART_Cmd(USART1, ENABLE);
}



//向串口写入数据
int fputc(int ch, FILE *f){
	
	USART_SendData(USART1, (unsigned char) ch);
	
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET);
	
	return (ch);
}

//向读串口数据
int fgetc(FILE *f){
	
	while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
	
	return (int)USART_ReceiveData(USART1);
}



