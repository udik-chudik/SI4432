#include "unity.h"
#include "SI4432.h"
#include "SI4432_private.h"

void test_SI44_CalcFrequencyDeviationRegister(void)
{
    uint8_t val;
    val = SI44_CalcFrequencyDeviationRegister(625);
    TEST_ASSERT_EQUAL(1, val);
    val = SI44_CalcFrequencyDeviationRegister(624);
    TEST_ASSERT_EQUAL(0, val);
    val = SI44_CalcFrequencyDeviationRegister(159375);
    TEST_ASSERT_EQUAL(255, val);
    val = SI44_CalcFrequencyDeviationRegister(2500);
    TEST_ASSERT_EQUAL(4, val);
}

void test_SI44_CalcFrequencyCarier(void)
{
    uint8_t regs[3];
    SI44_CalcFrequencyCarierRegisters(437.0, regs);

    //0x75
    TEST_ASSERT_EQUAL(0x53, regs[0]);
    //0x76
    TEST_ASSERT_EQUAL(0xaf, regs[1]);
    //0x77
    TEST_ASSERT_EQUAL(0, regs[2]);


    SI44_CalcFrequencyCarierRegisters(437.1, regs);
    //0x75
    TEST_ASSERT_EQUAL(0x53, regs[0]);
    //0x76
    TEST_ASSERT_EQUAL(0xb1, regs[1]);
    //0x77
    TEST_ASSERT_EQUAL(0x80, regs[2]);
    
    SI44_CalcFrequencyCarierRegisters(250.18, regs);
    //0x75
    TEST_ASSERT_EQUAL(0x41, regs[0]);
    //0x76
    TEST_ASSERT_EQUAL(0x04, regs[1]);
    //0x77
    TEST_ASSERT_EQUAL(0x80, regs[2]);
    
    SI44_CalcFrequencyCarierRegisters(911.0, regs);
    //0x75
    TEST_ASSERT_EQUAL(0x75, regs[0]);
    //0x76
    TEST_ASSERT_EQUAL(0x89, regs[1]);
    //0x77
    TEST_ASSERT_EQUAL(0x80, regs[2]);

    SI44_CalcFrequencyCarierRegisters(435.47, regs);
    //0x75
    TEST_ASSERT_EQUAL(0x53, regs[0]);
    //0x76
    TEST_ASSERT_EQUAL(0x88, regs[1]);
    //0x77
    TEST_ASSERT_EQUAL(0xc0, regs[2]);
}
/*
void test_SI44_CalcDataRateRegisters(void)
{
    uint8_t regs[2];
    SI44_CalcDataRateRegisters(1000, regs);
    //0x6e
    TEST_ASSERT_EQUAL(0x08, regs[0]);
    //0x6f
    TEST_ASSERT_EQUAL(0x31, regs[1]);

    SI44_CalcDataRateRegisters(1200, regs);
    //0x6e
    TEST_ASSERT_EQUAL(0x09, regs[0]);
    //0x6f
    TEST_ASSERT_EQUAL(0xd5, regs[1]);

    SI44_CalcDataRateRegisters(1200, regs);
    //0x6e
    TEST_ASSERT_EQUAL(0x09, regs[0]);
    //0x6f
    TEST_ASSERT_EQUAL(0xd5, regs[1]);

    SI44_CalcDataRateRegisters(9600, regs);
    //0x6e
    TEST_ASSERT_EQUAL(0x4e, regs[0]);
    //0x6f
    TEST_ASSERT_EQUAL(0xa5, regs[1]);
}

void test_SI44_CalcPHRegisters(void)
{
    uint8_t regs[3];
    si44_ph_config config;

    config.path = SI44_PH_TX_ONLY;
    config.preambule_length = 32;
    config.sync = SI44_PH_SYNC_2;
    config.header = SI44_PH_HEADER_OFF;
    config.crc = SI44_PH_CRC_DATA_ONLY;
    config.crc_type = SI44_PH_CRC_TYPE_IBM16;

    SI44_CalcPHRegisters(config, regs);

    //0x30
    TEST_ASSERT_EQUAL(0b00101101, regs[0]);
    //0x33
    TEST_ASSERT_EQUAL(0b00000010, regs[1]);
    //0x34
    TEST_ASSERT_EQUAL(32*4, regs[2]);
}

void test_SI44_CalcConfigRegisters(void)
{
    si44_config conf;
    conf.modulation_type = SI44_MODULATION_TYPE_GFSK;
    conf.modulation_source = SI44_MODULATION_SOURCE_FIFO;

    uint8_t regs[2];
    SI44_CalcConfigRegisters(conf, regs);

    //0x70
    TEST_ASSERT_EQUAL(0b00100000, regs[0]);
    //0x71
    TEST_ASSERT_EQUAL(0b00100011, regs[1]);
}

void test_SI44_Init(void)
{
    //Should make soft reset
    //Should save spi_handler
}

void test_SI44_SetConfig(void)
{
    //Should write appropriate registers
}

void test_SI44_SetPHConfig(void)
{
    //Should write appropriate registers
}

void test_SI44_SetFrequency(void)
{
    //Should call calc
    //Should write appropriate registers
}

void test_SI44_SendPacket(void)
{   
    //Should clear fifo
    //Should write to fifo
    //Should toggle txon bit
}

void test_SI44_ResendPacket(void)
{
    //Should toggle txon
}
*/