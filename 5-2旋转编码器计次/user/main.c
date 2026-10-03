#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "ENCODER.h"
#include "BUZZER.h"


int16_t num;

int main(void)
{		
		OLED_Init();
		Encoder_Init();
		buzzer_Init();
		OLED_ShowString(1,1,"Num:");//×Ö·û´®ÒªË«ÒýºÅ
		
		while(1)
		{
				num += Encoder_Count_get();
				OLED_ShowSignedNum(1,5,num,5);
				
				if(num %5 == 0)
				{
					buzzer_on();
				}
				else 
					buzzer_off();
		}
		

}
