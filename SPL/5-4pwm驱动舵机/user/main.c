#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "key.h"
#include "PWM.h"
#include "Servo.h"


int main(void)
{		
		OLED_Init();
		
		Servo_Init();
		key_Init();
		OLED_ShowString(1, 1, "ANGLE");
	
	
		uint8_t num = 0;//不可以在while里定义，否则每次都会被重置
		uint8_t state = 1;
		while(1)
		{
			if(Key_Getnum() == 1){
				if(state == 1){
					num++;
					if(num==6){
						state = 2;
					}
				}
				else{
					num--;
					if(num==0){
						state = 1;
					}
					
					}
				
				SetAngle(num*30);	
			
			
			}
			
			OLED_ShowNum(2,2,num*30,5);
			
			
			}
		

}


/*for(num=1;num<=6;num++){
					SetAngle(num*30);
					Delay_ms(300);
				}
				
				for(num=6;num>=1;num--){
					SetAngle(num*30);
					Delay_ms(300);
				}
*/
	

/*if(state == 1){
					num++;
					SetAngle(num*30);
					if(num==6){
						state = 2;
					}
					Delay_ms(300);
				}
				else if(state == 2){
						num--;
						SetAngle(num*30);
						if(num==0){
							state = 1;
						}
					Delay_ms(300);
					}
	*/
