#pragma once
#include <stdexcept>

using std::size_t;

template <typename T>
T* copy_array(T * array_, size_t size, size_t new_size); //strong
template <typename T1, typename T2>
auto construct(T1 * ptr, T2 const & value) -> void;
template <typename T>
auto destroy(T * ptr) noexcept -> void;
template <typename FwdIter>
auto destroy(FwdIter first, FwdIter last) noexcept -> void;

template <typename T>
class allocator {
protected:
	allocator(size_t size = 0); //noexcept
	~allocator(); //noexcept
	auto swap(allocator & other) noexcept -> void; //noexcept

	allocator(allocator const &) = delete;
	auto operator =(allocator const &)->allocator & = delete;

	T * array_;
	size_t array_size_;
	size_t count_;
};

template <typename T>
class stack : private ::allocator<T> {
public:
	stack(); //noexcept	
	stack(const stack<T> & stack_); //strong
	~stack(); //noexcept
	auto operator =(stack<T> & stack_) -> stack<T> &; //strong 
	auto count() const noexcept-> size_t; //noexcept
	auto size() const noexcept-> size_t; //noexcept
	auto push(T const & element) -> void; //strong
	auto empty() const noexcept -> bool; //noexcept
	auto top()  const throw(std::logic_error) -> T&; //strong
	auto pop()  throw(std::logic_error) -> void; //strong
};

#include "stack.cpp"
