#include <iostream>
#include <thread>
#include <chrono>

std::mutex m;

template<typename T>
int funky_time(T a, T b) {

    std::cout << "Processing " << a << " " << b << std::endl;
    std::lock_guard<std::mutex> lg(m);
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    std::cout << "Done with " << a << " " << b << std::endl;
    return a * b;

}

int main() {
    
    std::thread t1(funky_time<float>,10.0,50.0);
    std::thread t2(funky_time<float>,20.0,50.0);
    t1.join();
    t2.join();
    return 0;

}