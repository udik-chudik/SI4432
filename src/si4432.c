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