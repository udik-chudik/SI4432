/* AUTOGENERATED FILE. DO NOT EDIT. */

/*=======Test Runner Used To Run Each Test Below=====*/
#define RUN_TEST(TestFunc, TestLineNum) \
{ \
  Unity.CurrentTestName = #TestFunc; \
  Unity.CurrentTestLineNumber = TestLineNum; \
  Unity.NumberOfTests++; \
  UNITY_EXEC_TIME_START(); \
  if (TEST_PROTECT()) \
  { \
      setUp(); \
      TestFunc(); \
  } \
  if (TEST_PROTECT()) \
  { \
    tearDown(); \
  } \
  UNITY_EXEC_TIME_STOP(); \
  UnityConcludeTest(); \
}

/*=======Automagically Detected Files To Include=====*/
#define UNITY_INCLUDE_SETUP_STUBS
#include "unity.h"
#ifndef UNITY_EXCLUDE_SETJMP_H
#include <setjmp.h>
#endif
#include <stdio.h>
#include "SI4432.h"
#include "SI4432_private.h"
#include "io_fake.h"
#include <string.h>

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_SI44_CalcFrequencyDeviationRegister(void);
extern void test_SI44_CalcFrequencyCarier(void);
extern void test_SI44_CalcDataRateRegisters(void);
extern void test_SI44_CalcPHRegisters(void);
extern void test_SI44_CalcConfigRegisters(void);
extern void test_SI44_ReadStatus(void);
extern void test_SI44_Reset(void);
extern void test_SI44_Init(void);
extern void test_SI44_SetConfig(void);
extern void test_SI44_SetPHConfig(void);
extern void test_SI44_SetFrequency(void);
extern void test_SI44_SetDataRate(void);
extern void test_SI44_SetFrequencyDeviation(void);
extern void test_SI44_SetTXPower(void);
extern void test_SI44_SendPacket(void);
extern void test_SI44_ResendPacket(void);


/*=======Suite Setup=====*/
static void suite_setup(void)
{
#if defined(UNITY_WEAK_ATTRIBUTE) || defined(UNITY_WEAK_PRAGMA)
  suiteSetUp();
#endif
}

/*=======Suite Teardown=====*/
static int suite_teardown(int num_failures)
{
#if defined(UNITY_WEAK_ATTRIBUTE) || defined(UNITY_WEAK_PRAGMA)
  return suiteTearDown(num_failures);
#else
  return num_failures;
#endif
}

/*=======Test Reset Option=====*/
void resetTest(void);
void resetTest(void)
{
  tearDown();
  setUp();
}


/*=======MAIN=====*/
int main(void)
{
  suite_setup();
  UnityBegin("test/test_si4432.c");
  RUN_TEST(test_SI44_CalcFrequencyDeviationRegister, 23);
  RUN_TEST(test_SI44_CalcFrequencyCarier, 36);
  RUN_TEST(test_SI44_CalcDataRateRegisters, 90);
  RUN_TEST(test_SI44_CalcPHRegisters, 118);
  RUN_TEST(test_SI44_CalcConfigRegisters, 140);
  RUN_TEST(test_SI44_ReadStatus, 156);
  RUN_TEST(test_SI44_Reset, 166);
  RUN_TEST(test_SI44_Init, 175);
  RUN_TEST(test_SI44_SetConfig, 187);
  RUN_TEST(test_SI44_SetPHConfig, 202);
  RUN_TEST(test_SI44_SetFrequency, 222);
  RUN_TEST(test_SI44_SetDataRate, 235);
  RUN_TEST(test_SI44_SetFrequencyDeviation, 245);
  RUN_TEST(test_SI44_SetTXPower, 255);
  RUN_TEST(test_SI44_SendPacket, 266);
  RUN_TEST(test_SI44_ResendPacket, 279);

  return suite_teardown(UnityEnd());
}
