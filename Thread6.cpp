#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

// Initializes a global mutex object for thread synchronization
std::mutex glblLock;

static int shared_value = 0;

/*
void shared_val_inc() {
    glblLock.lock();
    shared_value++;
    // If we do not unlock the mutex, a deadlock will occur.
    // Threads that leave the critical section without unlocking prevent other threads from progressing,
    // causing them to block and wait for access. As a result, join() in the main thread will not complete.
}
*/

void shared_val_inc() {
    glblLock.lock();
    shared_value++;
    // Always unlock the mutex after modifying the shared resource to avoid deadlocks
    glblLock.unlock();
}

/*
void shared_val_inc() {
    glblLock.lock();
    // If an exception is thrown after incrementing, and the catch block returns,
    // the mutex will not be unlocked, causing a deadlock.
    try
    {
        shared_value++;
        throw "dangerous abort";
    }
    catch(...)
    {
        std::cout << "handle exception" << std::endl;
        return;
    }
    glblLock.unlock();
}
*/
/*
void shared_val_inc() {
    glblLock.lock();
    // Properly unlock the mutex in the catch block to avoid deadlocks if an exception occurs
    try
    {
        shared_value++;
        throw "dangerous abort";
    }
    catch(...)
    {
        std::cout << "handle exception" << std::endl;
        glblLock.unlock();
        return;
    }
    glblLock.unlock();
}
*/

int main() {
    // Create and start multiple threads
    std::vector<std::thread> multiThread;

    for (int i = 0; i < 20; i++)
    {
        multiThread.push_back(std::thread(shared_val_inc));
    }

    // Wait for all threads to finish
    for (int i = 0; i < multiThread.size(); i++)
    {
        multiThread[i].join();
    }

    std::cout << "Hello from main thread :) Value of shared_value: " << shared_value << std::endl;
    return 0;
}