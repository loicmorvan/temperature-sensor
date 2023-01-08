#include <unity.h>

#include <Dispatcher.h>

void StartTimerWorks()
{
    bool executed = false;

    Dispatcher dispatcher;
    dispatcher.StartTimer(TimeSpan::FromMilliseconds(1), [&](){ executed = true; });
    dispatcher.Execute(TimeSpan::FromMilliseconds(1));

    TEST_ASSERT(executed);
}

void NothingIsCalledWithoutExecute()
{
    bool executed = false;

    Dispatcher dispatcher;
    dispatcher.StartTimer(TimeSpan::FromMilliseconds(1), [&](){ executed = true; });

    TEST_ASSERT_FALSE(executed);
}

void ComplexExample()
{
    int firstCount = 0;
    int secondCount = 0;

    Dispatcher dispatcher;
    dispatcher.StartTimer(TimeSpan::FromMilliseconds(1), [&](){ firstCount += 1; });
    dispatcher.StartTimer(TimeSpan::FromMilliseconds(2), [&](){ secondCount += 1; });
    dispatcher.Execute(TimeSpan::FromMilliseconds(4));

    TEST_ASSERT_EQUAL(4, firstCount);
    TEST_ASSERT_EQUAL(2, secondCount);
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(StartTimerWorks);
    RUN_TEST(NothingIsCalledWithoutExecute);
    RUN_TEST(ComplexExample);
    return UNITY_END();
}
