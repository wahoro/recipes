#ifndef WAITER_H_H_
#define WAITER_H_H_

#include <mutex>
#include <condition_variable>

class Waiter
{
public:
    Waiter() = default;

    void wait() {
        std::unique_lock<std::mutex> lock(mutex_);
        while (!signaled_) {
            cond_.wait(lock);
        }
    }

    void signal() {
        broadcast();
    }

    void broadcast() {
        std::unique_lock<std::mutex> lock(mutex_);
        signaled_ = true;
        cond_.notify_all();
    }

    void reset() {
        std::unique_lock<std::mutex> lock(mutex_);
        signaled_ = false;
    }

private:
    std::mutex mutex_;
    std::condition_variable cond_;
    bool signaled_ = false;
};

#endif // WAITER_H_H_
