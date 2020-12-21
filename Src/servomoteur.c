#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_tim.h"
#include "servomoteur.h"


#define TIMERSERVO TIM4
TIM_HandleTypeDef TIM_TimerInstance; //Instance TIMER
TIM_OC_InitTypeDef OC_Instance;//Instance OutputCompare

void servomoteur_Init(void){
	__TIM4_CLK_ENABLE();   //Activer l'horloge du TIM3
	
TIM_TimerInstance.Instance=TIMERSERVO;
TIM_TimerInstance.Init.Prescaler= 399;
TIM_TimerInstance.Init.CounterMode= TIM_COUNTERMODE_UP;
TIM_TimerInstance.Init.Period= 3600; // Periode 20 ms
TIM_TimerInstance.Init.RepetitionCounter=0;
TIM_TimerInstance.Init.ClockDivision= TIM_CLOCKDIVISION_DIV1;

OC_Instance.OCMode=TIM_OCMODE_PWM1;
OC_Instance.Pulse=360; //Plage de 1ms a 2ms (180 a 360)
OC_Instance.OCPolarity=TIM_OCPOLARITY_HIGH;
OC_Instance.OCFastMode=TIM_OCFAST_DISABLE;
OC_Instance.OCIdleState=TIM_OCIDLESTATE_SET;
OC_Instance.OCNIdleState=TIM_OCNIDLESTATE_SET;	
	
	
HAL_TIM_PWM_Init(&TIM_TimerInstance);
HAL_TIM_PWM_ConfigChannel(&TIM_TimerInstance,&OC_Instance,TIM_CHANNEL_3);
HAL_TIM_PWM_Start(&TIM_TimerInstance, TIM_CHANNEL_3);

GPIO_InitTypeDef GPIO_InitStruct;
 __HAL_RCC_GPIOB_CLK_ENABLE();
GPIO_InitStruct.Pin = GPIO_PIN_8;
GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;//Alternate Push-pull
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}
// angle degrés
void servomoteur_SetPos(int angle){//Changer position du servo (relation Duty cycle/Position)	 
		HAL_TIM_PWM_Stop(&TIM_TimerInstance,TIM_CHANNEL_3); 
	  OC_Instance.Pulse=(angle*2)+180;//Normaliser l'angle
		HAL_TIM_PWM_ConfigChannel(&TIM_TimerInstance, &OC_Instance, TIM_CHANNEL_3);
		HAL_TIM_PWM_Start(&TIM_TimerInstance, TIM_CHANNEL_3); 
}
uint32_t servomoteur_GetPos(void){
	return (OC_Instance.Pulse-180);
}