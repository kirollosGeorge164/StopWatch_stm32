/*
 * Matrix_Keypad.c
 *
 *  Created on: Feb 17, 2024
 *      Author: Kiro
 */
#include "Matrix_Keypad.h"

static void HardwareInterface_Initialize(Keypad_Matrix_t *kp) {

	GPIO_InitTypeDef GP = { .Mode = GPIO_MODE_OUTPUT_PP, .Speed = GPIO_SPEED_LOW
	//pp:push pull
			};
	///
	/// Output Pins Initialization
	///
	uint32_t Pins = 0;
	for (int x = 0; x < kp->Rows; x++) {
		Pins |= (1 << (kp->Row_Start_Pin + x));
		//Pins = Pins | (1 << (Start_Pin) + x);
	}
	kp->Output_mask = Pins;
	GP.Pin = Pins;
	HAL_GPIO_Init(kp->Row_Port, &GP);
	///
	///Input Pins Initialization
	///
	GP.Mode = GPIO_MODE_INPUT;
	GP.Pull = GPIO_PULLDOWN;
	Pins = 0;
	for (int x = 0; x < kp->Columns; x++) {
		Pins |= (1 << (kp->Column_Start_Pin + x));
		//Pins = Pins | (1 << (Start_Pin) + x);
	}
	GP.Pin = Pins;
	kp->Input_mask = Pins;
	HAL_GPIO_Init(kp->Column_Port, &GP);

}

static void Generate_Delay(uint16_t Delay) {
	HAL_Delay(Delay);
}

static uint8_t HardwareInterface_GetInputs(Keypad_Matrix_t *kp) {
	uint32_t temp = kp->Column_Port->IDR & kp->Input_mask;
	temp >>= kp->Column_Start_Pin;
	return (uint8_t) temp;
}

static void HardwareInterface_SetOutputs(Keypad_Matrix_t *kp,
		uint8_t OutputStatus) {
	kp->Row_Port->ODR &= ~kp->Output_mask;
	kp->Row_Port->ODR |= ((uint32_t) OutputStatus << kp->Row_Start_Pin);
}

void Keypad_Matrix_init(Keypad_Matrix_t *kp) {
	HardwareInterface_Initialize(kp);
	HardwareInterface_SetOutputs(kp, 0);
}

void Keypad_Matrix_refresh(Keypad_Matrix_t *kp) {
	kp->Button_Status = 0;
	uint8_t scan = 0b1;
	for (uint8_t i = 0; i < kp->Rows; i++) {
		HardwareInterface_SetOutputs(kp, scan);
		Generate_Delay(1);
		kp->Button_Status |= HardwareInterface_GetInputs(kp)
				<< (i * kp->Columns);
		scan <<= 1;
	}
}

uint8_t Keypad_Matrix_ReadKey(Keypad_Matrix_t *kp, uint8_t key) {
	if (kp->Button_Status & (1 << key)) {
		return 1;
	} else
		return 0;
}

