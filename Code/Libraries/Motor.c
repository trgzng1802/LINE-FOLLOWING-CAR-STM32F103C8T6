/*
 * Motor.c
 *
 *  Created on: Aug 2, 2022
 *      Author: phang
 */
#include "Motor.h"
extern TIM_HandleTypeDef htim1;

void RightMotor(int speed) {
	  HAL_GPIO_WritePin(GPIOA, ENA_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(GPIOA, IN1_Pin, GPIO_PIN_RESET);
	  __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2, speed);
}

void LeftMotor(int speed) {
	  HAL_GPIO_WritePin(GPIOB, ENB_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(GPIOB, IN4_Pin, GPIO_PIN_RESET);
	  __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1, speed);
}
