#include <iostream>
#include <thread>
#include <vector>

auto test = [](int x) {
    std::cout<<"Hello from my thread! "<< std::this_thread::get_id() <<std::endl;
    std::cout<<"Arguments passed in: "<<x<<std::endl;
};

int main() {
    // Initialized multiple jthreads
    // jthread available in C++20 and above
    std::vector<std::jthread> jThreads;

    /* destructor of jthread checks if the thread is joinable, then a stop is requested and joins the thread
        just before jthread going out of scope...
        no need to join thread manually if required then we can add it
    */
    for (int i = 0; i < 10; i++)
    {
        jThreads.push_back(std::jthread(test,i));
    }

    std::cout<<"Hello from main thread:)"<<std::endl;
    return 0;
}