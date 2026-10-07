#include "stm32f10x.h"                  // Device header
#include "MySpi.h" 

void W25Q64_WriteEnable(void){
		MySPI_W_SS(0);
		MySPI_SwapByte(0x06);//写使能
		MySPI_W_SS(1);

}

void W25Q64_WaitBusy(void){
		MySpi_Start();
		MySPI_SwapByte(0x05);//读取状态寄存器1
		while((MySPI_SwapByte(0xFF)& 0x01) == 0x01) ;
		
		MySpi_Stop();


}


void W25Q64_Init(void){
	
	MySpi_Init();

}



void W25Q64_ReadID(uint8_t *MID,uint16_t *DID){
		MySpi_Start();
		
		MySPI_SwapByte(0x9F);//查询ID
		*MID = MySPI_SwapByte(0xFF);
		*DID = MySPI_SwapByte(0xFF);
		*DID <<= 8;// *DID = *DID向左移8位
		*DID |= MySPI_SwapByte(0xFF);
		
		MySpi_Stop();
}

void W25Q64_PageProgram(uint32_t Address, uint8_t *DataArray, uint16_t Count){
		uint8_t i;
		W25Q64_WriteEnable();
	
		MySpi_Start();
		MySPI_SwapByte(0x02);
		MySPI_SwapByte(Address>>16);
    MySPI_SwapByte(Address>>8);
		MySPI_SwapByte(Address);
	
		for(i=0;i<Count;i++){
		
			MySPI_SwapByte(DataArray[i]);
		
		}
		MySpi_Stop();
		W25Q64_WaitBusy();
}


uint8_t W25Q64_ReadData(uint32_t Address){

		uint8_t ReceiveData;
	
		MySpi_Start();
		MySPI_SwapByte(0x03);
		MySPI_SwapByte(Address>>16);
    MySPI_SwapByte(Address>>8);
		MySPI_SwapByte(Address);

		ReceiveData = MySPI_SwapByte(0xFF);
		
		MySpi_Stop();
	
		return ReceiveData;

}

