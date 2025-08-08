#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

//Initialises globalLock object of a mutex class
std::mutex glblLock;

static int shared_value = 0;

/*
void shared_val_inc() {
    glblLock.lock();
    shared_value++;
    // If we don't unlock critical section then deadlock situation occurs
    // because previous thread leaves or goes out of scope without unclocking critical situation so
    // remaining threads are unable to complete their progress they are blocked and waiting for their chance to get access to critical section
    // If they unable to complete progress then join are not getting called in main thread.
}
*/

void shared_val_inc() {
    glblLock.lock();
    shared_value++;
    glblLock.unlock();
}

/*
void shared_val_inc() {
    glblLock.lock();
    // same here after increment exception will be thrown and catch block handle the exception and returns
    // thread goes out of scope without unlocking critical section
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
    // Initialized multiple threads
    std::vector<std::thread> multiThread;

    for (int i = 0; i < 20; i++)
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