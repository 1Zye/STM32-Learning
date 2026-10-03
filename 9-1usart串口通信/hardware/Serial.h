#ifndef __SERIAL_H
#define __SERIAL_H
#include <stdio.h>

void Serial_Init(void);
void Serial_Sendbyte(uint8_t byte);
void Serial_SendString(char *string);
uint32_t Serial_Pow(uint32_t X, uint32_t Y);
void Serial_SendNumber(uint32_t Num,uint32_t lengh);
int fputc(int ch, FILE *f);


#endif
