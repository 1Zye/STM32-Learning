#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"






int main(void)
{		
		OLED_Init();
		Serial_Init();
		
//	Serial_Sendbyte(0x44);
		Serial_SendString("ÄãºÃ\r\n");
		Serial_SendNumber(1221,4);
		Serial_SendString("\r\n");
		printf("haha\r\n");
		while(1)
		{
			
			
			}
		

}
