#include "unity.h"
#include "FirstTest.h"

void test_FirstTest(void)
{
    TEST_ASSERT_EQUAL_HEX8(0xFF, FirstTest());
}

void setUp(void)
{

}

void tearDown(void)
{
    
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_FirstTest);
    return UNITY_END();
}
