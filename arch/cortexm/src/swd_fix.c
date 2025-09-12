#include "gpio.h"

/// force SWD reinit (CubeMX bug fix)
void SWD_Fix(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  // Enable GPIOA clock
  __HAL_RCC_GPIOA_CLK_ENABLE();

  // Configure SWDIO pin (PA13)
  GPIO_InitStruct.Pin = SWDIO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF0_SWJ;
  HAL_GPIO_Init(SWDIO_GPIO_Port, &GPIO_InitStruct);

  // Configure SWCLK pin (PA14)
  GPIO_InitStruct.Pin = SWCLK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF0_SWJ;
  HAL_GPIO_Init(SWDIO_GPIO_Port, &GPIO_InitStruct);
}
