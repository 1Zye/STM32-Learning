#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "IC.h"

uint8_t i;

int main(void)
{		
		OLED_Init();
		IC_Init();
		PWM_Init();
		PWM_SetCompare1(50);
		OLED_ShowString(1,1,"Freq£º");
	
		while(1)
			{
				uint32_t num = IC_GetFreq();
				OLED_ShowNum(2,1,num,5);
			
			}
		

}
