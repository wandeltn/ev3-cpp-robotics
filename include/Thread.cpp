#include "Thread.hpp"

Thread::Thread(std::function<void()> function)
{
    _function = function;
    _persist_after_complete = false;
}

Thread::Thread(std::function<void()> function, bool persist)
{
    _function = function;
    _persist_after_complete = persist;
}

void Thread::execute()
{
    _function();
}
