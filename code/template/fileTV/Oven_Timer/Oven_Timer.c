#include "stm32f4xx.h"
 

void delay_01ms(uint16_t period)
	{

  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);
  	TIM12->PSC = 8399;		// clk = SystemCoreClock / 4 / (PSC+1) *2 = 10KHz
  	TIM12->ARR = period-1;
  	TIM12->CNT = 0;
  	TIM12->EGR = 1;		// update registers;

  	TIM12->SR  = 0;		// clear overflow flag
  	TIM12->CR1 = 1;		// enable Timer6

  	while (!TIM12->SR);
    
  	TIM12->CR1 = 0;		// stop Timer6
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, DISABLE);
	}
	
	