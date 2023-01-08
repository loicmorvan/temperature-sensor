#pragma once

#include <TimeSpan.h>
#include <functional>

class Dispatcher
{
private:
    struct Pimpl;
    Pimpl *pimpl;

public:
    Dispatcher();

    void Execute(TimeSpan elapsedTime);
    void StartTimer(TimeSpan period, std::function<void()> handler);
};
