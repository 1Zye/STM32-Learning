#include "stm32f10x.h"                  // Device header



void Encoder_Init(void){

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
//GPIO
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
		GPIO_Init(GPIOA,&GPIO_InitStructure);
	
//Timerbase
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;
		TIM_TimeBaseInitStruct.TIM_ClockDivision =	TIM_CKD_DIV1;
		TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInitStruct.TIM_Period = 65536-1;
		TIM_TimeBaseInitStruct.TIM_Prescaler = 1-1;
		TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	
		TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
		
		TIM_ICInitTypeDef  TIM_ICInitStruct;
		TIM_ICStructInit(&TIM_ICInitStruct);
		
//channel1 and channel2 Init
		TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;
		TIM_ICInitStruct.TIM_ICFilter = 0x0f;
		
		TIM_ICInit(TIM3,&TIM_ICInitStruct);
		
		TIM_ICInitStruct.TIM_Channel = TIM_Channel_2;
		TIM_ICInitStruct.TIM_ICFilter = 0x0f;
		
		TIM_ICInit(TIM3,&TIM_ICInitStruct);
		
		TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
//TI12指的是给到编码器的ab相波形每个上升沿都有效，后面两个参数指是否把对应输入极性反转,rising指的是不反转
//一定要在IC_Init下面
//TIM_EncoderInterfaceConfig() 到底做了什么：让 TIM 根据 A/B 两相自动判断方向并控制 CNT 加减。
		TIM_Cmd(TIM3,ENABLE);
		
}




uint32_t Encoder_GetCnt(void){


	uint32_t temp =  TIM_GetCounter(TIM3);
	TIM_SetCounter(TIM3,0);
	return temp;

//记得清零，不清零不到临界点是不会为0的
//为什么测速时 Encoder_GetCnt() 读取后要 TIM_SetCounter(TIM3, 0)：因为要统计“下一个固定时间窗”的增量。
}












