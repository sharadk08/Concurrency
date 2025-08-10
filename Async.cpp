#include <iostream>
#include <future>

int square(int x) {
    return x * x;
}

int main() {
    std::cout << "Main thread: Starting work...\n";

    // Create a future to hold the result of the asynchronous operation
    std::future<int> asyncFunc = std::async(std::launch::async, &square, 16);
    // std::future<int> asyncFunc = std::async(std::launch::async, square, 16);
    // Alternatively, you can use std::async without specifying launch policy
    // std::future<int> asyncFunc = std::async(square, 16);
    // std::future<int> asyncFunc = std::async(&square, 16);

    // Do some other work in the main thread
    std::cout << "Main thread: Doing some other work...\n";
    for (int i = 0; i < 10; i++)
    {
        std::cout << "Main thread: Working... square of " << i << " = " << square(i) << std::endl;
    }
    
    // We are blocked here until the async function completes meaning we wait for the result to get computated
    int result = asyncFunc.get();
    
    std::cout << "Main thread: The square is " << result << std::endl;
    std::cout << "Main thread: Exiting...\n";
    
    return 0;
}