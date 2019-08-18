#include <stdint.h>
#include "spi.h"
#ifndef SI4432_IO
#define SI4432_IO
void SI44_Read(uint8_t reg, uint8_t * buf, uint8_t length);
void SI44_Write(uint8_t reg, uint8_t * buf, uint8_t length);
void SI44_IO_Init(SPI_HandleTypeDef * hspi, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
#endif