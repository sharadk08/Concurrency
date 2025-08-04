#include <iostream>
#include <thread>

void test (int x) {
    std::cout<<"Hello from my thread! "<<std::endl;
    std::cout<<"Arguments passed in: "<<x<<std::endl;
}

int main() {
    /* Created a thread object and passed reference of a function with parameter of that function
        You can either pass only reference of a function or no need to pass an argument
    */
    std::thread myThread(&test, 10);

    /* join() member of thread called to avoid core dump
        if it's not there then 2 threads are running here one is object other is main() thread
        main thread is getting terminated(program completed and returns 0) before thread object getting terminated
        to avoid this called join member it tells main thread to wait for it to terminate
    */
    myThread.join();

    std::cout<<"Hello from main thread:)"<<std::endl;
    return 0;
}