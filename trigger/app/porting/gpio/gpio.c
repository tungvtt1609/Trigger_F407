/*
 * gpio.c
 *
 *  Created on: Jul 15, 2023
 *      Author: ADMIN
 */

#include "gpio.h"

int32_t pin_isr = GPIO_PIN_0;

static gpio_pin_t s_gpio_pin[PIN_MAX] =
{
		{PIN_0, GPIO_PIN_0},
		{PIN_1, GPIO_PIN_1},
		{PIN_2, GPIO_PIN_2},
		{PIN_3, GPIO_PIN_3},
		{PIN_4, GPIO_PIN_4},
		{PIN_5, GPIO_PIN_5},
		{PIN_6, GPIO_PIN_6},
		{PIN_7, GPIO_PIN_7},
		{PIN_8, GPIO_PIN_8},
		{PIN_9, GPIO_PIN_9},
		{PIN_10, GPIO_PIN_10},
		{PIN_11, GPIO_PIN_11},
		{PIN_12, GPIO_PIN_12},
		{PIN_13, GPIO_PIN_13},
		{PIN_14, GPIO_PIN_14},
		{PIN_15, GPIO_PIN_15}
};

static gpio_port_t s_gpio_port[PORT_MAX] =
{
		{PORT_A, GPIOA},
		{PORT_B, GPIOB},
		{PORT_C, GPIOC},
		{PORT_D, GPIOD},
		{PORT_E, GPIOE},
};

void GPIO_SetPinOut(gpio_port_id_e port_id, gpio_pin_id_e pin_id)
{
	static GPIO_InitTypeDef  GPIO_InitStruct;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

	GPIO_InitStruct.Pin = s_gpio_pin[pin_id].pin;
	HAL_GPIO_Init(s_gpio_port[port_id].port, &GPIO_InitStruct);
	return;
}

void GPIO_SetPinIn(gpio_port_id_e port_id, gpio_pin_id_e pin_id, uint32_t PULLUPDOWN)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull  = PULLUPDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

	GPIO_InitStruct.Pin = s_gpio_pin[pin_id].pin;
	HAL_GPIO_Init(s_gpio_port[port_id].port, &GPIO_InitStruct);
	return;
}

void GPIO_WritePin(gpio_port_id_e port_id, gpio_pin_id_e pin_id, gpio_level_e level)
{
	HAL_GPIO_WritePin(s_gpio_port[port_id].port, s_gpio_pin[pin_id].pin, level);
}

void GPIO_TogglePin(gpio_port_id_e port_id, gpio_pin_id_e pin_id)
{
	HAL_GPIO_TogglePin(s_gpio_port[port_id].port, s_gpio_pin[pin_id].pin);
}

gpio_level_e GPIO_ReadPin(gpio_port_id_e port_id, gpio_pin_id_e pin_id)
{
	return HAL_GPIO_ReadPin(s_gpio_port[port_id].port, s_gpio_pin[pin_id].pin);
}

void EXTI15_10_IRQHandler_Config(gpio_port_id_e port_id, gpio_pin_id_e pin_id, uint32_t mode, uint32_t PULLUPDOWN)
{
  GPIO_InitTypeDef   GPIO_InitStructure;

  switch (port_id) {
	case PORT_A:
		__HAL_RCC_GPIOA_CLK_ENABLE();
		break;

	case PORT_B:
		__HAL_RCC_GPIOB_CLK_ENABLE();
		break;

	case PORT_C:
		__HAL_RCC_GPIOC_CLK_ENABLE();
		break;

	case PORT_D:
		__HAL_RCC_GPIOD_CLK_ENABLE();
		break;

	case PORT_E:
		__HAL_RCC_GPIOE_CLK_ENABLE();
		break;

	default:
		break;
  }

  GPIO_InitStructure.Mode = mode;
  GPIO_InitStructure.Pull = PULLUPDOWN;
  GPIO_InitStructure.Pin = s_gpio_pin[pin_id].pin;
  pin_isr = s_gpio_pin[pin_id].pin;
  HAL_GPIO_Init(s_gpio_port[port_id].port, &GPIO_InitStructure);

  /* Enable and set lines 10 to 15 Interrupt to the lowest priority */
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

  return;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

}
