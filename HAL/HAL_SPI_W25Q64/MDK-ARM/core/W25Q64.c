#include "W25Q64.h"
#include "main.h"
#include "spi.h"

#define W25Q64_CS_LOW() \
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)

#define W25Q64_CS_HIGH() \
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET)

void W25Q64_WriteEnable(void)
{
    uint8_t Cmd = 0x06;

    W25Q64_CS_LOW();

    HAL_SPI_Transmit(&hspi1, &Cmd, 1, 100);

    W25Q64_CS_HIGH();
}

HAL_StatusTypeDef W25Q64_ReadID(uint8_t ID[3])
{
		uint8_t command = 0x9F;
		uint8_t Dummy[3] = {0xFF,0xFF,0xFF};
		HAL_StatusTypeDef status;
	
		W25Q64_CS_LOW();//选中从机
	
		status = 	HAL_SPI_Transmit(&hspi1,&command,1,100);//发送操作符并接收发送结果
		if(status == HAL_OK){
				status = HAL_SPI_TransmitReceive(&hspi1,Dummy,ID,3,100);//read id
		

		
		}
	
		W25Q64_CS_HIGH();
			
		return status;//返回这个函数的整体运行结果
		




}

HAL_StatusTypeDef W25Q64_ReadReg(uint8_t *RegData)
{
		
		HAL_StatusTypeDef status;
		uint8_t command = 0x05;
		uint8_t Dummy = 0xFF;
	
		W25Q64_CS_LOW();//选中从机

		
		HAL_SPI_Transmit(&hspi1,&command,1,100);
		if(status == HAL_OK){
				status = HAL_SPI_TransmitReceive(&hspi1,&Dummy,RegData,1,100);
		
		}

		W25Q64_CS_HIGH();
		return status;


}

HAL_StatusTypeDef W25Q64_WaitBusy(uint32_t Timeout)
{			
		uint32_t StartTime = HAL_GetTick();//获取当前时间
		HAL_StatusTypeDef status;
		uint8_t RegData = 0;

	while(1){
	
		status = W25Q64_ReadReg(&RegData);
		
		if(status != HAL_OK){
				return status;
		
		}
		
		if((RegData&0x01) == 0x00){
				return HAL_OK;
		
		
		}
		if((uint32_t)(HAL_GetTick() - StartTime) >= 1000){
				return HAL_TIMEOUT;
		
		}
	}

}





