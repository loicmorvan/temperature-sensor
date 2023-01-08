#pragma once

#include <TimeSpan.h>

typedef void (*Handler)(void);

class Dispatcher {
private:
    struct Pimpl;
    Pimpl *pimpl;

public:
    Dispatcher();

    void Execute(TimeSpan elapsedTime);
    void StartTimer(TimeSpan period, Handler handler);
};
