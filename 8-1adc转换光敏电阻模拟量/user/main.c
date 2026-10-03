#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "adc.h"



int main(void)
{		
		OLED_Init();
		Adc_Init();
		OLED_ShowString(1,1,"ADValue:0000");//×Ö·û´®ÒªË«ÒýºÅ
		OLED_ShowString(2,1,"Volt:0.00");
		while(1)
		{
			OLED_ShowNum(1,9,Get_ADValue(),4);
			OLED_ShowNum(2,6,Get_ADValue()*3.3/4095,4);
			}
		

}
