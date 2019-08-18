#include "SI4432_IO.h"
#include "spi.h"
SPI_HandleTypeDef * spi_interface;
GPIO_TypeDef * nss_port;
uint16_t nss_pin;

void SI44_Read(uint8_t reg, uint8_t * buf, uint8_t length)
{
    uint8_t b[length + 1];
    HAL_GPIO_WritePin(nss_port, nss_pin, GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive(spi_interface, &reg, b, length+1, 100);
    HAL_GPIO_WritePin(nss_port, nss_pin, GPIO_PIN_SET);
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
    HAL_GPIO_WritePin(nss_port, nss_pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(spi_interface, b, length + 1, 100);
    HAL_GPIO_WritePin(nss_port, nss_pin, GPIO_PIN_SET);
}

void SI44_IO_Init(SPI_HandleTypeDef * hspi, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    spi_interface = hspi;
    nss_port = GPIOx;
    nss_pin = GPIO_Pin;
}