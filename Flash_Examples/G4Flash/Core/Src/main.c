/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
// 1. Define the test struct blueprint
  typedef struct {
      uint32_t device_id;   // 4 bytes
      float    temperature; // 4 bytes
      float    voltage;     // 4 bytes
      char     status[4];   // 4 bytes
  } TestStruct;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define ALIGN_8(size)         (((size) + 7) & ~7)
#define FLASH_START_ADDR   0x807F000
#define FLASH_STORAGE_START_PAGE  126  // Sector 126 of Bank 2
#define FLASH_STORAGE_PAGE_CNT  2    // Erases Sectors 126 and 127
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint32_t address      = FLASH_START_ADDR; // Write tracker
uint32_t read_address = FLASH_START_ADDR; // Read tracker

TestStruct WriteStruct = {
	.device_id = 9999,
	.temperature = 25.6f,
	.voltage = 3.3f,
	.status = "ON!"
};

TestStruct ReadStruct = {0};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void Flash_Erase(void);
void Flash_Write(void *data, uint32_t size_in_bytes);
void Flash_Read(void *destination_struct, uint32_t size_in_bytes);
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
  /* USER CODE BEGIN 2 */
  #ifdef WRITE
  Flash_Erase();
  Flash_Write(&WriteStruct, sizeof(TestStruct));
  #endif

  #ifdef READ
  Flash_Read(&ReadStruct, sizeof(TestStruct));
  #endif
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

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
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void Flash_Erase(void)
{
    HAL_FLASH_Unlock();
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_ALL_ERRORS);

    FLASH_EraseInitTypeDef erase_init;
    uint32_t page_error = 0;
    /*
	As the G4 uses a dual bank architecture that explains the "erase_init.Bank = FLASH_BANK_2"
	and it operates with 2Kb pages, so 512/2 = 256 to see how many pages there are total and that makes 128 pages per bank
	and we erase the last 2 pages hence the "erase_init.Page = 126" and the "NbPges = 2".
	*/
    //important to point to the 2nd Bank of the flash memory
    erase_init.TypeErase = FLASH_TYPEERASE_PAGES;
    erase_init.Banks     = FLASH_BANK_2;
    erase_init.Page      = FLASH_STORAGE_START_PAGE; // 0x807F000 starts at Page 126
    erase_init.NbPages   = FLASH_STORAGE_PAGE_CNT;   // Erase Page 126 and 127

    HAL_FLASHEx_Erase(&erase_init, &page_error);

    // Reset trackers back to the start of the sector
    address = FLASH_START_ADDR;
    read_address = FLASH_START_ADDR;

    HAL_FLASH_Lock();
}

void Flash_Write(void *data, uint32_t size_in_bytes)
{
    if(address % 8 != 0) return; // Ensure 8-byte alignment

    HAL_FLASH_Unlock();
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_ALL_ERRORS);

    uint32_t current_address = address;
    uint8_t *data_ptr = (uint8_t*)data;
    uint32_t bytes_remaining = size_in_bytes;

    while(bytes_remaining > 0)
    {
        // Create a blank 64-bit canvas (erased state is all 1s)
        uint64_t chunk = 0xFFFFFFFFFFFFFFFFULL;

        uint32_t bytes_to_copy = (bytes_remaining >= 8) ? 8 : bytes_remaining;

        // Copy up to 8 bytes of struct data into our 64-bit variable
        memcpy(&chunk, data_ptr, bytes_to_copy);

        // Write the 64-bit double-word to flash
        if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, current_address, chunk) != HAL_OK)
        {
            break;
        }

        current_address += 8;
        data_ptr += bytes_to_copy;
        bytes_remaining -= bytes_to_copy;
    }

    // Push the global write tracker forward by the padded size
    address += ALIGN_8(size_in_bytes);

    HAL_FLASH_Lock();
}

void Flash_Read(void *destination_struct, uint32_t size_in_bytes)
{
    // Copy the raw bytes from silicon flash to the RAM struct
    memcpy(destination_struct, (void *)read_address, size_in_bytes);

    // Push the global read tracker forward to the next available struct
    read_address += ALIGN_8(size_in_bytes);
}
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
#ifdef USE_FULL_ASSERT
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
