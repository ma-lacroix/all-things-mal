#include <iostream>
#include <stack>
#include <thread>
#include "stack_impl.h"

void push_new(thread_safe_stack<int> *a_stack, int a) {
    a_stack->push(a);
}

void pop_last(thread_safe_stack<int> *a_stack) {
    a_stack->pop();
}

int main()
{
	
    thread_safe_stack<int> *some_stack = new thread_safe_stack<int>();
    
    std::thread t1a(push_new,some_stack,30);
    std::thread t2a(push_new,some_stack,4);

    t1a.join();
    t2a.join();
    
    return 0;
}