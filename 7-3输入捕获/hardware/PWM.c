#include "stm32f10x.h"                  // Device header


void PWM_Init(void)
{

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//tim2在apb1里
		
		TIM_InternalClockConfig(TIM2);//开启内部时钟
		
	
		//配置时基单元：
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
		TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数模式
		TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;//时钟频率＝72000000/（psc＋1）（ARR＋1），周期＝1/f,  ARR
		TIM_TimeBaseInitStructure.TIM_Prescaler =720 - 1 ;//psc，计数频率＝（psc+1）
		TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
		
		
		TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);//时基单元初始化
		
	
	
		TIM_OCInitTypeDef TIM_OCInitStructure;
		TIM_OCStructInit(&TIM_OCInitStructure);//结构体值太多了，不想一个个赋值，使用该函数给每一个变量赋初始值，下面再改需要的
		
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OCInitStructure.TIM_OutputState =TIM_OutputState_Enable ;
		TIM_OCInitStructure.TIM_Pulse = 0;//ccr   例子是1khz，占空比为50%的PWM
		
		TIM_OC1Init(TIM2,&TIM_OCInitStructure);
		
		
		//PWM频率=CK_PSC/（psc＋1）（ARR＋1）
		//PWM占空比=ccr/（ARR＋1）
		//PWM分辨率=1/（ARR＋1）
		
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	  
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//当定时器控制引脚时，应用复用开漏/推挽输出模式
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
		GPIO_Init(GPIOA,&GPIO_InitStructure);	
		
		
		TIM_Cmd(TIM2,ENABLE);
		
		
		





}
void PWM_SetCompare1(uint16_t Compare)
{



TIM_SetCompare1(TIM2,Compare);



}
