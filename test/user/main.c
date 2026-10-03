#include "stm32f10x.h"                  // Device header
#include "led.h"
#include "light_sensor.h"


int main(void)
{
	 led_Init();
	 lightsensor_Init();
	
	while(1)
	{
		if(lightsensor_get() == 1)
			led_on();
		
		else 
			led_off();
	}


}	



