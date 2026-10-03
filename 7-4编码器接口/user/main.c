#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
#include "Encoder.h"


int16_t Speed;

int main(void)
{		
		OLED_Init();
		Encoder_Init();
		Timer_Init();
		OLED_ShowString(1,1,"Speed:");//字符串要双引号
		
		while(1)
		{
			OLED_ShowSignedNum(1,7,Speed,5);
			
		}
		

}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)//永远先先检查更新标志位
	{
		Speed = Encoder_GetCnt();
		
		
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//永远记得清除更新标志位
	}
	
}

