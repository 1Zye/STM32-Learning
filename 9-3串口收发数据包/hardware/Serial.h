#ifndef __SERIAL_H
#define __SERIAL_H
#include <stdio.h>
extern uint8_t TXPacket[4];
extern uint8_t RXPacket[100];


void Serial_Init(void);
void Serial_Sendbyte(uint8_t byte);
void Serial_SendString(char *string);
uint32_t Serial_Pow(uint32_t X, uint32_t Y);
void Serial_SendNumber(uint32_t Num,uint32_t lengh);
void Serial_SendArray(uint8_t *Array, uint16_t Length);
int fputc(int ch, FILE *f);

void USART1_IRQHandler(void);


uint16_t GetRxFlag(void);

void SendTXPacket(void);
void USART1_IRQHandler(void);
#endif
