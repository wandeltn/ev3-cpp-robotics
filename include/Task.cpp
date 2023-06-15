#include "Task.hpp"

Task::Task(std::function<void()> function)
{
    _function = function;
}

Task::Task(std::function<void()> function, bool persist)
{
    _function = function;
    _persist_after_complete = persist;
}

void Task::execute()
{
    _function();
}
