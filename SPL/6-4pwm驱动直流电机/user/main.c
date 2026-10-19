#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "key.h"
#include "Motor.h"


int main(void)
{		
		OLED_Init();
		key_Init();
		Motor_Init();
		OLED_ShowString(1,1,"Motor_Speed");//×Ö·û´®ÒªË«ÒýºÅ
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		
	
		uint16_t speed = 0;
		uint8_t state = 1;
		while(1)
		{
			if(key_getnum() == 1){
				if(state==1){
					
					speed += 10;
					if(speed==40){
						state = 2;
						}
					}
				else if(state==2){
					
					speed -= 10;
					if(speed==0){
						state = 1;
					}
				
					}
			
				}
			Motor_SetSpeed(speed);
			OLED_ShowNum(2,2,speed*2,5);
			}
		

}
/*if(key_getnum() == 1){
				if(state==1){
					GPIO_SetBits(GPIOA,GPIO_Pin_4);
					GPIO_ResetBits(GPIOA,GPIO_Pin_5);
					speed += 10;
					if(speed==50){
						state = 2;
						}
					}
				else if(state==2){
					GPIO_SetBits(GPIOA,GPIO_Pin_5);
					GPIO_ResetBits(GPIOA,GPIO_Pin_4);
					speed -= 10;
					if(speed==0){
						state = 1;
					}
				
					}
			
				}
*/

