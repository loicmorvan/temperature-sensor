#include <Dispatcher.h>

#include <vector>

struct DispatcherItem
{
    TimeSpan period;
    TimeSpan time;
    std::function<void()> handler;

    void Execute(TimeSpan elapsedTime)
    {
        this->time = this->time + elapsedTime;
        while (this->time >= this->period)
        {
            this->handler();
            this->time = this->time - this->period;
        }
    }
};

struct Dispatcher::Pimpl
{
    std::vector<DispatcherItem*> items;
};

Dispatcher::Dispatcher()
{
    pimpl = new Pimpl();
}

void Dispatcher::Execute(TimeSpan elapsedTime)
{
    for (auto item: pimpl->items)
    {
        item->Execute(elapsedTime);
    }
}

void Dispatcher::StartTimer(TimeSpan period, std::function<void()> handler)
{
    auto item = new DispatcherItem();
    item->period = period;
    item->time = TimeSpan::FromMilliseconds(0);
    item->handler = handler;

    pimpl->items.push_back(item);
}
