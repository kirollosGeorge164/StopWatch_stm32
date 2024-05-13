/*
 * StopWatch.c
 *
 *  Created on: May 7, 2024
 *      Author: Kiro
 */

#include "../Inc/StopWatch.h"

void StopWatch_loop() {
	Keypad_Matrix_t keypad = { .Rows = 4, .Row_Port = GPIOB,
			.Row_Start_Pin = 12, .Columns = 4, .Column_Port = GPIOB,
			.Column_Start_Pin = 3 };

	Alcd_t Lcd = { .Data_GPIO = GPIOA, .Data_GPIO_Start_Pin = 0, .RS_GPIO =
	GPIOA, .RS_GPIO_Pin = GPIO_PIN_4, .EN_GPIO = GPIOA, .EN_GPIO_Pin =
	GPIO_PIN_5 };

	__HAL_RCC_GPIOB_CLK_ENABLE()
	;
	Keypad_Matrix_init(&keypad);

	Alcd_Init(&Lcd, 2, 16);

	uint8_t HH = 0, MM = 0, SS = 0, mS = 0;
	char text_1[] = "Push * to play";
	char text_2[] = "0 Stop - # Reset";
	char text_3[] = "* play - # Reset";
	uint8_t len_1 = strlen(text_1);
	uint8_t len_2 = strlen(text_2);
	uint8_t len_3 = strlen(text_3);
	char str[16];

	while (1) {
		Keypad_Matrix_refresh(&keypad);

		if (!(Keypad_Matrix_ReadKey(&keypad, 12)
				|| Keypad_Matrix_ReadKey(&keypad, 13)
				|| Keypad_Matrix_ReadKey(&keypad, 14))) {
			Alcd_PutAt_n(&Lcd, 0, 0, text_1, len_1);
			HAL_Delay(500);
		}
		//start button
		else if (Keypad_Matrix_ReadKey(&keypad, 12)) {
			Alcd_Clear(&Lcd);
			Alcd_PutAt_n(&Lcd, 1, 0, text_2, len_2);
			uint8_t str_len = sprintf(str, "%02d:%02d:%02d.%02d", HH, MM, SS,
					mS);
			for (int i = 0; i < 24; i++) {
				for (int j = 0; j < 60; j++) {
					for (int k = 0; k < 60; k++) {
						for (int l = 0; l < 100; l++) {
							str_len = sprintf(str, "%02d:%02d:%02d.%02d", i, j,
									k, l);
							Alcd_PutAt_n(&Lcd, 0, 0, str, str_len);
							Keypad_Matrix_refresh(&keypad);
							// reset button
							if (Keypad_Matrix_ReadKey(&keypad, 14)) {
								i = 0;
								j = 0;
								k = 0;
								l = 0;
								str_len = sprintf(str, "%02d:%02d:%02d.%02d", i,
										j, k, l);
								Alcd_PutAt_n(&Lcd, 0, 0, str, str_len);
								Alcd_PutAt_n(&Lcd, 1, 0, text_1, len_1);
								while (!Keypad_Matrix_ReadKey(&keypad, 12)) {
									Keypad_Matrix_refresh(&keypad);
								}
								Alcd_PutAt_n(&Lcd, 1, 0, text_2, len_2);
							}

//							HAL_Delay(1);
							// stop button

							if (Keypad_Matrix_ReadKey(&keypad, 13)) {
								Keypad_Matrix_refresh(&keypad);
								Alcd_Clear(&Lcd);
								Alcd_PutAt_n(&Lcd, 0, 0, str, str_len);
								Alcd_PutAt_n(&Lcd, 1, 0, text_3, len_3);2
								while (!Keypad_Matrix_ReadKey(&keypad, 12)
										&& !Keypad_Matrix_ReadKey(&keypad, 14)) {
									Keypad_Matrix_refresh(&keypad);
									if (Keypad_Matrix_ReadKey(&keypad, 12))
										Alcd_PutAt_n(&Lcd, 1, 0, text_2, len_2);
									else
										Alcd_PutAt_n(&Lcd, 1, 0, text_1, len_1);
								}
//								if (Keypad_Matrix_ReadKey(&keypad, 14)) {
//									i = 0;
//									j = 0;
//									k = 0;
//									l = 0;
//									Alcd_Clear(&Lcd);
//									Alcd_PutAt_n(&Lcd, 0, 0, str, str_len);
//									Alcd_PutAt_n(&Lcd, 1, 0, text_1, len_1);
							}
						}

					}
				}
			}
		}
	}

}

