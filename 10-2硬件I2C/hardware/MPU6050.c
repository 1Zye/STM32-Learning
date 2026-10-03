#include "stm32f10x.h"                  // Device header
#include "MPU6050_Reg.h"
//这里的地址已经和读写位合起来了
#define MPU6050_ADDRESS 0xD0 
//记得先输入从机地址，还要输入从机寄存器的地址
void MPU6050_WriteReg(uint8_t RegAddress,uint8_t Data){
	
/*		My_I2C_Start();
		MyI2C_SendByte(MPU6050_ADDRESS);//主机找到从机
		MyI2C_ReceiveAck();
		MyI2C_SendByte(RegAddress);//从机具体的寄存器
		MyI2C_ReceiveAck();
		MyI2C_SendByte(Data);//写入的data
		MyI2C_Stop();
*/
		I2C_GenerateSTART(I2C2,ENABLE);
		while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
		
		I2C_Send7bitAddress(I2C2,MPU6050_ADDRESS,I2C_Direction_Transmitter);
		while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);
	
		I2C_SendData(I2C2,RegAddress);
		while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);

	
		I2C_SendData(I2C2,Data);
		while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);
	
		I2C_GenerateSTOP(I2C2,ENABLE);
	
	
}

uint8_t MPU6050_ReadReg(uint8_t RegAddress){

/*		My_I2C_Start();
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
*/
	
		I2C_GenerateSTART(I2C2,ENABLE);
		while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
		
		I2C_Send7bitAddress(I2C2,MPU6050_ADDRESS,I2C_Direction_Transmitter);
		while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);
	
		I2C_SendData(I2C2,RegAddress);
		while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);
		
		I2C_GenerateSTART(I2C2,ENABLE);
		while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
		
		I2C_Send7bitAddress(I2C2,MPU6050_ADDRESS,I2C_Direction_Receiver);
		while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS);

		I2C_AcknowledgeConfig(I2C2,DISABLE);
		I2C_GenerateSTOP(I2C2,ENABLE);
		while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS);
		I2C_AcknowledgeConfig(I2C2,ENABLE);
//在接收最后一个字节前要提前把标志位置0和产生停止条件
		return I2C_ReceiveData(I2C2);
		
}


void MPU6050_Init(void){

//		My_I2C_Init();
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	  
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;//复用是因为要在gpio口上输出，开漏输出是因为I2C的规定
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
		GPIO_Init(GPIOB,&GPIO_InitStructure);	
	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);
	
		I2C_InitTypeDef I2C_InitStruct;
		I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
		I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
		I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
		I2C_InitStruct.I2C_ClockSpeed = 5000;
		I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;//速度较低的情况下，duty都是1：1
		I2C_InitStruct.I2C_OwnAddress1 = 0x00;
		I2C_Init(I2C2,&I2C_InitStruct);
		
		I2C_Cmd(I2C2,ENABLE);

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


