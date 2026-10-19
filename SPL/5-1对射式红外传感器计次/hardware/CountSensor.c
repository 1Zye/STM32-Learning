#include "stm32f10x.h"                  // Device header



uint16_t CountSensor_Count;
void CountSensor_Init(void)
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//可以通过查gpio的推荐输入模式确定
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
		GPIO_Init(GPIOB,&GPIO_InitStructure);
	
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);
		//AFIO的初始化函数，前面选择GPIO口，后面选择PIN口
		//此函数运行后，数据就被选择完成，可以顺利进入EXTI
		//APIO就这一个
	
		EXTI_InitTypeDef EXTI_InitStructure;
		EXTI_InitStructure.EXTI_Line = EXTI_Line14;//选择中断线
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;//中断线状态
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//选择事件模式（Event）还是中断模式
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
		EXTI_Init(&EXTI_InitStructure);
		
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
		
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel =EXTI15_10_IRQn ;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =1 ;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		NVIC_Init(&NVIC_InitStructure);
		
}
uint16_t CountSensor_get(void)
{
	return CountSensor_Count;

}


void EXTI15_10_IRQHandler(void)//注意：每一个通道的中断函数的名字都是固定的
{
		if(EXTI_GetITStatus(EXTI_Line14) == SET)//确保是14进来的中断信号，因为15-10都能进入中断信号，set是1，reset是0
		{
				CountSensor_Count ++;
				EXTI_ClearITPendingBit(EXTI_Line14);//每次执行完中断函数记得把标志位置0
		}


}





