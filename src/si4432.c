#include "SI4432.h"
#include "SI4432_private.h"
#include "SI4432_IO.h"
#include <stdio.h>
uint8_t SI44_CalcFrequencyDeviationRegister(uint32_t deviation)
{
    return (uint8_t) (deviation/625);
}

void SI44_CalcFrequencyCarierRegisters(float freq, uint8_t * regs)
{
    uint32_t fb = 0;
    uint8_t hbsel = 0b01000000;

    uint32_t F = freq*1000;

    if (F < 480000)
    {
        fb = (F - 240000);
    } else {
        fb = (F - 480000)/2;
        hbsel |= 0b00100000;
    }
    regs[0] = hbsel | ((uint8_t)(fb/10000) & 0b00011111);
    uint16_t fc = 0;
    //printf("\n\n%i %i\n\n", F, (fb/10000)*10000);
    fc = (uint16_t) ((F/(1 + (F > 480000 ? 1 : 0) ) - 240000 - (fb/10000)*10000 )*100000/15625);
    //printf("\n\n%f\n\n", (freq/((1.0 + (freq > 480.0 ? 1.0 : 0) )) - 240.0 - fb*10 ));
    //printf("\n\n%i\n\n", fc);
    regs[1] = (uint8_t) ((fc >> 8) & 0xff);
    regs[2] = (uint8_t) (fc & 0xff);
}

void SI44_CalcDataRateRegisters(uint16_t baudrate, uint8_t * regs)
{
    //uint64_t val = 1;// = 2097152;
    //val <<= 21;
    uint64_t val =  (uint64_t)baudrate << 21;
    val /= 1000000;
    //printf("\n\n%i\n\n", val);
    //val = baudrate*2.097152;
    regs[0] = (uint8_t) ((val >> 8) & 0xff);
    regs[1] = (uint8_t) (val & 0xff);
}

void SI44_CalcPHRegisters(si44_ph_config config, uint8_t * regs)
{
    regs[0] = config.path | config.crc | config.crc_type;
    regs[1] = config.header | config.sync;
    regs[2] = config.preambule_length;
}

void SI44_CalcConfigRegisters(si44_config config, uint8_t * regs)
{
    regs[0] = 0b00100000 | config.encoding_options;
    regs[1] = config.modulation_source | config.modulation_type;
}

uint8_t SI44_ReadStatus(void)
{
    uint8_t buf[1];
    SI44_Read(SI44_REG_STATUS, buf, 1);
    return buf[0];
}

void SI44_Reset(void)
{
    uint8_t reset = SI44_OPERATION_MODE_DEFAULT | 0b10000000;
    SI44_Write(SI44_REG_CTRL1, &reset, 1);
}

void SI44_Init(SPI_HandleTypeDef * hspi, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    SI44_IO_Init(hspi, GPIOx, GPIO_Pin);
    SI44_Reset();
}

void SI44_SetConfig(si44_config * conf)
{
    uint8_t buf[2];
    SI44_CalcConfigRegisters(*conf, buf);
    SI44_Write(SI44_REG_CONF1, &buf[0], 1);
    SI44_Write(SI44_REG_CONF2, &buf[1], 1);
    //Load capacitance
    uint8_t a = 0xa5;
    SI44_Write(0x09, &a, 1);
    //GPIO0 & GPIO1 - TX/RX switch
    a = 0x12;
    SI44_Write(0x0b, &a, 1);
    a = 0x15;
    SI44_Write(0x0c, &a, 1);
    
}

void SI44_SetPHConfig(si44_ph_config * conf)
{
    uint8_t buf[3];
    SI44_CalcPHRegisters(*conf, buf);
    SI44_Write(SI44_REG_DATA_ACCESS_CONTROL, &buf[0], 1);
    SI44_Write(SI44_REG_HEADER_CONTROL, &buf[1], 1);
    SI44_Write(SI44_REG_PREAMBULE_LENGTH, &buf[2], 1);
}

void SI44_SetFrequency(float freq)
{
    uint8_t buf[3];
    SI44_CalcFrequencyCarierRegisters(freq, buf);
    SI44_Write(SI44_REG_FREQ_BAND_SELECT, &buf[0], 1);
    SI44_Write(SI44_REG_FREQ_MSB, &buf[1], 1);
    SI44_Write(SI44_REG_FREQ_LSB, &buf[2], 1);
}

void SI44_SetDataRate(uint16_t datarate)
{
    uint8_t buf[2];
    SI44_CalcDataRateRegisters(datarate, buf);
    SI44_Write(SI44_REG_DATARATE_MSB, &buf[0], 1);
    SI44_Write(SI44_REG_DATARATE_LSB, &buf[1], 1);
}

void SI44_SetFrequencyDeviation(uint32_t deviation)
{
    uint8_t d = SI44_CalcFrequencyDeviationRegister(deviation);
    SI44_Write(SI44_REG_DEVIATION, &d, 1);
}

void SI44_SetTXPower(SI44_TX_POWER power)
{
    uint8_t p = power;
    SI44_Write(SI44_REG_TX_POWER, &p, 1);
}

void SI44_SendPacket(uint8_t * buf, uint8_t length)
{
    uint8_t b;
    SI44_ClearTXFIFO();
    SI44_Read(0x03, &b, 1);
    SI44_Read(0x04, &b, 1);
    SI44_Write(0x3e, &length, 1);
    SI44_Write(SI44_REG_FIFO_ACCESS, buf, length);
    SI44_ResendPacket();
}
void SI44_ResendPacket(void)
{
    uint8_t txon = SI44_OPERATION_MODE_DEFAULT | 0b00001000;
    SI44_Write(SI44_REG_CTRL1, &txon, 1);
}

void SI44_ClearTXFIFO(void)
{
    uint8_t a = 1;
    SI44_Write(SI44_REG_CTRL2, &a, 1);
    a = 0;
    SI44_Write(SI44_REG_CTRL2, &a, 1);
}

uint8_t SI44_ReadBatteryVoltage(void)
{
    uint8_t value;
    SI44_Read(SI44_REG_BATTERY_VOLTAGE, &value, 1);
    return value;
}

uint8_t SI44_ReadTemperature(void)
{
    //Set adc input to internal temp. sensor
    uint8_t t = 0;
    SI44_Write(SI44_REG_ADC_CONFIG, &t, 1);
    //Set temperature range
    t = 0b00100000;
    SI44_Write(SI44_REG_TEMP_CONFIG, &t, 1);
    //Trigger ADC conversion
    t = 0b10000000;
    SI44_Write(SI44_REG_ADC_CONFIG, &t, 1);
    //Wait for ADC finish
    HAL_Delay(2);
    //Read out ADC value
    SI44_Read(SI44_REG_ADC_VALUE, &t, 1);
    return t;
}

void SI44_SetSyncBytes(uint8_t * bytes, uint8_t len)
{
    if (len > 4) 
    {
        return;
    }
    SI44_Write(SI44_REG_SYNC3, bytes, len);
}

void SI44_ForceRecalibrate(void)
{
    uint8_t t = SI44_FORCE_RACALIBRATION_VAL;
    SI44_Write(SI44_REG_CALIBRATION, &t, 1);
    HAL_Delay(10);
}