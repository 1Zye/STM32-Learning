#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "W25Q64.h"
#include "OLED.h"


int main(void)
{		
		uint8_t MID;
		uint16_t DID;
		W25Q64_Init();
		OLED_Init();
		W25Q64_ReadID(&MID,&DID);
		OLED_ShowHexNum(1,1,MID,2);
		OLED_ShowHexNum(1,5 ,DID,2);
		while(1)
		{

	}
		
	
}

