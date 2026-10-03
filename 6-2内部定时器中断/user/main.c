#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "timer.h"
#include "LED.h"

uint16_t num;

int main(void)
{		
		OLED_Init();
		LED_Init();
		Timer_Init();
		OLED_ShowString(1,1,"CNT");//字符串要双引号
		
		
		while(1){
		
		OLED_ShowNum(2,1,TIM_GetCounter(TIM2),5);
		
		}

}



void TIM2_IRQHandler(void){

	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET )
		{
			num++;
			LED_turn();
			TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//永远记得清除更新标志位
	  }




}

