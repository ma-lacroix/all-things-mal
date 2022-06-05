#pragma once
#include <iostream>
#include <mutex>
#include <stack>
#include <thread>
#include <chrono>
#include <memory>
#include <stdexcept>

template<typename T>
class thread_safe_stack {
public:
	std::stack<std::shared_ptr<T>> stk;
	std::mutex m;

public:
    thread_safe_stack() {};
    ~thread_safe_stack() {};
	void push(T element)
	{
		std::lock_guard<std::mutex> lg(m);
		stk.push(std::make_shared<T>(element));
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
		std::cout << "Done pushing " << element << std::endl;
	}

	std::shared_ptr<T> pop()
	{
		std::lock_guard<std::mutex> lg(m);
		if (stk.empty())
		{
			throw std::runtime_error("stack is empty");
		}

		std::shared_ptr<T> res(stk.top());
		stk.pop();
		return res;
	}

	void pop(T& value)
	{
		std::lock_guard<std::mutex> lg(m);
		if (stk.empty()) throw std::runtime_error("stack is empty");
		value = *(stk.top().get());
		stk.pop();
	}


	bool empty()
	{
		std::lock_guard<std::mutex> lg(m);
		return stk.empty();
	}

	size_t size()
	{
		std::lock_guard<std::mutex> lg(m);
		return stk.size();
	}
};