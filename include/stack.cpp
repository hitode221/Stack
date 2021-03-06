#include "Stack.h"
#ifndef STC_CPP
#define STC_CPP

template <typename T>
T* copy_array(T * array_, size_t size, size_t new_size) { //strong
	T * temp = new T[new_size];
	try {
		copy(array_, array_ + size, temp);
	}
	catch (std::exception &e) {
		delete[] temp;
		throw;
	}
	return temp;
}

template <typename T1, typename T2>
void construct(T1 * ptr, T2 const & value) {
	new(ptr) T1(value);
}

template <typename T>
void destroy(T * ptr) noexcept
{
	ptr->~T();
}

template <typename FwdIter>
void destroy(FwdIter first, FwdIter last) noexcept
{
	for (; first != last; ++first) {
		destroy(&*first);
	}
}

template <typename T>
::allocator <T>::allocator(size_t size) : array_size_(size), count_(0), array_(static_cast<T *>(size == 0 ? nullptr : operator new(size * sizeof(T)))) {}; //noexcept

template<typename T>
::allocator<T>::~allocator(){ //noexcept
	operator delete (array_);
}

template<typename T>
auto ::allocator<T>::swap(::allocator<T> & other) noexcept -> void{ //noexcept
	std::swap(allocator<T>::array_, other.array_);
	std::swap(allocator<T>::count_, other.count_);
	std::swap(allocator<T>::array_size_, other.array_size_);
};

template <typename T> 
stack<T>::stack() : ::allocator<T>() {};
template <typename T>
stack<T>::stack(stack const & stack_) : ::allocator<T>(stack_.array_size_) {
	for (size_t i = 0; i < stack_.count_; i++) {
		construct(allocator<T>::array_ + i, stack_.array_[i]);
	}
	allocator<T>::count_ = stack_.count_;
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
	return allocator<T>::count_;
}
template <typename T>
auto stack<T>::size() const noexcept -> size_t{//noexcept
	return allocator<T>::array_size_;
}
template <typename T>
auto stack<T>::push(T const & element) -> void{//strong
	if (allocator<T>::count_ == allocator<T>::array_size_) {
		size_t array_size = allocator<T>::array_size_ * 2 + (allocator<T>::array_size_ == 0);
		T* temp = static_cast<T *>(operator new (sizeof(T)*array_size));
		for (size_t i = 0; i < allocator<T>::count_; i++) {
			construct(temp + i, allocator<T>::array_[i]);
		}
		operator delete(allocator<T>::array_);
		allocator<T>::array_ = temp;
		allocator<T>::array_size_ = array_size;
	}

	construct(allocator<T>::array_ + allocator<T>::count_, element);
	++allocator<T>::count_;
}
template <typename T>
auto stack<T>::top() const throw(std::logic_error) -> T& {//strong
	if (allocator<T>::count_ != 0) {
		return allocator<T>::array_[allocator<T>::count_ - 1];
	}
	else throw std::logic_error("Empty stack");
}
template <typename T>
auto stack<T>::pop() throw(std::logic_error)  -> void{//strong
	if (allocator<T>::count_ != 0) {
		destroy(allocator<T>::array_ + allocator<T>::count_ - 1);
		--allocator<T>::count_;
	}
	else throw std::logic_error("Empty stack");
}
template <typename T>
auto stack<T>::empty() const noexcept -> bool{ //noexcept
	return (allocator<T>::count_ == 0);
}
template<typename T> 
stack<T>::~stack() {//noexcept
	destroy(allocator<T>::array_, allocator<T>::array_ + allocator<T>::count_);
}

#endif
