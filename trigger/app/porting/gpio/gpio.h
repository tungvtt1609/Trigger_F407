/*
 * gpio.h
 *
 *  Created on: Jul 15, 2023
 *      Author: ADMIN
 */

#ifndef PORTING_GPIO_GPIO_H_
#define PORTING_GPIO_GPIO_H_

#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include <stdint.h>

typedef enum gpio_pin_id_e {
	PIN_0 = 0,
	PIN_1,
	PIN_2,
	PIN_3,
	PIN_4,
	PIN_5,
	PIN_6,
	PIN_7,
	PIN_8,
	PIN_9,
	PIN_10,
	PIN_11,
	PIN_12,
	PIN_13,
	PIN_14,
	PIN_15,
	PIN_MAX
}gpio_pin_id_e;

typedef enum gpio_port_id_e {
	PORT_A = 0,
	PORT_B,
	PORT_C,
	PORT_D,
	PORT_E,
	PORT_MAX
}gpio_port_id_e;

typedef enum gpio_level_e {
	GPIO_LOW = 0,
	GPIO_HIGH
}gpio_level_e;

typedef struct gpio_pin_t {
	gpio_pin_id_e pin_id;
	uint32_t pin;
}gpio_pin_t;

typedef struct gpio_port_t
{
	gpio_port_id_e port_id;
	GPIO_TypeDef *port;
}gpio_port_t;

extern uint32_t pin_isr;

void GPIO_SetPinOut(gpio_port_id_e port_id, gpio_pin_id_e pin_id);
void GPIO_SetPinIn(gpio_port_id_e port_id, gpio_pin_id_e pin_id, uint32_t PULLUPDOWN);
void GPIO_WritePin(gpio_port_id_e port_id, gpio_pin_id_e pin_id, gpio_level_e level);
void GPIO_TogglePin(gpio_port_id_e port_id, gpio_pin_id_e pin_id);
gpio_level_e GPIO_ReadPin(gpio_port_id_e port_id, gpio_pin_id_e pin_id);
void EXTI15_10_IRQHandler_Config(gpio_port_id_e port_id, gpio_pin_id_e pin_id, uint32_t mode, uint32_t PULLUPDOWN);

#endif /* PORTING_GPIO_GPIO_H_ */
