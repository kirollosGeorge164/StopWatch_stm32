/*
 * Matrix_Keypad.h
 *
 *  Created on: Feb 17, 2024
 *      Author: Kiro
 */

#ifndef DEVICE_DRIVERS_MATRIX_KEYPAD_MATRIX_KEYPAD_H_
#define DEVICE_DRIVERS_MATRIX_KEYPAD_MATRIX_KEYPAD_H_

#include "stm32f1xx_hal.h"
#include <stdint.h>

/// @struct keypad_str
/// @brief
/// this struct is used to configure the keypad
typedef struct keypad_str {
	///
	/// attribute : keypad rows
	uint8_t Rows;
	///
	/// attribute : keypad columns
	uint8_t Columns;

	///
	/// user data
	/// holds the status of the buttons
	uint32_t Button_Status;

	///
	/// peripheral configuration
	///
	GPIO_TypeDef *Row_Port;
	uint8_t Row_Start_Pin;
	GPIO_TypeDef *Column_Port;
	uint8_t Column_Start_Pin;

	///
	/// masking
	///
	uint32_t Input_mask ;
	uint32_t Output_mask ;

} Keypad_Matrix_t;

//User Functions
/// @fn void Keypad_Matrix_init(Keypad_Matrix_t*)
/// @brief
///
/// @param kp
void Keypad_Matrix_init(Keypad_Matrix_t *kp);
/// @fn void Keypad_Matrix_refresh(Keypad_Matrix_t*)
/// @brief
///
/// @param kp
void Keypad_Matrix_refresh(Keypad_Matrix_t *kp);

/// @fn uint8_t Keypad_Matrix_ReadKey(Keypad_Matrix_t*, uint8_t)
/// @brief
///
/// @param kp
/// @param key
/// @return
uint8_t Keypad_Matrix_ReadKey(Keypad_Matrix_t *kp, uint8_t key);


#endif /* DEVICE_DRIVERS_MATRIX_KEYPAD_MATRIX_KEYPAD_H_ */
