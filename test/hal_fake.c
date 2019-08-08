#include "hal_fake.h"


int fake_io_ncall;
HAL_SPI_TRANSMIT_PARAMS * fake_io_hal_transmit_params;
HAL_SPI_TRANSMIT_RECEIVE_PARAMS * fake_io_hal_transmit_receive_params;

HAL_StatusTypeDef HAL_SPI_TransmitReceive(SPI_HandleTypeDef * hspi, uint8_t * pTxData, uint8_t * pRxData, uint16_t Size, uint32_t Timeout)
{
    HAL_SPI_TRANSMIT_RECEIVE_PARAMS p;
    p.hspi = hspi;
    p.pTxData = pTxData;
    p.pRxData = pRxData;
    p.Size = Size;
    p.Timeout = Timeout;
    fake_io_hal_transmit_receive_params[fake_io_ncall++] = p;
    for (int i = 0; i < Size - 1; i++)
    {
        pRxData[i] = i + 1;
    }
    return 1;
}

HAL_StatusTypeDef HAL_SPI_Transmit (SPI_HandleTypeDef * hspi, uint8_t * pData, uint16_t Size, uint32_t Timeout)
{
    HAL_SPI_TRANSMIT_PARAMS p;
    p.hspi = hspi;
    p.pData = pData;
    p.Size = Size;
    p.Timeout = Timeout;
    fake_io_hal_transmit_params[fake_io_ncall++] = p;
    return 1;
}