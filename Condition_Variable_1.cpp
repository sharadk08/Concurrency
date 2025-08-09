#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void waitForWork() {
    // Lock the mutex to protect shared data
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << "Worker thread: Waiting for signal...\n";

    /* This thread goes into blocked state until it is notified
        by the main thread that it can proceed
        waiting for the condition variable to be notified
        1. Before wait: Mutex locked by unique_lock.
        2. Inside wait: Mutex unlocked so other threads can do work and notify.
        3. Before returning from wait: Mutex locked again to ensure safe continuation.
        4. After wait: You still hold the lock until lock goes out of scope (or you manually unlock()).
    */
    cv.wait(lock, [] { return ready; });  // Wait until 'ready' becomes true
    std::cout << "Worker thread: Received signal! Proceeding...\n";
}

void setReady() {
    std::this_thread::sleep_for(std::chrono::seconds(5)); // Simulate work
    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true;
        std::cout << "Main thread: Setting ready = true\n";
    }
    cv.notify_one();  // Notify the waiting thread
}

int main() {
    std::thread worker(waitForWork);
    std::thread notifier(setReady);

    worker.join();
    notifier.join();

    std::cout << "Main thread: All done!\n";
    return 0;
}