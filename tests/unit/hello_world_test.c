#include "unity.h"

void setUp(void)
{
    // This is run before EACH test
}

void tearDown(void)
{
    // This is run after EACH test
}

void test_hello_world(void)
{
    // Arrange
    char expected[] = "Hello, World!";
    char actual[] = "Hello, World!";

    // Assert
    TEST_ASSERT_EQUAL_STRING(expected, actual);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_hello_world);
    UNITY_END();

    return 0;
}