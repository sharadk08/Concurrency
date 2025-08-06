#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

//Initialises globalLock object of a mutex class
std::mutex glblLock;

static int shared_value = 0;

/*
void shared_val_inc() {
    // In this synchronization are not possible...
    // Multiple thread are accessing this function parallelly
    // few threads are reading the value, few are performing increment operation and few are writing the value
    // so final value will not be same as no of times loop executed... to check increase the iteration of loop
    shared_value++;
}
*/

void shared_val_inc() {
    /* lock is blocking access to piece of code between lock and unlock to synchronize the code
        it's protecting this section from all threads except which got first and have access
        until previous thread not getting unlocked till that time all thread will be waiting for access
    */
    glblLock.lock();
    shared_value++;
    glblLock.unlock();
}

int main() {
    // Initialized multiple threads
    std::vector<std::thread> multiThread;

    for (int i = 0; i < 10000; i++)
    {
        multiThread.push_back(std::thread(shared_val_inc));
    }
    
    for (int i = 0; i < multiThread.size(); i++)
    {
        multiThread[i].join();
    }

    std::cout<<"Hello from main thread:) and value of shared_value: "<<shared_value<<std::endl;
    return 0;
}