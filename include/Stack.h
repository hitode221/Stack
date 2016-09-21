#pragma once
#include <stdexcept>

using namespace std; 

template <typename T>
class stack {
public:
	stack(); 
	stack(const stack<T> & stack_); 
	stack<T> & operator =(stack<T> & stack_);
	size_t count() const noexcept; 
	size_t size() const noexcept; 
	void push(T const & element);
	T& top() const throw(logic_error); 
	void pop() throw(logic_error); 
	void swap(stack & stack_) noexcept;
	~stack(); 
private:
	T * array_;
	size_t array_size_;
	size_t count_;
};

#include "stack.cpp"

