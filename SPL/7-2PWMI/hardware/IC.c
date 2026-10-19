#include "stm32f10x.h"                  // Device header

void IC_Init(void){

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//tim2在apb1里
		
		TIM_InternalClockConfig(TIM3);//开启内部时钟
		
	
		//配置时基单元：
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
		TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数模式
		TIM_TimeBaseInitStructure.TIM_Period = 65536-1;
		TIM_TimeBaseInitStructure.TIM_Prescaler =72 - 1 ;//psc，计数频率＝（psc+1）
		TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
		
		
		TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//时基单元初始化

	
	
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	  
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//当定时器控制引脚时，应用复用开漏/推挽输出模式
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
		GPIO_Init(GPIOA,&GPIO_InitStructure);

		TIM_ICInitTypeDef  TIM_ICInitStruct;
		TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;
		TIM_ICInitStruct.TIM_ICFilter = 0x00;
		TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
		TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
		TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;

		TIM_PWMIConfig(TIM3,&TIM_ICInitStruct);//和上面的配置相反，作用是一个gpio的捕获送到两个IC通道
		
		
		TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);
		TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);
		
		TIM_Cmd(TIM3,ENABLE);
}

uint32_t IC_GetFreq(void){

	return 1000000/TIM_GetCapture1(TIM3);
	
}

uint32_t IC_GetDuty(void){

	return ((TIM_GetCapture2(TIM3)+1)*100)/(TIM_GetCapture1(TIM3)+1);


}


