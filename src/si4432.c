#include "SI4432.h"
#include "SI4432_private.h"
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