#include "stm32f10x.h"                  // Device header
#include "My_I2C.h"
#include "MPU6050_Reg.h"
//这里的地址已经和读写位合起来了
#define MPU6050_ADDRESS 0xD0 

void MPU6050_WriteReg(uint8_t RegAddress,uint8_t Data){
	
		My_I2C_Start();
		MyI2C_SendByte(MPU6050_ADDRESS);//主机找到从机
		MyI2C_ReceiveAck();
		MyI2C_SendByte(RegAddress);//从机具体的寄存器
		MyI2C_ReceiveAck();
		MyI2C_SendByte(Data);//写入的data
		MyI2C_Stop();

}

uint8_t MPU6050_ReadReg(uint8_t RegAddress){

		My_I2C_Start();
		MyI2C_SendByte(MPU6050_ADDRESS);//主机找到从机
		MyI2C_ReceiveAck();
		MyI2C_SendByte(RegAddress);//从机具体的寄存器
		MyI2C_ReceiveAck();
		
		My_I2C_Start();
		MyI2C_SendByte(MPU6050_ADDRESS | 0x01);//把最后的写改成读,guanjianguanjian
		MyI2C_ReceiveAck();
		uint16_t Data = MyI2C_ReceiveByte();
		MyI2C_SendAck(1);//如果只读一个，那你就不回,意思是回个1
		MyI2C_Stop();
		return Data;
}


void MPU6050_Init(void){

		My_I2C_Init();
		MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01);      
    MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);
    MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);
    MPU6050_WriteReg(MPU6050_CONFIG, 0x03);
    MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);
    MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);


}



/*
PWR_MGMT_1    → 电源/时钟
PWR_MGMT_2    → 各轴待机控制
SMPLRT_DIV    → 采样率
CONFIG        → 低通滤波
GYRO_CONFIG   → 陀螺仪量程
ACCEL_CONFIG  → 加速度计量程
WHO_AM_I      → 检查芯片身份
*/


