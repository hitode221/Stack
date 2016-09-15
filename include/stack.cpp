#include "Stack.h"
#include <iostream>
#ifndef STC_CPP
#define STC_CPP

using namespace std;

template <typename T>
stack<T>::stack() : array_size_(0), count_(0), array_(nullptr) {}

template <typename T>
stack<T>::stack(const stack<T> & stack_) : array_size_(stack_.array_size_), count_(stack_.count_) {
	array_ = copy_array(stack_.array_, array_size_, array_size_);
}

template <typename T>
stack<T> & stack<T>::operator =(stack<T> & stack_) {
	if (this != &stack_) {
		stack(stack_).swap(*this);
	}
	return *this;
}
template <typename T>
size_t stack<T>::count() const noexcept {
	return count_;
}
template <typename T>
size_t stack<T>::size() const noexcept {
	return array_size_;
}
template <typename T>
void stack<T>::push(T const & element) {
	if (array_size_ == count_) {
		array_size_ = array_size_ * 2 + (array_size_ == 0);
		T * temp = copy_array(array_, count_, array_size_);
		delete[] array_;
		array_ = temp;
	}
	array_[count_] = element;
	count_++;
}
template <typename T>
T& stack<T>::top() const throw(logic_error) {
	if (count_ != 0) {
		return array_[count_- 1];
	}
	else throw logic_error("Empty stack");
}
template <typename T>
void stack<T>::pop() throw(logic_error){
	if (count_ != 0) {
		count_--;
	}
	else throw logic_error("Empty stack");
}
template <typename T>
void stack<T>::swap(stack & stack_) noexcept {
	std::swap(array_size_, stack_.array_size_);
	std::swap(count_, stack_.count_);
	std::swap(array_, stack_.array_);
}
template <typename T>
stack<T>::~stack() {
	delete[] array_;
}
template <typename T>
T* copy_array(T * array_, size_t size, size_t new_size) {
	T * temp = new T[new_size];
	copy(array_, array_ + size, temp);
	return temp;
}
#endif
