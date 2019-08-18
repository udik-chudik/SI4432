#include "unity.h"
#include "SI4432.h"
#include "SI4432_private.h"
#include "io_fake.h"
#include <string.h>
fake_io_call * fake_io_call_stack;

int fake_io_ncall;
SPI_HandleTypeDef * spi_interface;
void setUp(void)
{
    fake_io_ncall = 0;
    fake_io_call buf[15];
    fake_io_call_stack =  buf;
}

void tearDown(void)
{
    fake_io_call_stack = NULL;
    spi_interface = NULL;
}

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

    SI44_CalcFrequencyCarierRegisters(888.88, regs);
    //0x75
    TEST_ASSERT_EQUAL(0x74, regs[0]);
    //0x76
    TEST_ASSERT_EQUAL(0x6f, regs[1]);
    //0x77
    TEST_ASSERT_EQUAL(0x00, regs[2]);
}

void test_SI44_CalcDataRateRegisters(void)
{
    uint8_t regs[2];
    SI44_CalcDataRateRegisters(1000, regs);
    //0x6e
    TEST_ASSERT_EQUAL(0x08, regs[0]);
    //0x6f
    TEST_ASSERT_EQUAL(0x31, regs[1]);
    /*
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
    */
}

void test_SI44_CalcPHRegisters(void)
{
    uint8_t regs[3];
    si44_ph_config config;

    config.path = SI44_PH_PATH_TX_ONLY;
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
    TEST_ASSERT_EQUAL(32, regs[2]);
}

void test_SI44_CalcConfigRegisters(void)
{
    si44_config conf;
    conf.modulation_type = SI44_MODULATION_TYPE_GFSK;
    conf.modulation_source = SI44_MODULATION_SOURCE_FIFO;
    conf.encoding_options = 0;

    uint8_t regs[2];
    SI44_CalcConfigRegisters(conf, regs);

    //0x70
    TEST_ASSERT_EQUAL(0b00100000, regs[0]);
    //0x71
    TEST_ASSERT_EQUAL(0b00100011, regs[1]);
}

void test_SI44_ReadStatus(void)
{
    uint8_t status = SI44_ReadStatus();
     
    TEST_ASSERT_EQUAL(1, fake_io_call_stack[0].length);
    TEST_ASSERT_EQUAL(0x02, fake_io_call_stack[0].reg);
    TEST_ASSERT_EQUAL(READ, fake_io_call_stack[0].type);
    TEST_ASSERT_EQUAL(1, status);
}

void test_SI44_Reset(void)
{
    SI44_Reset();
    TEST_ASSERT_EQUAL(0b10000001, fake_io_call_stack[0].buf[0]);
    TEST_ASSERT_EQUAL(1, fake_io_call_stack[0].length);
    TEST_ASSERT_EQUAL(0x07, fake_io_call_stack[0].reg);
    TEST_ASSERT_EQUAL(WRITE, fake_io_call_stack[0].type);
}

void test_SI44_Init(void)
{
    SPI_HandleTypeDef a = 125;
    GPIO_TypeDef port = 1;
    SI44_Init(&a, &port, 1);
    TEST_ASSERT_EQUAL(0b10000001, fake_io_call_stack[0].buf[0]);
    TEST_ASSERT_EQUAL(125, *spi_interface);
    TEST_ASSERT_EQUAL(1, fake_io_ncall);
    TEST_ASSERT_EQUAL(0x07, fake_io_call_stack[0].reg);
    //Should make soft reset
    //Should save spi_handler
}

void test_SI44_SetConfig(void)
{
    //Should write appropriate registers
    si44_config conf;
    conf.modulation_type = SI44_MODULATION_TYPE_GFSK;
    conf.modulation_source = SI44_MODULATION_SOURCE_FIFO;
    conf.encoding_options = 0;

    SI44_SetConfig(&conf);

    TEST_ASSERT_EQUAL(5, fake_io_ncall);
    TEST_ASSERT_EQUAL(0x70, fake_io_call_stack[0].reg);
    TEST_ASSERT_EQUAL(0x71, fake_io_call_stack[1].reg);

}
void test_SI44_SetPHConfig(void)
{
    //Should write appropriate registers
    si44_ph_config config;

    config.path = SI44_PH_PATH_TX_ONLY;
    config.preambule_length = 32;
    config.sync = SI44_PH_SYNC_2;
    config.header = SI44_PH_HEADER_OFF;
    config.crc = SI44_PH_CRC_DATA_ONLY;
    config.crc_type = SI44_PH_CRC_TYPE_IBM16;

    SI44_SetPHConfig(&config);

    TEST_ASSERT_EQUAL(3, fake_io_ncall);
    TEST_ASSERT_EQUAL(0x30, fake_io_call_stack[0].reg);
    TEST_ASSERT_EQUAL(0x33, fake_io_call_stack[1].reg);
    TEST_ASSERT_EQUAL(0x34, fake_io_call_stack[2].reg);
}

void test_SI44_SetFrequency(void)
{
    //Should call calc
    //Should write appropriate registers
    SI44_SetFrequency(433.0);

    TEST_ASSERT_EQUAL(3, fake_io_ncall);
    TEST_ASSERT_EQUAL(0x75, fake_io_call_stack[0].reg);
    TEST_ASSERT_EQUAL(0x76, fake_io_call_stack[1].reg);
    TEST_ASSERT_EQUAL(0x77, fake_io_call_stack[2].reg);
}


void test_SI44_SetDataRate(void)
{
    SI44_SetDataRate(2000);

    TEST_ASSERT_EQUAL(2, fake_io_ncall);
    TEST_ASSERT_EQUAL(0x6e, fake_io_call_stack[0].reg);
    TEST_ASSERT_EQUAL(0x6f, fake_io_call_stack[1].reg);

}

void test_SI44_SetFrequencyDeviation(void)
{

    SI44_SetFrequencyDeviation(65000);
    
    TEST_ASSERT_EQUAL(1, fake_io_ncall);
    TEST_ASSERT_EQUAL(0x72, fake_io_call_stack[0].reg);

}

void test_SI44_SetTXPower(void)
{
    SI44_SetTXPower(SI44_TX_POWER_14dBm);
    TEST_ASSERT_EQUAL(SI44_TX_POWER_14dBm, fake_io_call_stack[0].buf[0]);
    TEST_ASSERT_EQUAL(1, fake_io_ncall);
    TEST_ASSERT_EQUAL(0x6d, fake_io_call_stack[0].reg);
    TEST_ASSERT_EQUAL(WRITE, fake_io_call_stack[0].type);
    
}


void test_SI44_SendPacket(void)
{   
    //Should clear fifo
    //Should write to fifo
    //Should toggle txon bit
    const char data[] = "2134";
    SI44_SendPacket((uint8_t *)data, strlen(data));
    TEST_ASSERT_EQUAL(7, fake_io_ncall);
    //TEST_ASSERT_EQUAL(0x7f, fake_io_call_stack[1].reg);
    //TEST_ASSERT_EQUAL(0x07, fake_io_call_stack[3].reg);

}

void test_SI44_ResendPacket(void)
{
    //Should toggle txon
    SI44_ResendPacket();
    TEST_ASSERT_EQUAL(1, fake_io_ncall);
    TEST_ASSERT_EQUAL(0x07, fake_io_call_stack[0].reg);


}

void test_SI44_ReadBatteryVoltage(void)
{
    uint8_t v = SI44_ReadBatteryVoltage();
    TEST_ASSERT_EQUAL(0x1b, fake_io_call_stack[0].reg);
    TEST_ASSERT_EQUAL(1, v);
}

void test_SI44_ReadTemperature(void)
{
    //Should configure ADC for internal Temp. sensor
    //Should set appropriate ADC offset
    //Should configure temp. sensor calibration
    //Should start ADC conversion
    //Should wait for ADC conversion finishes
    //Should give a right value))
    uint8_t T = SI44_ReadTemperature();
    //Config ADC
    TEST_ASSERT_EQUAL(0x0f, fake_io_call_stack[0].reg);
    TEST_ASSERT_EQUAL(0b00000000, fake_io_call_stack[0].buf[0]);
    //Config TEMP. RANGE (-40 +63, 0.5 resolution, in Celsium)
    TEST_ASSERT_EQUAL(0x12, fake_io_call_stack[1].reg);
    //TEST_ASSERT_EQUAL(0b00100000, fake_io_call_stack[1].buf[0]);
    //Check for triggering ADC read
    TEST_ASSERT_EQUAL(0x0f, fake_io_call_stack[2].reg);
    //TEST_ASSERT_EQUAL(0b10000000, fake_io_call_stack[2].buf[0]);
    
    //Check for reading ADC value after conversion
    TEST_ASSERT_EQUAL(0x11, fake_io_call_stack[3].reg);
    TEST_ASSERT_EQUAL(T, 1);

}