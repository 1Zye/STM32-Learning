#include "stm32f10x.h"                  // Device header
#include "PWM.h"


void Servo_Init(void){

	  PWM_Init();



}


//psc = 720 - 1    period = 2000 - 1, so T = 20ms
//f(cnt)=72MHz / 720 = 100000, so 计一个数的时间是1 / 100000 = 10us
//ccr = 50 对应 0°  ccr = 200 对应 180°

void SetAngle(uint16_t i){
	
	PWM_SetCompare1(i*150/180+50);





}


