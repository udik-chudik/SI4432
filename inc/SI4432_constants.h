#ifndef SI4432_CONSTANTS
#define SI4432_CONSTANTS
/*
    Packet handler config values. Default values are:
    * Packet length includes in packet
    * Preambule < 128 bytes
    * MSB first
*/
typedef enum {
    SI44_PH_PATH_OFF     = 0b00000000,
    SI44_PH_PATH_RX_ONLY = 0b10000000,
    SI44_PH_PATH_TX_ONLY = 0b00001000,
    SI44_PH_PATH_TXRX = SI44_PH_PATH_RX_ONLY | SI44_PH_PATH_TX_ONLY
} SI44_PH_PATH;

typedef enum {
    SI44_PH_CRC_OFF = 0b00000000,
    SI44_PH_CRC_ON  = 0b00000100,
    SI44_PH_CRC_DATA_ONLY = SI44_PH_CRC_ON | 0b00100000
} SI44_PH_CRC;

typedef enum {
    SI44_PH_CRC_TYPE_CITT       = 0b00000000,
    SI44_PH_CRC_TYPE_IBM16      = 0b00000001,
    SI44_PH_CRC_TYPE_IEC16      = 0b00000010,
    SI44_PH_CRC_TYPE_BIACHEVA   = 0b00000011
} SI44_PH_CRC_TYPE;

typedef enum {
    SI44_PH_HEADER_OFF  = 0b00000000,
    SI44_PH_HEADER_1    = 0b00010000,
    SI44_PH_HEADER_2    = 0b00100000,
    SI44_PH_HEADER_3    = 0b00110000,
    SI44_PH_HEADER_4    = 0b01000000
} SI44_PH_HEADER_LENGTH;

typedef enum {
    SI44_PH_SYNC_1    = 0b00000000,
    SI44_PH_SYNC_2    = 0b00000010,
    SI44_PH_SYNC_3    = 0b00000100,
    SI44_PH_SYNC_4    = 0b00000110
} SI44_PH_SYNC_LENGTH;

/*
    Output power in Si4432 corresponds to +20dBm
*/

typedef enum {
    SI44_TX_POWER_11dBm   = 0b00000000,
    SI44_TX_POWER_14dBm   = 0b00000001,
    SI44_TX_POWER_17dBm   = 0b00000010,
    SI44_TX_POWER_20dBm   = 0b00000011,

} SI44_TX_POWER;

/*
    Tx settings. Default values:
    * data rate < 30 kbps
    * No TX data clock (because we use FIFO mode)
    * Frequency deviation < 160 kHz
*/

#define SI44_DATA_WHITENING_ENABLED     0b00000001
#define SI44_DATA_MANCHESTER_ENABLED    0b00000010
#define SI44_DATA_MANCHESTER_INVERSION  0b00000100
#define SI44_DATA_MANCHESTER_POLARITY   0b00001000

typedef enum {
    SI44_MODULATION_SOURCE_GPIO    = 0b00000000,
    SI44_MODULATION_SOURCE_SDI     = 0b00010000,
    SI44_MODULATION_SOURCE_FIFO    = 0b00100000,
    SI44_MODULATION_SOURCE_PN9     = 0b00110000
} SI44_MODULATION_SOURCE;

typedef enum {
    SI44_MODULATION_TYPE_UNMODULATED    = 0b00000000,
    SI44_MODULATION_TYPE_OOK            = 0b00000001,
    SI44_MODULATION_TYPE_FSK            = 0b00000010,
    SI44_MODULATION_TYPE_GFSK           = 0b00000011
} SI44_MODULATION_TYPE;


/* Registers */

#define SI44_REG_STATUS 0x02
#define SI44_REG_CTRL1  0x07
#define SI44_REG_CTRL2  0x08

#define SI44_REG_CONF1  0x70
#define SI44_REG_CONF2  0x71

#define SI44_REG_DATA_ACCESS_CONTROL    0x30
#define SI44_REG_HEADER_CONTROL         0x33
#define SI44_REG_PREAMBULE_LENGTH       0x34

#define SI44_REG_FREQ_BAND_SELECT       0x75
#define SI44_REG_FREQ_MSB               0x76
#define SI44_REG_FREQ_LSB               0x77

#define SI44_REG_DATARATE_MSB           0x6e
#define SI44_REG_DATARATE_LSB           0x6f

#define SI44_REG_DEVIATION              0x72
#define SI44_REG_TX_POWER               0x6d

#define SI44_REG_FIFO_ACCESS            0x7f

#define SI44_REG_BATTERY_VOLTAGE        0x1b
#define SI44_REG_ADC_CONFIG             0x0f
#define SI44_REG_ADC_VALUE              0x11
#define SI44_REG_TEMP_CONFIG            0x12

#define SI44_REG_SYNC3                  0x36

#endif