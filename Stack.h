#pragma once
#include <stdexcept>

using namespace std; 

template <typename T>
class stack {
public:
	stack() : array_size_(0), count_(0), array_(nullptr){}
	size_t count() const {
		return count_;
	}
	size_t size() const {
		return array_size_;
	}
	void push(T const & element) {
		count_++;
		if (array_size_ == 0) {
			array_size_++;
			array_ = new T[array_size_];
			array_[count_ - 1] = element;

		}
		else {
			if (array_size_ < count_) {
				array_size_++;
				T * temp = new T[array_size_];
				for (size_t i = 0; i < count_ - 1; i++) {
					temp[i] = array_[i];
				}
				temp[count_ - 1] = element;
				delete[] array_;
				array_ = new T[array_size_];
				for (size_t i = 0; i < count_; i++) {
					array_[i] = temp[i];
				}
				delete[] temp;
			}
			else {
				array_[count_ - 1] = element;
			}
		}
	}
	T pop() {
		if (count_ != 0) {
			return array_[--count_];
		}
		else throw logic_error("Empty stack");
	}
	~stack() {
		if (array_size_ != 0) delete[] array_;
	}
private:
	T * array_;
	size_t array_size_;
	size_t count_;
};
