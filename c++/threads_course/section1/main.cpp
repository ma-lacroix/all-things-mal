#include <chrono>
#include <iostream>
#include <thread>

void calculating_loop_1(int loops) {
    int total = 0;
    for (int i = 0; i < loops; ++i) {
        ++total;
    }
}

void calculating_loop_2(int loops) {
    int total = 0;
    for (int i = loops; i < 0; --i) {
        --total;
    }
}

void calculating_loop_3(int loops) {
    std::thread sub_thread1(calculating_loop_1,loops);
    std::thread sub_thread2(calculating_loop_2,loops);
    sub_thread1.join();
    sub_thread2.join();
}

int main() {
    auto start = std::chrono::steady_clock::now();

    std::cout << "Starting program" << std::endl;
    
    std::thread thread1(calculating_loop_1,1000000000);
    std::thread thread2(calculating_loop_2,1000000000);
    std::thread thread3(calculating_loop_3,1000000000);
    std::thread thread4(calculating_loop_2,1000000000);
    std::thread thread5(calculating_loop_1,1000000000);
    std::thread thread6(calculating_loop_2,1000000000);


    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();
    thread5.join();
    thread6.join();
    
    auto end1 = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start).count() << std::endl;

    calculating_loop_1(1000000000);
    calculating_loop_2(1000000000);
    calculating_loop_3(1000000000);
    calculating_loop_2(1000000000);
    calculating_loop_1(1000000000);
    calculating_loop_2(1000000000);

    auto end2 = std::chrono::steady_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end2 - end1).count() << std::endl;
    return 1;
}