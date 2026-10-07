#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "key.h"

uint8_t Keynum;

int main(void)
{		
		LED_Init();//LED初始化
		key_Init();//按键初始化
		
		while(1)
		{
			Keynum = key_getnum();
			if(Keynum == 1){
				LED1_turn();
			
			}
			else if(Keynum == 2){
				LED2_turn();
			
			}
		}

}
