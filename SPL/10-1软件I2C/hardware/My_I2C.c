#include "stm32f10x.h"                  // Device header


//封装函数方便后续使用别的外设
void MyI2C_W_SCL(uint8_t x){
		GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)x);
}

void MyI2C_W_SDA(uint8_t x){
		GPIO_WriteBit(GPIOB,GPIO_Pin_11,(BitAction)x);
}

uint8_t MyI2C_R_SDA(void){
		return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
}





void My_I2C_Init(void){

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;//I2C最好使用开漏输出   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;//sda 11 |  scl 10
	GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_50MHz;
  
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_10 | GPIO_Pin_11);//软件记得设置高电平以充当上拉电阻

}


void My_I2C_Start(void){
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(0);//除了stop其他的基本scl都以低电平结束

}

void MyI2C_SendByte(uint8_t byte){
	uint8_t i;

	for(i=0;i<8;i++){
		MyI2C_W_SDA(byte & (0x80>>i));
		MyI2C_W_SCL(1);//从机读
		MyI2C_W_SCL(0);
	
	}
	

}

uint8_t MyI2C_ReceiveByte(void){
	uint8_t i = 0;
	uint8_t byte = 0x00;
	
	MyI2C_W_SDA(1);//主机释放sda给从机写入
	
	for(i=0;i<8;i++){
		MyI2C_W_SCL(1);
		if(MyI2C_R_SDA()==1){
			byte |= (0x80>>i);
		}
		MyI2C_W_SCL(0);
	
	}
	return byte;

}


void MyI2C_SendAck(uint8_t AckBit){

	MyI2C_W_SDA(AckBit);
	MyI2C_W_SCL(1);
	MyI2C_W_SCL(0);

}

uint8_t MyI2C_ReceiveAck(void){

	uint8_t AckBit;
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	AckBit = MyI2C_R_SDA();
	MyI2C_W_SCL(0);
	return AckBit;


}

void MyI2C_Stop(void){
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(1);


}

