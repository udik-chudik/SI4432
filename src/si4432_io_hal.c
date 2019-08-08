#include "SI4432_IO.h"

SPI_HandleTypeDef * spi_interface;

void SI44_Read(uint8_t reg, uint8_t * buf, uint8_t length)
{
    
}

void SI44_Write(uint8_t reg, uint8_t * buf, uint8_t length)
{
    
}

void SI44_IO_Init(SPI_HandleTypeDef * hspi)
{
    spi_interface = hspi;
}