#include "SI4432_IO.h"
#include "io_fake.h"

fake_io_call * fake_io_call_stack;


int fake_io_ncall;
SPI_HandleTypeDef * spi_interface;

void SI44_Read(uint8_t reg, uint8_t * buf, uint8_t length)
{
    fake_io_call call;
    call.buf = buf;
    call.reg = reg;
    call.length = length;
    call.type = READ;
    fake_io_call_stack[fake_io_ncall++] = call;
    for (int i = 0; i < length; i++)
    {
        buf[i] = i + 1;
    }
}

void SI44_Write(uint8_t reg, uint8_t * buf, uint8_t length)
{
    fake_io_call call;
    call.buf = buf;
    call.reg = reg;
    call.length = length;
    call.type = WRITE;
    fake_io_call_stack[fake_io_ncall++] = call;
}

void SI44_IO_Init(SPI_HandleTypeDef * hspi)
{
    spi_interface = hspi;
}
