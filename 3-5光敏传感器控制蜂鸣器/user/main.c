#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "buzzer.h"
#include "key.h"
#include "LightSensor.h"


uint8_t Keynum;

int main(void)
{		
		LightSensor_Init();
		buzzer_Init();
		while(1)
			{
				if(LightSensor_get() == 1)//光敏传感器暗时高电平输出灯不亮
					buzzer_ON();
				else//亮时低电平输出灯亮
					buzzer_OFF();
				
			}

}

//按钮控制蜂鸣器，但要记得在上面添加“key.h”
//uint8_t keynum = key_getnum();
			
//			if(keynum == 3)
//				buzzer_ON();
			
//			else
//			buzzer_OFF();





