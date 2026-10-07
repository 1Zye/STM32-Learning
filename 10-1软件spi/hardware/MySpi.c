#include "stm32f10x.h"                  // Device header

//以模式0为输入输出

void MySPI_W_SS(uint8_t BitValue){

    GPIO_WriteBit(GPIOA,GPIO_Pin_4,(BitAction)BitValue);
	
}

void MySPI_W_MOSI(uint8_t BitValue){

    GPIO_WriteBit(GPIOA,GPIO_Pin_7,(BitAction)BitValue);
	
}


void MySPI_W_SCK(uint8_t BitValue){

		GPIO_WriteBit(GPIOA,GPIO_Pin_5,(BitAction)BitValue);
	
}

uint8_t MySPI_R_MISO(void){

		return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);

}



void MySpi_Init(void){

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	  
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
		GPIO_Init(GPIOA,&GPIO_InitStructure);	

		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_4;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
		GPIO_Init(GPIOA,&GPIO_InitStructure);	

		GPIO_SetBits(GPIOA,GPIO_Pin_4);
}


void MySpi_Start(void){

		MySPI_W_SS(0);
	
}

void MySpi_Stop(void){

		MySPI_W_SS(1);
	
}


uint8_t MySPI_SwapByte(uint8_t SendByte){

		uint8_t i,ReceiveByte = 0x00;
		
		for(i=0;i<8;i++){
			
				MySPI_W_MOSI(SendByte & (0x80>>i));//逐步左移发送的字节
			
				MySPI_W_SCK(1);//模式0第一个边沿移入数据
				if (MySPI_R_MISO() == 1){
						ReceiveByte |= (0x80 >> i);
				}		
		}
		
		MySPI_W_SCK(0);
		return ReceiveByte;


}


