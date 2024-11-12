#include "stm32f4xx.h"                 
#include "Oven_Timer.h"
void LED_Config(void);


int main(void)
{

LED_Config();

while(1)
{
GPIO_ResetBits(GPIOC,GPIO_Pin_5);
delay_01ms(1000);
GPIO_SetBits(GPIOC,GPIO_Pin_5);
delay_01ms(1000);
	
GPIO_ResetBits(GPIOB,GPIO_Pin_6);
delay_01ms(1000);
GPIO_SetBits(GPIOB,GPIO_Pin_6);
delay_01ms(1000);
}
}
void LED_Config(void)
	{
		GPIO_InitTypeDef GPIO_InitStructure;

		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		GPIO_Init(GPIOB, &GPIO_InitStructure);

	}
