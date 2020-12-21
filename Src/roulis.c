#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_adc.h"
#include "roulis.h"


ADC_HandleTypeDef ADC_Instance; //Instance ADC1
ADC_ChannelConfTypeDef ADC_Channel; //Channel ADC1
TIM_HandleTypeDef TIM2_TimerInstance; //Instance TIM2
GPIO_InitTypeDef GPIO_InitStruct;


void roulis_Init(void){
		 __HAL_RCC_GPIOC_CLK_ENABLE();
GPIO_InitStruct.Pin = GPIO_PIN_0;
GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;//ANALOG INPUT
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	
	 __ADC1_CLK_ENABLE();
RCC_PeriphCLKInitTypeDef PeriphClkInit;
PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;

ADC_Instance.Instance = ADC1;
ADC_Instance.Init.NbrOfDiscConversion = 1;
ADC_Instance.Init.DiscontinuousConvMode = ENABLE;
ADC_Instance.Init.ScanConvMode = ADC_SCAN_DISABLE;
ADC_Channel.Channel = ADC_CHANNEL_10;
ADC_Channel.SamplingTime = ADC_SAMPLETIME_7CYCLES_5;

HAL_ADC_Init(&ADC_Instance);
HAL_ADC_ConfigChannel(&ADC_Instance,&ADC_Channel);
HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

HAL_NVIC_SetPriority(ADC1_IRQn, 0, 0);
HAL_NVIC_EnableIRQ(ADC1_IRQn);
	
__TIM2_CLK_ENABLE();   //Activer l'horloge du TIM2
//Configurer les parametres pour TIM2
TIM2_TimerInstance.Instance=TIM2;
TIM2_TimerInstance.Init.Prescaler= 35997;
TIM2_TimerInstance.Init.CounterMode= TIM_COUNTERMODE_UP;
TIM2_TimerInstance.Init.Period= 1000; //10ms
TIM2_TimerInstance.Init.RepetitionCounter=0;
TIM2_TimerInstance.Init.ClockDivision= TIM_CLOCKDIVISION_DIV1;
HAL_TIM_Base_Init(&TIM2_TimerInstance);

HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);//PreemptPriority et Subpriority
HAL_NVIC_EnableIRQ(TIM2_IRQn);



HAL_TIM_Base_Start_IT(&TIM2_TimerInstance);
}

int roulis_GetValue(void){
	return HAL_ADC_GetValue(&ADC_Instance);	
}

