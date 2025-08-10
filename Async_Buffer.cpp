#include <iostream>
#include <thread>
#include <future>

bool bufferedLoader() {
    int count = 0;
    size_t bytesLoader = 0;
    while (bytesLoader < 20000)
    {
        count++;
        std::cout<<"thread: loading file..."<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        bytesLoader += 1000;
    }
    std::cout<<"Count in buuferedLoader is: "<< count << std::endl;
    
    return true;
}

int main()
{
    int counter = 0;

    // future to hold the result of the asynchronous operation
    // We use std::launch::async to ensure that the function runs in a separate thread immediately
    // std::launch::deferred would mean that the function runs only when we call get() or wait() on the future
    // if not launched then it will be system will decide whether to run immediately or not
    std::future<bool> backGroundThread = std::async(std::launch::async, bufferedLoader);
    // std::future<bool> backGroundThread = std::async(bufferedLoader);

    // future status to check if the background thread is ready
    // std::future_status is used to check the status of the future
    // it holds the status of the asynchronous operation getting from wait_for() or wait_until()
    std::future_status status;

    // Our main program loop
    while (true)
    {
        counter++;
        std::cout<<"Main thread is running..."<<std::endl;

        // Artificial sleep for our program
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        // wait() -> blocks until the asynchronous operation is complete and returns the result
        // wait_for() -> blocks for a specified duration and returns the status of the asynchronous operation
        // it will return std::future_status::ready if the operation is complete
        // it will return std::future_status::timeout if the operation is not complete within the specified duration
        status = backGroundThread.wait_for(std::chrono::milliseconds(10));

        // If our data is ready, that is, our background thread is completed
        if(status == std::future_status::ready) {
            std::cout<<"Our data is ready"<<std::endl;
            break;
        }
    }

    std::cout<<"Program is completed and counter id: "<< counter <<std::endl;
    return 0;
    
}