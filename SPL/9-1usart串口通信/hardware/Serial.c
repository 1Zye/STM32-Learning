#include "stm32f10x.h"                  // Device header
#include <stdio.h>



void Serial_Init(void){


		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
			
	  GPIO_InitTypeDef GPIO_InitStructure;
 	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_9;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		USART_InitTypeDef  USART_InitStruct;
		USART_InitStruct.USART_BaudRate = 9600;
		USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//是否使用硬件流
		USART_InitStruct.USART_Mode = USART_Mode_Tx;
		USART_InitStruct.USART_Parity = USART_Parity_No;//奇校验还是偶校验还是不校验
		USART_InitStruct.USART_StopBits = USART_StopBits_1;
		USART_InitStruct.USART_WordLength = 8;
	
		USART_Init(USART1,&USART_InitStruct);
		
		USART_Cmd(USART1,ENABLE);



}

void Serial_Sendbyte(uint8_t byte){

		USART_SendData(USART1,byte);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
	



}

void Serial_SendString(char *string){

		uint8_t i;
		for(i=0;string[i]!=0;i++){
		
				Serial_Sendbyte(string[i]);
		
		}


}


//本质上是求x的y次方
uint32_t Serial_Pow(uint32_t X, uint32_t Y)
{
    uint32_t Result = 1;

    while (Y--)
    {
        Result *= X;
    }

    return Result;
}

void Serial_SendNumber(uint32_t Num,uint32_t lengh){
		uint8_t i;
		for(i=0;i<lengh;i++){
			
			Serial_Sendbyte((Num/Serial_Pow(10,lengh-i-1))%10 + '0');
		
		
		
		}


}

//printf重新定向，记得开lib和写stdio

int fputc(int ch, FILE *f)
{
    Serial_Sendbyte(ch);
    return ch;
}




