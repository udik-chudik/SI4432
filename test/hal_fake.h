#include <stdint.h>
#ifndef HAL_FAKE
#define HAL_FAKE

#define SPI_HandleTypeDef int
#define HAL_StatusTypeDef int
#define GPIO_PIN_RESET 0
#define GPIO_PIN_SET 1
#define GPIO_TypeDef int
#define GPIO_PinState int
extern int fake_io_ncall;


typedef struct
{
    SPI_HandleTypeDef * hspi;
    uint8_t * pData;
    uint16_t Size;
    uint32_t Timeout;
} HAL_SPI_TRANSMIT_PARAMS;

typedef struct
{
    SPI_HandleTypeDef * hspi;
    uint8_t * pTxData;
    uint8_t * pRxData;
    uint16_t Size;
    uint32_t Timeout;
} HAL_SPI_TRANSMIT_RECEIVE_PARAMS;

extern HAL_SPI_TRANSMIT_PARAMS * fake_io_hal_transmit_params;
extern HAL_SPI_TRANSMIT_RECEIVE_PARAMS * fake_io_hal_transmit_receive_params;

HAL_StatusTypeDef HAL_SPI_TransmitReceive(SPI_HandleTypeDef * hspi, uint8_t * pTxData, uint8_t * pRxData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_SPI_Transmit (SPI_HandleTypeDef * hspi, uint8_t * pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_GPIO_WritePin( GPIO_TypeDef * port, uint16_t pin,  GPIO_PinState state);
void HAL_Delay(int a);
#endif