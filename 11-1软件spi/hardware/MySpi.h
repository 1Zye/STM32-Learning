#ifndef __MYSPI_H
#define __MYSPI_H

void MySPI_W_SS(uint8_t BitValue);
void MySPI_W_MOSI(uint8_t BitValue);
void MySPI_W_SCK(uint8_t BitValue);
uint8_t MySPI_R_MISO(void);
void MySpi_Init(void);
void MySpi_Start(void);
void MySpi_Stop(void);
uint8_t MySPI_SwapByte(uint8_t SendByte);





#endif
