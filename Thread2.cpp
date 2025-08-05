#include <iostream>
#include <thread>

auto test = [](int x) {
    std::cout<<"Hello from my thread! "<<std::endl;
    std::cout<<"Arguments passed in: "<<x<<std::endl;
};

int main() {
    /* Declared test as a lambda function
        it can be passed without reference
    */
    std::thread myThread(test, 10);

    myThread.join();

    std::cout<<"Hello from main thread:)"<<std::endl;
    return 0;
}