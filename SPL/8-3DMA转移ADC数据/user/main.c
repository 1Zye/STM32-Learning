#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "adc.h"

extern uint16_t DataA[];

int main(void)
{		
		OLED_Init();
		Adc_Init();
		OLED_ShowString(1,1,"DataA0:");//×Ö·û´®ÒªË«ÒýºÅ
		OLED_ShowString(2,1,"DataA1:");
		while(1)
		{
			OLED_ShowHexNum(1,8,DataA[0],4);
			OLED_ShowHexNum(2,8,DataA[1],4);
			
			}
		

}
