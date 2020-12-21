#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_tim.h"
#include "girouette.h"

#define TIMERGIROUETTE TIM3
//#define TIMERCONTROL TIM7

TIM_HandleTypeDef TIM_TimerIncremental; //Instance TIMER
TIM_HandleTypeDef TIM_TimerInterrupt; //Instance TIMER
TIM_Encoder_InitTypeDef EncoderInstance;//Instance OutputCompare
GPIO_InitTypeDef GPIO_InitStructPA6;
GPIO_InitTypeDef GPIO_InitStructPA7;
GPIO_InitTypeDef GPIO_InitStructPA5;

void girouette_Init(void){
	 __HAL_RCC_TIM3_CLK_ENABLE(); 
//Configurer les pins comme Alternate PP	
 __HAL_RCC_GPIOA_CLK_ENABLE();// Activer l'horloge
	//GPIOA, pin 6 comme CHA
GPIO_InitStructPA6.Pin = GPIO_PIN_6;
GPIO_InitStructPA6.Mode = GPIO_MODE_AF_PP ;//Alternate Push-pull
//GPIO_InitStructPA6.Pull=GPIO_PULLUP;


//GPIOA, pin 7 comme CHB
GPIO_InitStructPA7.Pin = GPIO_PIN_7;
GPIO_InitStructPA7.Mode = GPIO_MODE_AF_PP ;//Alternate Push-pull
//GPIO_InitStructPA7.Pull=GPIO_PULLUP;//Doute

//GPIOA, pin 5 comme INDEX
GPIO_InitStructPA5.Mode = GPIO_MODE_IT_RISING;
GPIO_InitStructPA5.Pull = GPIO_NOPULL;
GPIO_InitStructPA5.Pin = GPIO_PIN_5;
	
	
// Init Ports 
HAL_GPIO_Init(GPIOA, &GPIO_InitStructPA6);	
HAL_GPIO_Init(GPIOA, &GPIO_InitStructPA7);	
HAL_GPIO_Init(GPIOA, &GPIO_InitStructPA5);
// Configurer Interrupt

	//Configurer Timer comme Encoder incremental
	
TIM_TimerIncremental.Instance=TIMERGIROUETTE;
TIM_TimerIncremental.Init.Prescaler= 3;
TIM_TimerIncremental.Init.CounterMode= TIM_COUNTERMODE_UP;
TIM_TimerIncremental.Init.Period= 359; //1439



EncoderInstance.EncoderMode=TIM_ENCODERMODE_TI12;
//CHA
EncoderInstance.IC1Filter=5;
EncoderInstance.IC1Polarity=TIM_ICPOLARITY_RISING;
EncoderInstance.IC1Selection=TIM_ICSELECTION_DIRECTTI;
//CHB
EncoderInstance.IC2Filter=5;
EncoderInstance.IC2Polarity=TIM_ICPOLARITY_RISING;
EncoderInstance.IC2Selection=TIM_ICSELECTION_DIRECTTI;

HAL_TIM_Encoder_Init(&TIM_TimerIncremental,&EncoderInstance);
HAL_TIM_Encoder_Start(&TIM_TimerIncremental,TIM_CHANNEL_ALL);		


/*
 __HAL_RCC_TIM7_CLK_ENABLE();    //Activer l'horloge du TIM2
//Configurer les parametres pour TIM2
TIM_TimerInterrupt.Instance=TIMERCONTROL;
TIM_TimerInterrupt.Init.Prescaler= 3597;
TIM_TimerInterrupt.Init.CounterMode= TIM_COUNTERMODE_UP;
TIM_TimerInterrupt.Init.Period= 10000;//500 ms
TIM_TimerInterrupt.Init.RepetitionCounter=0;
TIM_TimerInterrupt.Init.ClockDivision= TIM_CLOCKDIVISION_DIV1;

HAL_TIM_Base_Init(&TIM_TimerInterrupt);
//HAL_TIM_Base_Start(&TIM2_TimerInstance);


HAL_NVIC_SetPriority(TIM7_IRQn, 4, 0);//PreemptPriority et Subpriority
HAL_NVIC_EnableIRQ(TIM7_IRQn);
HAL_TIM_Base_Start_IT(&TIM_TimerInterrupt);
*/
HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 1);//PreemptPriority et Subpriority
HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

}

int girouette_GetValue(void){
	return TIMERGIROUETTE->CNT;	
}

