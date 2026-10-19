#ifndef __W25Q64_H
#define __W25Q64_H

#include "main.h"
void W25Q64_WriteEnable(void);
HAL_StatusTypeDef W25Q64_ReadID(uint8_t ID[3]);
HAL_StatusTypeDef W25Q64_ReadReg(uint8_t *RegData);
HAL_StatusTypeDef W25Q64_WaitBusy(uint32_t Timeout);



#endif
