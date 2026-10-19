#include "stm32f10x.h"                  // Device header
#include "MyDMA.h"

uint16_t DataA[] = {0,0};
void Adc_Init(void){

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
		RCC_ADCCLKConfig(RCC_PCLK2_Div6);//六分频
		
		
	
	
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//模拟输入
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		
	
		ADC_InitTypeDef  ADC_InitStruct;
		ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
		ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;//对齐方式
		ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
		ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
		ADC_InitStruct.ADC_NbrOfChannel = 2;//转换的总通道数
		ADC_InitStruct.ADC_ScanConvMode = ENABLE;

		ADC_Init(ADC1,&ADC_InitStruct);
		
		

		ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
		ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_55Cycles5);




		
		ADC_Cmd(ADC1,ENABLE);
		ADC_DMACmd(ADC1,ENABLE);
		MyDMA_Init((uint32_t)&ADC1->DR,(uint32_t)DataA);//(uint32_t)&ADC1->DR这个样子才是地址
		
		ADC_SoftwareStartConvCmd(ADC1,ENABLE);

}




// 复位校准
//		ADC_ResetCalibration(ADC1);
	//	while (ADC_GetResetCalibrationStatus(ADC1) == SET);

// 开始校准
//		ADC_StartCalibration(ADC1);
	//	while (ADC_GetCalibrationStatus(ADC1) == SET);







