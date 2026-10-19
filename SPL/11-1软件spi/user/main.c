#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "W25Q64.h"
#include "OLED.h"


uint8_t WriteArray[4] = {0x01,0x02,0x03,0x04};
uint8_t ReadArray[4];


int main(void)
{		
		uint8_t MID;
		uint16_t DID;
		W25Q64_Init();
		OLED_Init();
	
		SectorErase(0x000000);//²Á³ý
		W25Q64_PageProgram(0x000000,WriteArray,4);
		W25Q64_ReadData(0x000000,ReadArray,4);
	
		W25Q64_ReadID(&MID,&DID);
		OLED_ShowHexNum(1,1,MID,2);
		OLED_ShowHexNum(1,5 ,DID,4);
		OLED_ShowHexNum(2,1 ,WriteArray[0],2);
		OLED_ShowHexNum(2,4 ,WriteArray[1],2);
		OLED_ShowHexNum(2,7 ,WriteArray[2],2);
		OLED_ShowHexNum(2,10 ,WriteArray[3],2);

		OLED_ShowHexNum(3,1 ,ReadArray[0],2);
		OLED_ShowHexNum(3,4 ,ReadArray[1],2);
		OLED_ShowHexNum(3,7 ,ReadArray[2],2);
		OLED_ShowHexNum(3,10 ,ReadArray[3],2);
	
		while(1)
		{

	}
		
	
}

