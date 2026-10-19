#include "stm32f10x.h"                  // Device header



void PWM_Init(void){

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_50MHz;
  
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TimeBaseInitStructure;
	TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TimeBaseInitStructure.TIM_Period = 2000 - 1;
	TimeBaseInitStructure.TIM_Prescaler = 720 - 1;
	TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM2,&TimeBaseInitStructure);
	
	TIM_OCInitTypeDef  TIM_OCInitStruct;
	TIM_OCStructInit(&TIM_OCInitStruct);
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse = 0;//Õ¼¿Õ±È
	
	TIM_OC1Init(TIM2,&TIM_OCInitStruct);
	TIM_Cmd(TIM2,ENABLE);
}


void PWM_SetCompare1(uint16_t Compare){

	TIM_SetCompare1(TIM2,Compare);



}



