#include <iostream>
#include <thread>
#include <mutex>

std::mutex glblMtxLock;

void job1() {
    glblMtxLock.lock();
    std::cout << "Job 1 is executed in thread: " << std::this_thread::get_id() << std::endl;
    glblMtxLock.unlock();
}

void job2() {
    // Attempt to lock the mutex without blocking
    // If the mutex is already locked, it will return false else true
    // This is useful to avoid deadlocks and to handle cases where the mutex is already locked
    if (glblMtxLock.try_lock())
    {
        std::cout << "Job 2 is executed in thread: " << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        glblMtxLock.unlock();
    }
    else
    {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        if (glblMtxLock.try_lock())
        {
            std::cout << "Job 2 is executed on 2nd attempt " << std::this_thread::get_id() << " after waiting" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            glblMtxLock.unlock();
        }
    }
}

int main() {
    std::thread t1(job1);
    std::thread t2(job2);

    t1.join();
    t2.join();

    std::cout << "Both jobs are completed." << std::endl;
    return 0;
}