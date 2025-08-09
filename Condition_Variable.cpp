#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex glblLock;
std::condition_variable glblConditionVar;
static bool ready = false;

int main() {
    int result = 0;
    std::cout << "Main thread: Starting work...\n";

    // Reporting thread
    // Must wait on work, done by the working thread
    std::thread reporter([&] {
        std::cout << "Worker thread: Waiting for work...\n";
        
        // Lock the mutex to protect shared data
        std::unique_lock<std::mutex> lock(glblLock);
        
        // Wait until 'ready' is true
        if (!ready)
        {
            glblConditionVar.wait(lock);
        }
        // glblConditionVar.wait(lock, [] { return ready; });
        
        std::cout << "Reporter thread: Report is ready, result is: " << result << std::endl;
    });

    // Worker thread
    // This thread will do some work and notify the reporter thread when done
    std::thread worker([&] {
        std::cout << "Worker thread: Doing some work...\n";

        // Lock the mutex to protect shared data
        std::lock_guard<std::mutex> lock(glblLock);

        // Do our work (Simulate some computation), because we have the lock
        result = 42 + 58 * 2;
        
        // Simulate some work
        ready = true;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::cout << "Worker thread: Work done" << std::endl;

        // Notify the reporter thread that work is done
        // This will wake up the reporter thread if it is waiting
        glblConditionVar.notify_one();
    });
    
    reporter.join();
    worker.join();

    std::cout << "Main thread: Exiting...\n";
    return 0;
}