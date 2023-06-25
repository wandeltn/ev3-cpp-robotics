#include "Rope.hpp"

Rope::Rope()
{
    
}

std::shared_ptr<Thread> Rope::create(std::function<void()> callback)
{
    std::shared_ptr<Thread> thread = std::shared_ptr<Thread>(new Thread(callback));
    _current_threads.push_back(thread);
    return thread;
}

std::shared_ptr<Thread> Rope::create(std::function<void()> callback, bool persist)
{
    std::shared_ptr<Thread> thread = std::shared_ptr<Thread>(new Thread(callback, persist));
    _current_threads.push_back(thread);
    return thread;
}

void Rope::start()
{
    for (int thread_index = 0; thread_index <= _current_threads.size(); thread_index++) {
        _current_threads[thread_index]->execute();
        if (_current_threads[thread_index]->_persist_after_complete) {
            _current_threads.erase(_current_threads.begin() + thread_index);
        }
    }
}
