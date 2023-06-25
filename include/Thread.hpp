#ifndef __Thread_H__
#define __Thread_H__

#include <functional>
#include <vector>

class Thread {
    private:
        std::function<void()> _function;

    public:
        bool _persist_after_complete;

        Thread(std::function<void()> function);
        Thread(std::function<void()> function, bool persist);

        void execute();
};

#endif // __Thread_H__