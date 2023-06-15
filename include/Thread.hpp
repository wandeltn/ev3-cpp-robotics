#ifndef __THREAD_H__
#define __THREAD_H__

#include <vector>
#include <functional>
#include <memory>
#include "Task.hpp"

class Thread {
    private:
        std::vector<std::shared_ptr<Task>> _current_threads;

    public:
        Thread();

        std::shared_ptr<Task> create(std::function<void()> callback);
        std::shared_ptr<Task> create(std::function<void()> callback, bool persist);
        void start();
};

#endif // __THREAD_H__