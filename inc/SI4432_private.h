#include <stdint.h>
uint8_t SI44_CalcFrequencyDeviationRegister(uint32_t deviation);
void SI44_CalcFrequencyCarierRegisters(float freq, uint8_t * regs);