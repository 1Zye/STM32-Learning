#include "stm32f10x.h"                  // Device header

void IC_Init(void){

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//
		
		TIM_InternalClockConfig(TIM3);//
		
	
		//配置时基单元：
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
		TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数模式
		TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;// arr越大越好，防止两次ccr的值在两个周期内
		TIM_TimeBaseInitStructure.TIM_Prescaler =72 - 1 ;// 72M/72=1MHz的计数频率
		TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
		
		
		TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//时基单元初始化
		
		

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	  
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
		GPIO_Init(GPIOA,&GPIO_InitStructure);	
	
		TIM_ICInitTypeDef  TIM_ICInitStruct;
		TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;
		TIM_ICInitStruct.TIM_ICFilter = 0x0f;//滤波
		TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
		TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;//每个上升沿都有效
		TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;//直连IC1
		
		TIM_ICInit(TIM3,&TIM_ICInitStruct);
		
		TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);//选择从模式的触发源
		TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);//选择从模式对应功能，这里是给cnt置零

		TIM_Cmd(TIM3,ENABLE);
}


uint32_t IC_GetFreq(void)
{
    return 1000000 / TIM_GetCapture1(TIM3);
}
