#include <unity.h>

#include <Dispatcher.h>

void StartTimerWorks()
{
    Dispatcher dispatcher;

    bool executed = false;

    TEST_ASSERT(executed);
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(StartTimerWorks);
    return UNITY_END();
}
