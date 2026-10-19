#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"


 extern uint32_t RxData;




int main(void)
{		
		OLED_Init();
		Serial_Init();

		OLED_ShowString(1,1,"RxData:");
	
		while(1)
		{
			if(GetRxFlag() == 1){
				RxData = GetRxData();
				Serial_Sendbyte(RxData);
				OLED_ShowHexNum(1,8,RxData,4);
			
			}
			
			}
		

}
