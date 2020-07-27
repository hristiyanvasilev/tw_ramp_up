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

int run_test_scenario()
{
	toggle_external_led_blink();
	return 0;
}
