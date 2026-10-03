#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "CountSensor.h"




int main(void)
{		
		OLED_Init(); 
		
		OLED_ShowString(1,1,"Count:");//字符串要双引号
		
		CountSensor_Init();
	
		OLED_Clear();//想清零就使用
		
		while(1)
		{
			OLED_ShowNum(1,7,CountSensor_get(),5);
			
		}
		

}
