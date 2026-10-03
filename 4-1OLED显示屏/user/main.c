#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"




int main(void)
{		
		OLED_Init();
		OLED_ShowString(1,1,"helloworld");//×Ö·û´®ÒªË«ÒýºÅ
		OLED_ShowChar(2,1,'A');
		while(1)
		{
			
			
			}
		

}
