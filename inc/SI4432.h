#include "SI4432_constants.h"
#include <stdint.h>
#ifndef SI4432
#define SI4432
typedef struct
{
    SI44_PH_PATH path;
    uint8_t preambule_length;
    SI44_PH_SYNC_LENGTH sync;
    SI44_PH_HEADER_LENGTH header;
    SI44_PH_CRC crc;
    SI44_PH_CRC_TYPE crc_type;
} si44_ph_config;

typedef struct
{
    uint8_t encoding_options;
    SI44_MODULATION_SOURCE modulation_source;
    SI44_MODULATION_TYPE modulation_type;
} si44_config;
#endif