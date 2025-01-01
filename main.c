#include "gpio.h"


int main()
{
	GPIO_init();
	while(1)
	{
	uint16_t status = Read_Pin(BUTTON_START);
	uint16_t status_stop = Read_Pin(BUTTON_STOP);
	if(status == 0)
	{
		LED_PORT_START->ODR |= LED_START;
	}
	else if ( status_stop == 0)
	{
	LED_PORT_STOP -> ODR |= LED_STOP;
	}	
	else 
	{
	LED_PORT_STOP -> ODR &= ~LED_STOP;
	LED_PORT_START -> ODR &= ~LED_START;
	}
}
}