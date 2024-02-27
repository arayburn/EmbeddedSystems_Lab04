/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
char userinput1;
char userinput2;
char button;
int test;
char errormessage1[] = "wrong code use r g b or o ";
char errormessage2[] = "wrong code use 0 1 or 2 ";
int x = 25; // hard code length of message
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
void TransmitCharacter (char input) {
	// int transmit = USART3->ISR |= (1<<7);
	uint32_t TXEmask = (1<<7);
  while ((USART3->ISR & TXEmask) == 0) { // checking if flag is up by looking at the TXE bit
	//while ((transmit) == 0) {
	}
	USART3->TDR = input;
}

void CharReader(char string[x]){
	int i;
	for (i = 0;i<x;i++){
		if (string[i] == 0){ // null 
			break;
		}
		else {
			TransmitCharacter(string[i]);
		}
	}
}
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  HAL_Init();
  SystemClock_Config();

	RCC->AHBENR |= RCC_AHBENR_GPIOBEN; 	
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

	// HAL_RCC_GetHCLKFreq();
	
	// moder 01 for general purpose
	GPIOC->MODER |= ((1<<14)|(1<<12)|(1<<18)|(1<<16)); // normal function mode 
	GPIOC->MODER &=~  ((1<<15)|(1<<13)|(1<<19)|(1<<17)); // normal function mode 
	
	GPIOB->MODER  |= ((1<<21)|(1<<23));
	GPIOB->MODER  &=~ ((1<<20)|(1<<22));
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */

  /* Configure the system clock */

	// Pins on board for this are PB10(TX) and PB 11(RX), other pins work but those are close to ground 
	// *note for user remember to use putty, also use alternate function mode 4 (0100)
	GPIOB->AFR[1] &=~ ((1<<8)|(1<<9)|(1<<11)|(1<<12)|(1<<13)|(1<<15)); // alternate function on pb 10 and 11
	GPIOB->AFR[1] |= ((1<<10)|(1<<14));
	// set frequency to 115200
	USART3->BRR = 69; // actual is 69.44 (8000000/115200), actual baud rate now is 115942
	// Usart control register enable 
	USART3->CR1 |= ((1<<2)|(1<<3)); // enable reciever and transmitter 

	GPIOC->ODR |= (1<<6);
	GPIOC->ODR |= (1<<7);
	GPIOC->ODR |= (1<<8);
	GPIOC->ODR |= (1<<9);
	// ***** do this last 
	USART3->CR1 |= (1<<0); // enable USART	
  /* Infinite loop */
  while (1)
  { 
		// char input = 'a';
		// TransmitCharacter(input);
		// HAL_Delay(500);
		userinput1 = 0;		// reset user input
		userinput2 = 0;
		while(test == 0) { // if the user pushes a button read the input to check for which led to turn on 
			test = USART3->ISR &= (1<<5);
			HAL_Delay(10);
		}
		test = 0;
		userinput1 = USART3->RDR; // read user input
	
		while(test == 0) { // if the user pushes a button read the input to check for which led to turn on 
			test = USART3->ISR &= (1<<5);
			HAL_Delay(10);
		}
		test = 0;
		userinput2 = USART3->RDR; // read user input
		
		
		//button = CharReader(userinput);
		if(userinput1== 'r'){
			if(userinput2 == '0'){ // turn on
				GPIOC->ODR |= (1<<6);
			}
			if(userinput2 == '1'){
				GPIOC->ODR &=~ (1<<6); // turn off 
			}
			if(userinput2 == '2'){
				GPIOC->ODR ^= (1<<6);	// toggle
			}
			else{
			CharReader(errormessage2);
		// return wrong button pushed to reader 
		}		
		}
		else if(userinput1== 'b'){
			if(userinput2 == '0'){ // turn on
				GPIOC->ODR |= (1<<7);
			}
			if(userinput2 == '1'){
				GPIOC->ODR &=~ (1<<7); // turn off 
			}
			if(userinput2 == '2'){
				GPIOC->ODR ^= (1<<7);	// toggle
			}
			else{
			CharReader(errormessage2);
		// return wrong button pushed to reader 
		}		
		}
		else if(userinput1== 'o'){
			if(userinput2 == '0'){ // turn on
				GPIOC->ODR |= (1<<8);
			}
			if(userinput2 == '1'){
				GPIOC->ODR &=~ (1<<8); // turn off 
			}
			if(userinput2 == '2'){
				GPIOC->ODR ^= (1<<8);	// toggle
			}
			else{
			CharReader(errormessage2);
		// return wrong button pushed to reader 
		}		
		}
		else if(userinput1== 'g'){
			if(userinput2 == '0'){ // turn on
				GPIOC->ODR |= (1<<9);
			}
			if(userinput2 == '1'){
				GPIOC->ODR &=~ (1<<9); // turn off 
			}
			if(userinput2 == '2'){
				GPIOC->ODR ^= (1<<9);	// toggle
			}
			else{
			CharReader(errormessage2);
		// return wrong button pushed to reader 
		}		
		}
		else{
			CharReader(errormessage1);
		// return wrong button pushed to reader 
		}		
		userinput1 =0;
		userinput2 =0;
		HAL_Delay(10); // small delay because baud rate is faster than board 
	}
		
  
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
