#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "key.h"


 extern uint32_t RxData;




int main(void)
{		
		OLED_Init();
		key_Init();
		Serial_Init();
		
		OLED_ShowString(1,1,"TxData:");
		OLED_ShowString(3,1,"RxData:");
	
		TXPacket[0] = 0x01;
		TXPacket[1] = 0x02;
		TXPacket[2] = 0x03;
		TXPacket[3] = 0x04;
	
		while(1)
		{
			
			if(key_getnum() == 1){
				TXPacket[0] ++;
				TXPacket[1] ++;
				TXPacket[2] ++;
				TXPacket[3] ++;
				SendTXPacket();
			
			}
			
			if(GetRxFlag() == 1){
				OLED_ShowHexNum(4,1,RXPacket[0],2);
				OLED_ShowHexNum(4,4,RXPacket[1],2);
				OLED_ShowHexNum(4,7,RXPacket[2],2);
				OLED_ShowHexNum(4,10,RXPacket[3],2);
			}
			
			
			
			
			}
			
			}
		


