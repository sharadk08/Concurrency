#include <iostream>
#include <thread>
#include <vector>

auto test = [](int x) {
    std::cout<<"Hello from my thread! "<< std::this_thread::get_id() <<std::endl;
    std::cout<<"Arguments passed in: "<<x<<std::endl;
};

int main() {
    // Initialized multiple threads
    std::vector<std::thread> multiThread;

    for (int i = 0; i < 10; i++)
    {
        multiThread.push_back(std::thread(test,i));
    }
    
    /* Join used in different loop because if it's in same then
        it won't launch multiple thread because before launching 
        new thread it's waiting for previous thread to terminate
    */
    for (int i = 0; i < multiThread.size(); i++)
    {
        multiThread[i].join();
    }

    std::cout<<"Hello from main thread:)"<<std::endl;
    return 0;
}