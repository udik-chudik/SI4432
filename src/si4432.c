#include "SI4432.h"
#include "SI4432_private.h"
#include <stdio.h>
uint8_t SI44_CalcFrequencyDeviationRegister(uint32_t deviation)
{
    return (uint8_t) (deviation/625);
}

void SI44_CalcFrequencyCarierRegisters(float freq, uint8_t * regs)
{
    uint8_t fb = 0;
    uint8_t hbsel = 0b01000000;
    if (freq < 480.0)
    {
        fb = (uint8_t) ((freq - 240.0)/10.0);
    } else {
        fb = 24 + (uint8_t) ((freq - 480.0)/20.0);
        hbsel |= 0b00100000;
    }
    regs[0] = hbsel | (fb & 0b00011111);
    uint16_t fc = 0;
    //printf("\n\n%f\n\n", fb);
    fc = (uint16_t) (64000.0f*(freq/(10.0 * (1.0 + (freq > 480.0 ? 1.0 : 0) )) - 24.0 - fb ));
    //printf("\n\n%f\n\n", (freq/(10.0 * (1.0 + (freq > 480.0 ? 1.0 : 0) )) - 24.0 - fb ));
    //printf("\n\n%f\n\n", 0.018);
    regs[1] = (uint8_t) ((fc >> 8) & 0xff);
    regs[2] = (uint8_t) (fc & 0xff);
}