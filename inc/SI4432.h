#include "SI4432_constants.h"
#include <stdint.h>
#include "SI4432_IO.h"
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
uint8_t SI44_ReadStatus(void);
void SI44_Reset(void);
void SI44_Init(SPI_HandleTypeDef * hspi, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void SI44_SetConfig(si44_config * conf);
void SI44_SetPHConfig(si44_ph_config * conf);
void SI44_SetFrequency(float freq);
void SI44_SetDataRate(uint16_t datarate);
void SI44_SetFrequencyDeviation(uint32_t deviation);
void SI44_SetTXPower(SI44_TX_POWER power);
void SI44_SendPacket(uint8_t * buffer, uint8_t length);
void SI44_ResendPacket(void);
uint8_t SI44_ReadBatteryVoltage(void);
uint8_t SI44_ReadTemperature(void);
void SI44_SetSyncBytes(uint8_t * bytes, uint8_t length);
#endif