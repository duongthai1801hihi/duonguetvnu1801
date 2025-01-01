#include "gpio.h"


void GPIO_init(void) {
    // Enable clocks for GPIOC, GPIOA, and GPIOB
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; // Enable GPIOC clock
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // Enable GPIOA clock
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; // Enable GPIOB clock

    // Configure PC14 (LED Stop) as output push-pull, max speed 50 MHz
    LED_PORT_STOP->CRH &= ~(unsigned int)(0xF << ((14 - 8) * 4)); // Clear configuration for PC14
    LED_PORT_STOP->CRH |= (0x3 << ((14 - 8) * 4));  // Output mode, 50 MHz

    // Configure PA1 (LED Start) as output push-pull, max speed 50 MHz
    LED_PORT_START->CRL &= ~(unsigned int)(0xF << (1 * 4));        // Clear configuration for PA1
    LED_PORT_START->CRL |= (0x3 << (1 * 4));         // Output mode, 50 MHz

    // Configure PB14 and PB15 as input with pull-up
    GPIOB->CRH &= ~(unsigned int)(0xF << ((14 - 8) * 4)); // Clear configuration for PB14
    GPIOB->CRH |= (0x8 << ((14 - 8) * 4));  // Input mode with pull-up
    GPIOB->CRH &= ~(unsigned int)(0xF << ((15 - 8) * 4)); // Clear configuration for PB15
    GPIOB->CRH |= (unsigned int)(0x8 << ((15 - 8) * 4));  // Input mode with pull-up

    // Enable pull-up for PB14 and PB15
    GPIOB->ODR |= (BUTTON_START | BUTTON_STOP);

    // Initialize LEDs to OFF
    LED_PORT_START->ODR &= ~ (unsigned int) LED_START;
    LED_PORT_STOP ->ODR &= ~ (unsigned int) LED_STOP;

}


uint16_t Read_Pin(uint16_t pin)
{
    return BUTTON_PORT->IDR & pin;  // Read input data register
}

