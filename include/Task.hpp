#ifndef __TASK_H__
#define __TASK_H__

#include <functional>
#include <vector>

class Task {
    private:
        std::function<void()> _function;

    public:
        bool _persist_after_complete;

        Task(std::function<void()> function);
        Task(std::function<void()> function, bool persist);

        void execute();
};

#endif // __TASK_H__