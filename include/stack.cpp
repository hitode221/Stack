#include "Stack.h"

#ifndef STC_CPP
#define STC_CPP

using namespace std;

template <typename T>
stack<T>::stack() : array_size_(0), count_(0), array_(nullptr) {}

template <typename T>
stack<T>::stack(const stack<T> & stack_) : array_size_(stack_.array_size_), count_(stack_.count_) {
		array_ = new T[array_size_];
		for (size_t i = 0; i < count_; i++) {
			array_[i] = stack_.array_[i];
		}
	}

template <typename T>
stack<T> & stack<T>::operator =(stack<T> & stack_) {
	if (this != &stack_) {
		stack(stack_).swap(*this);
	}
	return *this;
}
template <typename T>
size_t stack<T>::count() const {
	return count_;
}
template <typename T>
size_t stack<T>::size() const {
	return array_size_;
}
template <typename T>
void stack<T>::push(T const & element) {
	if (array_size_ == count_) {
		array_size_++;
		T * temp = new T[array_size_];
		for (size_t i = 0; i < count_; i++) {
			temp[i] = array_[i];
		}
		delete[] array_;
		array_ = temp;
	}
	array_[count_++] = element;
}
template <typename T>
T stack<T>::pop() {
	if (count_ != 0) {
		return array_[--count_];
	}
	else throw logic_error("Empty stack");
}
template <typename T>
void stack<T>::swap(stack & stack_) {
	std::swap(array_size_, stack_.array_size_);
	std::swap(count_, stack_.count_);
	std::swap(array_, stack_.array_);
}
template <typename T>
stack<T>::~stack() {
	delete[] array_;
}
#endif
