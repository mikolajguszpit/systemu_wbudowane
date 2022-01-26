/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdlib.h"
#include<stdio.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct{
	uint8_t x;
	uint8_t y;
	uint8_t left_coordinate;
	uint8_t right_coordinate;
	uint8_t x_size;
	uint8_t y_size;
}Block;
typedef struct {
	int8_t x_pos;
	int8_t y_pos;
	int8_t x_speed;
	int8_t y_speed;
} Ball;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define M 12
#define N 16
#define LCD_HEIGHT 240
#define LCD_WIDTH 320
#define SQUARE_SIZE LCD_HEIGHT/M
#define CIRCLE_SIZE 10
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
// An array representing a game board. For now: 0 = empty space, 1 = platform, 2 = brick, 3=ball.
int8_t game_board[M][N] = {{0}};
Block platform = {.x = M-1, .x_size = 1, .y = (N/2)-2, .y_size = 5, .left_coordinate=0, .right_coordinate=0};
Ball ball = {.x_pos = M-3, .y_pos = 8, .x_speed = -1, .y_speed = -1};
uint8_t bricks_counter = 0;
int points = 0;

// A variable storing game state.
uint8_t game_state = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
// void MX_USB_HOST_Process(void);

/* USER CODE BEGIN PFP */
uint8_t ADC1_Init(void);
uint32_t GetSeedValue(void);
void GeneratePlatform(void);
void DrawPlatform(void);
void GenerateBricks(void);
void DrawBricks(void);
void MoveLeft(void);
void MoveRight(void);
void GameOver(void);
void CounterFunction(void);
void DrawBall(void);
void GenerateBall(void);
void BallMovement(void);
void EreaseBlocks(void);
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
  JOYState_TypeDef JoyState = JOY_NONE;
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
  
  /* Configure the Key push-button in GPIO Mode */

  /*## Initialize the LCD #################################################*/
  if (BSP_LCD_Init() != LCD_OK)
  {
	  Error_Handler();
  }

  if (BSP_JOY_Init(JOY_MODE_GPIO) != IO_OK)
  {
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
    BSP_LCD_SetTextColor(LCD_COLOR_RED);
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()- 95, (uint8_t *)"ERROR", CENTER_MODE);
    BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()- 80, (uint8_t *)"Joystick cannot be initialized", CENTER_MODE);
    Error_Handler();
  }

  if (ADC1_Init() != HAL_OK)
  {
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
    BSP_LCD_SetTextColor(LCD_COLOR_RED);
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()- 95, (uint8_t *)"ERROR", CENTER_MODE);
    BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()- 80, (uint8_t *)"ADC1 cannot be initialized", CENTER_MODE);
    Error_Handler();
  }

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	BSP_LCD_Clear(LCD_COLOR_WHITE);

	GeneratePlatform();
	DrawPlatform();
	GenerateBricks();
	DrawBricks();
	GenerateBall();
	DrawBall();

	while (game_state == 0)
	{
	  /* Get the Joystick State */
	  JoyState = BSP_JOY_GetState();
	  BallMovement();
	  switch(JoyState)
	  {
	  case JOY_LEFT:
		  HAL_Delay(200);
		  MoveLeft();
	      break;
	  case JOY_RIGHT:
		  HAL_Delay(200);
		  MoveRight();
	      break;
	  default:
	      break;
	  }

	}

	GameOver();
    /* USER CODE END WHILE */
    // MX_USB_HOST_Process();

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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure. */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV5;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.Prediv1Source = RCC_PREDIV1_SOURCE_PLL2;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  RCC_OscInitStruct.PLL2.PLL2State = RCC_PLL2_ON;
  RCC_OscInitStruct.PLL2.PLL2MUL = RCC_PLL2_MUL8;
  RCC_OscInitStruct.PLL2.HSEPrediv2Value = RCC_HSE_PREDIV2_DIV5;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks */
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

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_ADC
                              |RCC_PERIPHCLK_USB;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV3;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }

  // HAL_RCC_MCOConfig(RCC_MCO, RCC_MCO1SOURCE_HSE, RCC_MCODIV_1);
  /** Configure the Systick interrupt time */
  __HAL_RCC_PLLI2S_ENABLE();
}

/* USER CODE BEGIN 4 */
uint8_t ADC1_Init(void)
{
  uint8_t ret = HAL_OK;
  ADC_HandleTypeDef hadc1 = {0};
  ADC_ChannelConfTypeDef sConfig = {0};

  /** Common configuration */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  ret = HAL_ADC_Init(&hadc1);
  if (ret != HAL_OK)
  {
    return ret;
  }

  /** Configure regular channel group */
  sConfig.Channel = ADC_CHANNEL_7;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
  ret = HAL_ADC_ConfigChannel(&hadc1, &sConfig);

  return ret;
}

void GeneratePlatform(void)
{


	for(int i=0; i < platform.y_size; i++){
		game_board[platform.x][platform.y+i] = 1;
	}
	platform.left_coordinate=platform.y;
	platform.right_coordinate=platform.y+platform.y_size;

}

void DrawPlatform(void)
{
	int i = 0;
	int j = 0;


	for (i= 0; i < M; i++)
		{
			for (j = 0; j < N; j++)
			{
				if (game_board[i][j] == 1)
				{
					BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
					BSP_LCD_FillRect(j*SQUARE_SIZE, i*SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE);
				}
			}
		}
	return;
}

void GenerateBall(void)
{
	game_board[ball.x_pos][ball.y_pos] = 3;
}


void DrawBall(void)
{
	int i = 0;
	int j = 0;

	for (i= 0; i < M; i++)
		{
			for (j = 0; j < N; j++)
			{
				if (game_board[i][j] == 3)
				{
					BSP_LCD_SetTextColor(LCD_COLOR_RED);
					BSP_LCD_FillCircle(j*SQUARE_SIZE+10, i*SQUARE_SIZE+10, CIRCLE_SIZE);
				}
			}
		}
	return;
}


void MoveLeft(void)
{

	uint8_t head_y = platform.y;
	uint8_t next_col = head_y-1;
	uint8_t tail_y = platform.y+platform.y_size-1;

	if (head_y == (0))
	{
		return;
	}

	else
	{

		game_board[M-1][tail_y] = 0;

		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_FillRect( (tail_y)*SQUARE_SIZE, (M-1)*SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE);

		platform.y = next_col;

		game_board[M-1][next_col] = 1;

		DrawPlatform();
	}
}

void MoveRight(void)
{

	uint8_t head_y = platform.y+platform.y_size-1;
	uint8_t next_col = head_y+1;
	uint8_t tail_y = platform.y;

	if (head_y == (N-1))
	{
		return;
	}

	else
	{

		game_board[M-1][tail_y] = 0;

		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_FillRect( (tail_y)*SQUARE_SIZE, (M-1)*SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE);

		platform.y += 1;

		game_board[M-1][next_col] = 1;

		DrawPlatform();
	}
}

void BallMovement(void){
	uint8_t curr_x = ball.x_pos;
	uint8_t curr_y = ball.y_pos;

	if (bricks_counter == 0)
	{
		game_state = 2;
		GameOver();
	}

	if (ball.x_pos+ball.x_speed == M)
	{
		game_state = 1;
		GameOver();
	}
	if (game_board[ball.x_pos+ball.x_speed][ball.y_pos+ball.y_speed] == 1)
	{
		ball.x_speed *= -1;
	}

	if (game_board[curr_x+1][curr_y] == 0 && game_board[curr_x-1][curr_y] == 0 && game_board[curr_x][curr_y+1] == 0 && game_board[curr_x][curr_y-1] == 0 && game_board[ball.x_pos+ball.x_speed][ball.y_pos+ball.y_speed] == 2)
	{
		game_board[ball.x_pos+ball.x_speed][ball.y_pos+ball.y_speed] = 0;
		points++;
		bricks_counter--;
		EreaseBlocks();
		ball.x_speed *= -1;
		ball.y_speed *= -1;

	}
	if (game_board[curr_x-1][curr_y] == 2 || game_board[curr_x+1][curr_y] == 2)
	{
		ball.x_speed *= -1;
		if (game_board[curr_x-1][curr_y] == 2)
		{
			game_board[curr_x-1][curr_y] = 0;
			points++;
			bricks_counter--;
			EreaseBlocks();
		}
		if (game_board[curr_x+1][curr_y] == 2)
		{
			game_board[curr_x+1][curr_y] = 0;
			points++;
			bricks_counter--;
			EreaseBlocks();
		}
	}
	if ((ball.x_pos+ball.x_speed) == -1)
	{
		ball.x_speed *= -1;
		if (game_board[curr_x+1][curr_y] == 0 && game_board[curr_x][curr_y-1] == 0 && game_board[curr_x][curr_y+1] == 0 && game_board[ball.x_pos+ball.x_speed][ball.y_pos+ball.y_speed] == 2)
		{
			game_board[ball.x_pos+ball.x_speed][ball.y_pos+ball.y_speed] = 0;
			points++;
			bricks_counter--;
			EreaseBlocks();
			ball.x_speed *= -1;
			ball.y_speed *= -1;
		}
		if ((ball.x_pos+ball.x_speed) == -1)
		{
			ball.x_speed *= -1;
		}

	}

	if ((ball.y_pos+ball.y_speed) == -1)
			{
				ball.y_speed *= -1;
				if (game_board[curr_x+1][curr_y] == 0 && game_board[curr_x-1][curr_y] == 0 && game_board[curr_x][curr_y+1] == 0 && game_board[ball.x_pos+ball.x_speed][ball.y_pos+ball.y_speed] == 2)
				{
					game_board[ball.x_pos+ball.x_speed][ball.y_pos+ball.y_speed] = 0;
					points++;
					bricks_counter--;
					EreaseBlocks();
					ball.x_speed *= -1;
					ball.y_speed *= -1;
				}
				if ((ball.y_pos+ball.y_speed) == -1)
					{
					ball.y_speed *= -1;
					}

			}
	if ((ball.y_pos+ball.y_speed) == N)
				{
					ball.y_speed *= -1;
					if (game_board[curr_x+1][curr_y] == 0 && game_board[curr_x-1][curr_y] == 0 && game_board[curr_x][curr_y-1] == 0 && game_board[ball.x_pos+ball.x_speed][ball.y_pos+ball.y_speed] == 2)
					{
						game_board[ball.x_pos+ball.x_speed][ball.y_pos+ball.y_speed] = 0;
						points++;
						bricks_counter--;
						EreaseBlocks();
						ball.x_speed *= -1;
						ball.y_speed *= -1;
					}
					if ((ball.y_pos+ball.y_speed) == N)
					{
					ball.y_speed *= -1;
					}

				}
	if (game_board[curr_x][curr_y+1] == 2 || game_board[curr_x][curr_y-1] == 2)
	{
		ball.y_speed *= -1;
		if (game_board[curr_x][curr_y+1] == 2)
		{
			game_board[curr_x][curr_y+1] = 0;
			points++;
			bricks_counter--;
			EreaseBlocks();
		}
		if (game_board[curr_x][curr_y-1] == 2)
		{
			game_board[curr_x][curr_y-1] = 0;
			points++;
			bricks_counter--;
			EreaseBlocks();
		}
	}

	ball.x_pos += ball.x_speed;
	ball.y_pos += ball.y_speed;

	game_board[curr_x][curr_y] = 0;
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillCircle(curr_y*SQUARE_SIZE+10, curr_x*SQUARE_SIZE+10, CIRCLE_SIZE);

	game_board[ball.x_pos][ball.y_pos] = 3;
	DrawBall();
	HAL_Delay(100);
	return;
}

void GenerateBricks(void)
{
	uint8_t i = 0, j = 0;

	for (i= 0; i < M/4; i++)
	{
		for (j = 0; j < N; j++)
		{
			if (game_board[i][j] == 0)
			{
				game_board[i][j] = 2;
				bricks_counter++;
			}
		}
	}

	for (j = 4; j < 11; j++)
	{
		if (game_board[3][j] == 0)
		{
			game_board[3][j] = 2;
			bricks_counter++;
		}
	}
	return;
}
void DrawBricks(void)
{
	uint8_t i = 0, j = 0;

	for (i = 0; i < M; i++)
		for (j = 0; j < N; j++)
		{
			if (game_board[i][j] == 2)
			{
				BSP_LCD_SetTextColor(LCD_COLOR_ORANGE);
				BSP_LCD_FillRect(j*SQUARE_SIZE, i*SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE);
			}
		}
}

void EreaseBlocks(void)
{
	uint8_t i = 0, j = 0;

		for (i = 0; i < M; i++)
			for (j = 0; j < N; j++)
			{
				if (game_board[i][j] == 0)
				{
					BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
					BSP_LCD_FillRect(j*SQUARE_SIZE, i*SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE);
				}
			}
}

void GameOver(void)
{
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
	BSP_LCD_SetFont(&Font12);
	char result1[10];
	char result2[10];
	sprintf(result1, "%d", points/10);
	sprintf(result2, "%d", points%10);


	if(game_state == 1){
		BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()- 95, (uint8_t *)"GAME OVER", CENTER_MODE);
		BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()- 80, (uint8_t *)"You lost", CENTER_MODE);
		BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()- 65, (uint8_t *)"Your score:", CENTER_MODE);
		BSP_LCD_DisplayChar(BSP_LCD_GetXSize()/2-7, BSP_LCD_GetYSize()- 50, *result1);
		BSP_LCD_DisplayChar(BSP_LCD_GetXSize()/2, BSP_LCD_GetYSize()- 50, *result2);
		BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()- 35, (uint8_t *)"Press \"Reset\" to start new game", CENTER_MODE);
		while(1);
	}

	if(game_state == 2){
		BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()- 95, (uint8_t *)"Congratulations!!!", CENTER_MODE);
		BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()- 80, (uint8_t *)"You won", CENTER_MODE);
		BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()- 65, (uint8_t *)"Your score:", CENTER_MODE);
		BSP_LCD_DisplayChar(BSP_LCD_GetXSize()/2-7, BSP_LCD_GetYSize()- 50, *result1);
		BSP_LCD_DisplayChar(BSP_LCD_GetXSize()/2, BSP_LCD_GetYSize()- 50, *result2);
		BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()- 65, (uint8_t *)"Press \"Reset\" to start new game", CENTER_MODE);
		while(1);
	}
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  BSP_LED_On(LED_RED);
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
