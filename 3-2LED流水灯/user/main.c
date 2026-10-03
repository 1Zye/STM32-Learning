#include "stm32f10x.h"                  // Device header
#include "Delay.h"


int main(void)
{		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		
	
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
		GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz; 
		GPIO_Init(GPIOA,&GPIO_InitStructure);
	
		
		while(1)
		{
				GPIO_Write(GPIOA,~0x0001);  //0000 0000 0001
			//0000 0000 0001每一位控制一个引脚，1是高电平，0反之，本程序是低电平点亮，~的意思是逐位取反
				Delay_ms(100);
			
				GPIO_Write(GPIOA,~0x0008);  //0000 0000 1000
				Delay_ms(500);
			
				GPIO_Write(GPIOA,~0x0004);  //0000 0000 0100
				Delay_ms(500);
			
				GPIO_Write(GPIOA,~0x0002);  //0000 0000 0010
				Delay_ms(500);
		}

}














