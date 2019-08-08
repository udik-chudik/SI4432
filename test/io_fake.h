#include <stdint.h>
#include "spi.h"
#ifndef FAKE_IO
#define FAKE_IO

typedef enum {
    READ,
    WRITE
} FAKE_IO_CALL_TYPE;

typedef struct
{
    FAKE_IO_CALL_TYPE type;
    uint8_t reg;
    uint8_t * buf;
    uint8_t length;
} fake_io_call;

extern fake_io_call * fake_io_call_stack;
extern int fake_io_ncall;
extern SPI_HandleTypeDef * spi_interface;




#endif