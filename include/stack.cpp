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
::allocator <T>::allocator(size_t size) : array_size_(size), count_(0), array_(new T[size]) {}; //noexcept

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
	::allocator<T>::array_ = copy_array(stack_.array_, stack_.count_, stack_.array_size_);
	::allocator<T>::array_size_ = stack_.array_size_;
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
	return ::allocator<T>::count_;
}
template <typename T>
auto stack<T>::size() const noexcept -> size_t{//noexcept
	return ::allocator<T>::array_size_;
}
template <typename T>
auto stack<T>::push(T const & element) -> void{//strong
	if (::allocator<T>::array_size_ == ::allocator<T>::count_) {
		size_t size = ::allocator<T>::array_size_ * 2 + (::allocator<T>::array_size_ == 0);
		T * temp = copy_array(::allocator<T>::array_, ::allocator<T>::count_, size);
		delete[] ::allocator<T>::array_;
		::allocator<T>::array_size_ = size;
		::allocator<T>::array_ = temp;
	}
	::allocator<T>::array_[::allocator<T>::count_] = element;
	++::allocator<T>::count_;
}
template <typename T>
auto stack<T>::top() const throw(logic_error) -> T& {//strong
	if (::allocator<T>::count_ != 0) {
		return ::allocator<T>::array_[::allocator<T>::count_ - 1];
	}
	else throw logic_error("Empty stack");
}
template <typename T>
auto stack<T>::pop() throw(logic_error)  -> void{//strong
	if (::allocator<T>::count_ != 0) {
		--::allocator<T>::count_;
	}
	else throw logic_error("Empty stack");
}
template <typename T>
auto stack<T>::empty() const noexcept -> bool{ //noexcept
	return (::allocator<T>::count_ == 0);
}

#endif
