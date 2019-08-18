#include "unity.h"
#include "SI4432_IO.h"
#include "hal_fake.h"

int fake_io_ncall;
HAL_SPI_TRANSMIT_PARAMS * fake_io_hal_transmit_params;
HAL_SPI_TRANSMIT_RECEIVE_PARAMS * fake_io_hal_transmit_receive_params;

void setUp(void)
{
    fake_io_ncall = 0;
    HAL_SPI_TRANSMIT_PARAMS buf[10];
    fake_io_hal_transmit_params =  buf;

    HAL_SPI_TRANSMIT_RECEIVE_PARAMS buf2[10];
    fake_io_hal_transmit_receive_params =  buf2;
}

void test_SI44_Write(void)
{
    uint8_t buf[1];
    buf[0] = 37;
    SI44_Write(0x11, buf, 1);
    
    TEST_ASSERT_EQUAL(37, fake_io_hal_transmit_params[0].pData[1]);
    TEST_ASSERT_EQUAL(0x11 | 0b10000000, fake_io_hal_transmit_params[0].pData[0]);
    TEST_ASSERT_EQUAL(1, fake_io_ncall);
    TEST_ASSERT_EQUAL(2, fake_io_hal_transmit_params[0].Size);
}

void test_SI44_Read(void)
{
    uint8_t buf[10];
    SI44_Read(0x7a, buf, 10);

    TEST_ASSERT_EQUAL(0x7a, fake_io_hal_transmit_receive_params[0].pTxData[0]);
    TEST_ASSERT_EQUAL(1, fake_io_ncall);
    TEST_ASSERT_EQUAL(3 + 1, buf[2]);
    TEST_ASSERT_EQUAL(11, fake_io_hal_transmit_receive_params[0].Size);
}