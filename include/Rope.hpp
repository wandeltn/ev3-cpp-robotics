#ifndef __Rope_H__
#define __Rope_H__

#include <vector>
#include <functional>
#include <memory>
#include "Thread.hpp"

class Rope {
    private:
        std::vector<std::shared_ptr<Thread>> _current_threads;

    public:
        Rope();

        std::shared_ptr<Thread> create(std::function<void()> callback);
        std::shared_ptr<Thread> create(std::function<void()> callback, bool persist);
        void start();
};

#endif // __Rope_H__