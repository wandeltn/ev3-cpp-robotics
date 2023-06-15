#ifndef __THREAD_H__
#define __THREAD_H__

#include <vector>
#include <functional>
#include "Task.hpp"

class Thread {
    private:
        std::vector<Task> _current_threads;

    public:
        Thread();

        void create(std::function<void()>);
        void start();
};

#endif // __THREAD_H__