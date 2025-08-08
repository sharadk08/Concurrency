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
}
*/

void shared_val_inc() {
    /* Created a lock_guard object (holding mutex object) to manage the mutex automatically
        lock_guard locks the mutex on creation and unlocks it when going out of scope
    */
    std::lock_guard<std::mutex> lockGuard(glblLock);
    shared_value++;
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
    /* Created a lock_guard object (holding mutex object) to manage the mutex automatically
        lock_guard locks the mutex on creation and unlocks it when going out of scope
        This ensures that the mutex is always unlocked, even if an exception occurs
    */
   /*
    std::lock_guard<std::mutex> lockGuard(glblLock);
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