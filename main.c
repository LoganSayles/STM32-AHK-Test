/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_hid.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
extern USBD_HandleTypeDef hUsbDeviceFS;

typedef struct{
	uint8_t MODIFIER;
	uint8_t RESERVED;
	uint8_t KEYCODE1;
	uint8_t KEYCODE2;
	uint8_t KEYCODE3;
	uint8_t KEYCODE4;
	uint8_t KEYCODE5;
	uint8_t KEYCODE6;
} keyboardReportDes;

keyboardReportDes HIDKeyBoard={0,0,0,0,0,0,0,0};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
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

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */
HAL_Delay(2000);
int counter = 0;

void SendHIDreport(uint8_t modifier, uint8_t keycode1, uint8_t keycode2, uint8_t keycode3, uint8_t keycode4, uint8_t keycode5, uint8_t keycode6, uint32_t delay)
{
    HIDKeyBoard.MODIFIER = modifier;
    HIDKeyBoard.KEYCODE1 = keycode1;
    HIDKeyBoard.KEYCODE2 = keycode2;
    HIDKeyBoard.KEYCODE3 = keycode3;
    HIDKeyBoard.KEYCODE4 = keycode4;
    HIDKeyBoard.KEYCODE5 = keycode5;
    HIDKeyBoard.KEYCODE6 = keycode6;
    USBD_HID_SendReport(&hUsbDeviceFS, &HIDKeyBoard, sizeof(HIDKeyBoard));
    HAL_Delay(delay);
    HIDKeyBoard.MODIFIER = 0x00;
    HIDKeyBoard.KEYCODE1 = 0x00;
    HIDKeyBoard.KEYCODE2 = 0x00;
    HIDKeyBoard.KEYCODE3 = 0x00;
    HIDKeyBoard.KEYCODE4 = 0x00;
    HIDKeyBoard.KEYCODE5 = 0x00;
    HIDKeyBoard.KEYCODE6 = 0x00;
    USBD_HID_SendReport(&hUsbDeviceFS, &HIDKeyBoard, sizeof(HIDKeyBoard));
    HAL_Delay(delay);
}
  /* USER CODE END 2 */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  if (counter == 0)
	  {
		  SendHIDreport(0x01, 0x29, 0x00, 0x00, 0x00, 0x00, 0x00, 100); // CTRL + ESCAPE
	      SendHIDreport(0x00, 0x06, 0x10, 0x07, 0x00, 0x00, 0x00, 100); // 'cmd'
	      SendHIDreport(0x00, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 300); // ENTER
	      SendHIDreport(0x00, 0x06, 0x07, 0x2C, 0x07, 0x08, 0x16, 50); // 'cd Des'
	      SendHIDreport(0x00, 0x0E, 0x17, 0x12, 0x13, 0x00, 0x00, 50); // 'ktop'
	      SendHIDreport(0x00, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 50); // ENTER
	      SendHIDreport(0x00, 0x08, 0x06, 0x0B, 0x12, 0x2C, 0x00, 100); // 'echo' + SPACE
	      SendHIDreport(0x00, 0x16, 0x12, 0x10, 0x08, 0x2C, 0x00, 50); // '"some' + SPACE
	      SendHIDreport(0x00, 0x08, 0x19, 0x0C, 0x0F, 0x2C, 0x16, 50); // 'evil' + SPACE + 's'
	      SendHIDreport(0x00, 0x17, 0x18, 0x09, 0x09, 0x2C, 0x00, 50); // 'tuff"' + SPACE
	      SendHIDreport(0x02, 0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 50); // >
	      SendHIDreport(0x00, 0x2C, 0x08, 0x19, 0x0C, 0x0F, 0x37, 50); // SPACE + 'evil.'
	      SendHIDreport(0x00, 0x17, 0x1B, 0x17, 0x00, 0x00, 0x00, 50); // 'txt'
	      SendHIDreport(0x00, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 50); // ENTER
	      SendHIDreport(0x04, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x00, 50); // ALT + F4
		  counter +=1;
	  }
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
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
