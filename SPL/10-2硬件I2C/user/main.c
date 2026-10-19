#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MPU6050.h"
#include "MPU6050_Reg.h"

int main(void)
{		
		OLED_Init();
		MPU6050_Init();
	
		while(1)
		{
		OLED_ShowHexNum(1,1,MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H),2);
		OLED_ShowHexNum(2,1,MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H),2);
		OLED_ShowHexNum(3,1,MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H),2);
		OLED_ShowHexNum(1,1,MPU6050_ReadReg(MPU6050_GYRO_XOUT_H),2);
		OLED_ShowHexNum(2,1,MPU6050_ReadReg(MPU6050_GYRO_YOUT_H),2);
		OLED_ShowHexNum(3,1,MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H),2);
			}
		

}


