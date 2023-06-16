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
    for (int thread_index = 0; thread_index <= _current_threads.size(); thread_index++) {
        _current_threads[thread_index]->execute();
        if (_current_threads[thread_index]->_persist_after_complete) {
            _current_threads.erase(_current_threads.begin() + thread_index);
        }
    }
}
