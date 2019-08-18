#include "SI4432_IO.h"
#include "spi.h"
SPI_HandleTypeDef * spi_interface;

void SI44_Read(uint8_t reg, uint8_t * buf, uint8_t length)
{
    uint8_t b[length + 1];
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive(spi_interface, &reg, b, length+1, 100);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
    for (int i = 0; i < length; i++)
    {
        buf[i] = b[i+1];
    }
    
}

void SI44_Write(uint8_t reg, uint8_t * buf, uint8_t length)
{
    uint8_t b[length + 1];
    b[0] = reg | 0b10000000;
    for (int i = 0; i < length; i++)
    {
        b[i+1] = buf[i];
    }
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
    HAL_SPI_Transmit(spi_interface, b, length + 1, 100);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
}

void SI44_IO_Init(SPI_HandleTypeDef * hspi)
{
    spi_interface = hspi;
}