#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "PWM.h"


void key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_50MHz;
  
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//上面配置的是上拉输入，所以下面GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)的初始值
	//是1，只有按下按钮才变成0执行if语句！！
}


	
uint16_t  Key_Getnum(void){
		uint8_t num = 0;
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0){
		Delay_ms(10);
				if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0){
				num = 1;
				while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0)
					Delay_ms(10);
				}
		}
			return num;
}
	
		
	
		
		
		
		
	
		












