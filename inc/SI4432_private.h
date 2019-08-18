#include <stdint.h>
#include "SI4432.h"
#ifndef SI4432_PRIVATE
#define SI4432_PRIVATE
uint8_t SI44_CalcFrequencyDeviationRegister(uint32_t deviation);
void SI44_CalcFrequencyCarierRegisters(float freq, uint8_t * regs);
void SI44_CalcDataRateRegisters(uint16_t baudrate, uint8_t * regs);
void SI44_CalcPHRegisters(si44_ph_config config, uint8_t * regs);
void SI44_CalcConfigRegisters(si44_config config, uint8_t * regs);
void SI44_ClearTXFIFO(void);
#endif