/*
 * tests.c
 *
 *  Created on: Jul 27, 2020
 *      Author: Hrist
 */

#include "main.h"

//brief - toggle blinking external led connected to "PC3" by pressing "USER B1".
//        toggle occurs on button release.
static void toggle_external_led_blink(void)
{
	  uint8_t is_down = 0;
	  uint8_t should_blink = 0;
	  while (1)
	  {
		if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET)
		{
			is_down = 1;
		}

		if (is_down && HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_SET)
		{
			should_blink = !should_blink;
			is_down = 0;
		}

		if(should_blink)
		{
			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_3);
			HAL_Delay(200);
		}
	  }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{
	//handle just the interrupt for USER btn1
	if(GPIO_PIN_13 == GPIO_PIN)
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}

//brief - interrupt handler for USER btn1 is pressed.
void EXTI4_15_IRQHandler(void)
{
	//clear the interrupt and toggle the pin
	//should be cleared only when if we not utilizing the HAL
	//__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_13);

	//internally the interrupt flag is being cleared.
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
}

//brief - configure user button 1 to generate interrupt
//		  start blinking when the button is clicked
static void user_bt1_interrupt()
{
	GPIO_InitTypeDef GPIO_InitStruct;

	//remove the existing auto-generated configuration for the pin
	HAL_GPIO_DeInit(GPIOC, GPIO_PIN_13);

	//re-init the pin with the new configuration
	GPIO_InitStruct.Pin = GPIO_PIN_13 | GPIO_PIN_12;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	//enable the interrupt line for the pin
	HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

	while(1)
	{
		//do nothing
	}
}

int run_test_scenario()
{
	//toggle_external_led_blink();
	//user_bt1_interrupt();
	return 0;
}
