#pragma once
#include <stdexcept>

using namespace std; 

template <typename T>
T* copy_array(T * array_, size_t size, size_t new_size); //strong

template <typename T>
class stack {
public:
	stack(); //strong
	stack(const stack<T> & stack_); //strong
	stack<T> & operator =(stack<T> & stack_); //strong 
	size_t count() const noexcept; //noexcept
	size_t size() const noexcept; //noexcept
	void push(T const & element); //strong
	T& top() const throw(logic_error); //strong
	void pop() throw(logic_error); //strong
	void swap(stack & stack_) noexcept; //noexcept
	~stack(); //noexcept
private:
	T * array_;
	size_t array_size_;
	size_t count_;
};

#include "stack.cpp"

