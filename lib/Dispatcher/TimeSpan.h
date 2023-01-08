#pragma once

struct TimeSpan
{
    unsigned long milliseconds;

    static TimeSpan FromSeconds(unsigned long seconds)
    {
        return {.milliseconds = seconds * 1000};
    }

    static TimeSpan FromMilliseconds(unsigned long milliseconds)
    {
        return {.milliseconds = milliseconds};
    }

    TimeSpan operator+(TimeSpan right)
    {
        return {
            .milliseconds = milliseconds + right.milliseconds,
        };
    }

    TimeSpan operator-(TimeSpan right)
    {
        return {
            .milliseconds = milliseconds - right.milliseconds,
        };
    }

    bool operator >=(TimeSpan right)
    {
        return milliseconds >= right.milliseconds;
    }

    bool operator ==(TimeSpan other)
    {
        return milliseconds == other.milliseconds;
    }
};
