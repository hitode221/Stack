#pragma once
#include <stdexcept>

using namespace std; 

template <typename T>
class stack {
public:
	stack() : array_size_(0), count_(0), array_(nullptr){}
	stack(const stack<T> & stack_) : array_size_(stack_.array_size_), count_(stack_.count_) {
		array_ = new T[array_size_];
		for (size_t i = 0; i < count_; i++) {
			array_[i] = stack_.array_[i];
		}
	}
	stack<T> & operator =(stack<T> & stack_) {
		if (this != &stack_) {
			stack(stack_).swap(*this);
		}
		return *this;
	}
	size_t count() const {
		return count_;
	}
	size_t size() const {
		return array_size_;
	}
	void push(T const & element) {
		if (array_size_ == count_) {
				array_size_++;
				T * temp = new T[array_size_];
				for (size_t i = 0; i < count_; i++) {
					temp[i] = array_[i];
				}
				temp[count_] = element;
				delete[] array_;
				array_ = temp;
			}
			else {
				array_[count_] = element;
			}
		count_++;
	}
	T pop() {
		if (count_ != 0) {
			return array_[--count_];
		}
		else throw logic_error("Empty stack");
	}
	void swap(stack & stack_) {
		std::swap(array_size_, stack_.array_size_);
		std::swap(count_, stack_.count_);
		std::swap(array_, stack_.array_);
	}
	~stack() {
		delete[] array_;
	}
private:
	T * array_;
	size_t array_size_;
	size_t count_;
};
