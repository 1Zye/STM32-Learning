#include "stm32f10x.h"                  // Device header



void Timer_Init(void)
{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//tim2在apb1里
		
		TIM_InternalClockConfig(TIM2);//开启内部时钟
		
	
		//配置时基单元：
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
		TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数模式
		TIM_TimeBaseInitStructure.TIM_Period = 10000 - 1;//时钟频率＝72000000/（psc＋1）（ARR＋1），周期＝1/f,  ARR
		TIM_TimeBaseInitStructure.TIM_Prescaler =7200 - 1 ;//psc，计数频率＝（psc+1）
		TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
		
		
		TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);//时基单元初始化
	
		TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//配置定时中断,用以开启定时器中断
	
	
		//配置NVIC
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
		NVIC_InitTypeDef NVIC_InitStructure;
	
		NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		
		NVIC_Init(&NVIC_InitStructure);
		
		TIM_Cmd(TIM2,ENABLE);
		
		
		
}

/*
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)//永远先先检查更新标志位
	{
	
	
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//永远记得清除更新标志位
	}
	
	
	
	
}

*/



