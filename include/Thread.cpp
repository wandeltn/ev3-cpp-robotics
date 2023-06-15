#include "Thread.hpp"

Thread::Thread()
{
    
}

std::shared_ptr<Task> Thread::create(std::function<void()> callback)
{
    std::shared_ptr<Task> thread = std::shared_ptr<Task>(new Task(callback));
    _current_threads.push_back(thread);
    return thread;
}

std::shared_ptr<Task> Thread::create(std::function<void()> callback, bool persist)
{
    std::shared_ptr<Task> thread = std::shared_ptr<Task>(new Task(callback, persist));
    _current_threads.push_back(thread);
    return thread;
}

void Thread::start()
{

}
