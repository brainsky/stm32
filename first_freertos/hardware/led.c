#include "led.h"
#include "stm32f10x_gpio.h"

//初始化LED0 LED1

void LED_Init(void){
	
	GPIO_InitTypeDef  GPIO_InitStructure;
	//使能PA、PD时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD, ENABLE);
	
	//设置pin8脚
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	
	//设置推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//设置PAD高电平
	GPIO_SetBits(GPIOA, GPIO_Pin_8);
	
	//设置pinD2脚
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOD, GPIO_Pin_2);
}

void LED_State(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction state){
	GPIO_WriteBit(GPIOx, GPIO_Pin,  state);
}

uint8_t getLedOneDataBit(){
	
	return GPIO_ReadInputDataBit(GPIOA, LED0_PA);
	
}

void setLedOneState(BitAction state){
	
	LED_State(GPIOA, LED0_PA, state);
	
}




uint8_t getLedTwoDataBit(){
	
	return GPIO_ReadInputDataBit(GPIOA, LED1_PD);
	
}


void setLedTwoState(BitAction state){
	
		LED_State(GPIOD, LED1_PD, state);
}
