#ifndef __LED_H
#define __LED_H

#include "stm32f10x_gpio.h"

/**
 * 初始化PA8脚
 */
#define LED0_PA GPIO_Pin_8

/**
 * 初始化PD2脚
 */
#define LED1_PD GPIO_Pin_2


typedef enum {ON = 0, OFF = !ON} SwitchState;

//LED初始化函数
void LED_Init(void);

//LED开关
void LED_State(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,BitAction state);

uint8_t getLedOneDataBit(void);

void setLedOneState(BitAction state);

uint8_t getLedTwoDataBit(void);

void setLedTwoState(BitAction state);


#endif
