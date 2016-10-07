#include "Stack.h"
#ifndef STC_CPP
#define STC_CPP

template <typename T>
T* copy_array(T * array_, size_t size, size_t new_size) { //strong
	T * temp = new T[new_size];
	try {
		copy(array_, array_ + size, temp);
	}
	catch (exception &e) {
		delete[] temp;
		throw;
	}
	return temp;
}

template <typename T>
::allocator <T>::allocator(size_t size = 0) : array_size_(size), count_(0), array_(operator new (size*sizeof(T))) {}; //noexcept

template<typename T>
::allocator<T>::~allocator(){ //noexcept
	delete[] array_;
}

template<typename T>
auto ::allocator<T>::swap(allocator & other) noexcept -> void{ //noexcept
	std::swap(array_, other.array_);
	std::swap(count_, other.count_);
	std::swap(array_size_, other.array_size_);
};

template <typename T> 
stack<T>::stack() : ::allocator<T>() {};

template <typename T>
stack<T>::stack(stack const & stack_) : ::allocator<T>(stack_.count_) {
	ptr_ = copy_array(stack_.ptr_, stack_.count_, stack_.size_);
	size_ = stack_.size_;
}

template <typename T>
auto stack<T> :: operator =(stack<T> & stack_)->stack<T> &{ //strong 
	if (this != &stack_) {
		stack(stack_).swap(*this);
	}
	return *this;
}
template <typename T>
auto stack<T>::count() const  noexcept -> size_t{//noexcept
	return count_;
}
template <typename T>
auto stack<T>::size() const noexcept -> size_t{//noexcept
	return array_size_;
}
template <typename T>
auto stack<T>::push(T const & element) -> void{//strong
	if (array_size_ == count_) {
		size_t size = array_size_ * 2 + (array_size_ == 0);
		T * temp = copy_array(array_, count_, size);
		delete[] array_;
		array_size_ = size;
		array_ = temp;
	}
	array_[count_] = element;
	++count_;
}
template <typename T>
auto stack<T>::top() const throw(logic_error) -> T& {//strong
	if (count_ != 0) {
		return array_[count_ - 1];
	}
	else throw logic_error("Empty stack");
}
template <typename T>
auto stack<T>::pop() throw(logic_error)  -> void{//strong
	if (count_ != 0) {
		--count_;
	}
	else throw logic_error("Empty stack");
}
template <typename T>
auto stack<T>::empty() const noexcept -> bool{ //noexcept
	return (count_ == 0);
}

#endif
