#include "stm32f10x.h"                  // Device header
#include "Delay.h"


void key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_50MHz;
  
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//上面配置的是上拉输入，所以下面GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)的初始值
	//是1，只有按下按钮才变成0执行if语句！！
}

uint8_t key_getnum(void){
		uint8_t keynum = 0;
		if  (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0)//控制a2引脚
		{
			Delay_ms(20);//消除抖动
			while (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0);//如果一直按着，会在循环里出不去
			Delay_ms(20);//消除抖动
			keynum = 1;
			
		}
		
		
		if  (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0)//控制a1引脚
		{
			Delay_ms(20);
			while (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0);
			Delay_ms(20);
			keynum = 2;
			
		}
		
				if  (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) == 0)//控制a1引脚
		{
			Delay_ms(20);
			while (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0);
			Delay_ms(20);
			keynum = 3;
			
		}
		
		return keynum;


}









