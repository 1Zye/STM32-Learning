#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "My_I2C.h"



int main(void)
{		
		OLED_Init();
		My_I2C_Init();
		My_I2C_Start();
		MyI2C_SendByte(0xD0);
		uint8_t Ack = MyI2C_ReceiveAck();
		MyI2C_Stop();
	
		OLED_ShowHexNum(1,1,Ack,2);
	
		while(1)
		{
			
			
			}
		

}


