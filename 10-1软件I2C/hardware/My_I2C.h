#ifndef __MY_I2C_H
#define __MY_I2C_H

void MyI2C_W_SCL(uint8_t x);
void MyI2C_W_SDA(uint8_t x);
uint8_t MyI2C_R_SDA(void);


void My_I2C_Init(void);

void My_I2C_Start(void);

void MyI2C_SendByte(uint8_t byte);

uint8_t MyI2C_ReceiveByte(void);

void MyI2C_SendAck(uint8_t AckBit);

uint8_t MyI2C_ReceiveAck(void);

void MyI2C_Stop(void);

#endif
