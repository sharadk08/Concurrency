#include <iostream>
#include <thread>
#include <vector>
#include <atomic>

static std::atomic<int> shared_value = 0;

/*
void shared_val_inc() {
    shared_value = shared_value + 1;
    // it's a sequence of operations: read, multiply, add, write. Between these steps, another thread could change shared_value, 
    // leading to race conditions (asynchronous behavior). Instead, we should use atomic operations (operator overloading).
}
*/

void shared_val_inc() {
    shared_value++;
}


int main() {
    // Create and start multiple threads
    std::vector<std::thread> multiThread;

    for (int i = 0; i < 10000; i++)
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