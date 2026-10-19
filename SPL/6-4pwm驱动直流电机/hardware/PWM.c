#include "stm32f10x.h"                  // Device header

void PWM_Init(void){

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	TIM_InternalClockConfig(TIM2);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	  
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);	
	

	TIM_TimeBaseInitTypeDef TimeBaseInitStructure;
	
	
	TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TimeBaseInitStructure.TIM_Period = 50-1;
	TimeBaseInitStructure.TIM_Prescaler = 72-1;
	TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	// psc= 72-1  arr=50-1  F=20kHz T=0.05ms
	//cnt计数频率是1000kHz,计算一个数的时间是1us 
	// compare=10   占空比20%
	//         20         40%
	//         30         60%
	//
	//         50        100%
	
	
	
	TIM_TimeBaseInit(TIM2,&TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	
	TIM_OC1Init(TIM2,&TIM_OCInitStructure);
	TIM_Cmd(TIM2,ENABLE);
	
}
	
void PWM_SetCompare(uint8_t Compare){

	TIM_SetCompare1(TIM2,Compare);

}
	
