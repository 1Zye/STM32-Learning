#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"


uint16_t num;

int main(void)
{		
		OLED_Init();
		Timer_Init();
		OLED_ShowString(1,1,"num:");//字符串要双引号
		
		while(1)
		{
			OLED_ShowNum(1,5,num,5);
			
		}
		

}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)//永远先先检查更新标志位
	{
	
		num ++;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//永远记得清除更新标志位
	}
	
}

