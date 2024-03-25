#pragma once

#include <stdexcept>
#include <array>
#include <iostream>

using namespace std;

template <typename T, size_t N>
class StackVector {
public:
	explicit StackVector(size_t a_size = 0) :  capacity(N), size(a_size) {
		if(a_size > N){
			throw std::invalid_argument("Size cannot be bigger than capacity!");
		}
		array <T, N> stack_vector;
	};

	T& operator[](size_t index){
		return stack_vector[index];
	};
	
	const T& operator[](size_t index) const{
		return stack_vector[index];
	};

	auto begin(){
		return stack_vector.begin();
	};
	
	auto end(){
		return stack_vector.begin() + size;
	};
	
	auto begin() const{
		return stack_vector.begin();
	};
	
	auto end() const {
		return stack_vector.begin() + size;
	};

	size_t Size() const{
		return size;
	};
	size_t Capacity() const{
		return capacity;
	};

	void PushBack(const T& value){
		if(size == capacity){
			throw std::overflow_error("Array is already full");
		}
		stack_vector[size] = value;
		++size;
	};

	T PopBack(){
		if(size == 0){
			throw std::underflow_error("Array is already empty");
		}
		auto last_elem = stack_vector.begin() + (size - 1);
		--size;
		return *last_elem;
	};

private:
	size_t capacity;
	size_t size;
	array <T, N> stack_vector;

	};

