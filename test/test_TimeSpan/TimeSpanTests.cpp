#include <unity.h>

#include <TimeSpan.h>

void CreateTimeSpanFromMilliseconds()
{
    auto sut1 = TimeSpan::FromMilliseconds(1000);
    TEST_ASSERT_TRUE(sut1.milliseconds == 1000);

    auto sut2 = TimeSpan::FromMilliseconds(10000);
    TEST_ASSERT_TRUE(sut2.milliseconds == 10000);

    auto sut3 = TimeSpan::FromMilliseconds(100);
    TEST_ASSERT_TRUE(sut3.milliseconds == 100);

    auto sut4 = TimeSpan::FromMilliseconds(10);
    TEST_ASSERT_TRUE(sut4.milliseconds == 10);
}

void CreateTimeSpanFromSeconds()
{
    auto sut1 = TimeSpan::FromSeconds(1000);
    TEST_ASSERT_TRUE(sut1.milliseconds == 1000000);

    auto sut2 = TimeSpan::FromSeconds(10000);
    TEST_ASSERT_TRUE(sut2.milliseconds == 10000000);

    auto sut3 = TimeSpan::FromSeconds(100);
    TEST_ASSERT_TRUE(sut3.milliseconds == 100000);

    auto sut4 = TimeSpan::FromSeconds(10);
    TEST_ASSERT_TRUE(sut4.milliseconds == 10000);
}

void ComparisonWorks()
{
    auto sut1 = TimeSpan::FromSeconds(0);
    auto sut2 = TimeSpan::FromSeconds(5);
    TEST_ASSERT(sut2 >= sut1);
}

void EqualityWorks()
{
    auto sut1 = TimeSpan::FromSeconds(5);
    auto sut2 = TimeSpan::FromSeconds(5);

    TEST_ASSERT(sut1 == sut2);
}

void AdditionWorks()
{
    auto sut1 = TimeSpan::FromSeconds(0);
    auto sut2 = TimeSpan::FromSeconds(5);

    auto result = sut1 + sut2;
    auto expected = TimeSpan::FromSeconds(5);

    TEST_ASSERT(result == expected);
}

void SubtractionWorks()
{
    auto sut1 = TimeSpan::FromSeconds(0);
    auto sut2 = TimeSpan::FromSeconds(5);

    auto result = sut1 - sut2;
    auto expected = TimeSpan::FromSeconds(-5);

    TEST_ASSERT(result == expected);
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(CreateTimeSpanFromMilliseconds);
    RUN_TEST(CreateTimeSpanFromSeconds);
    RUN_TEST(ComparisonWorks);
    RUN_TEST(EqualityWorks);
    RUN_TEST(AdditionWorks);
    RUN_TEST(SubtractionWorks);
    return UNITY_END();
}
