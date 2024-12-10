#pragma once

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;


template <typename T>
class SimpleVector {
public:
	SimpleVector() = default;

	explicit SimpleVector(size_t size) : data(new T[size]), capacity(size), size(size) {};
	
	SimpleVector(const SimpleVector<T>& other) : data(new T[other.capacity]), size(other.size), capacity(other.capacity) {
		copy(other.begin(), other.end(), begin()); 
	};


	void operator = (const SimpleVector& other) {
    if (other.size <= capacity) {
      copy(other.begin(), other.end(), begin());
      size = other.size;
    } else {
	  //copy-swap idiom
      SimpleVector<T> tmp(other);
      swap(tmp.data, data);
      swap(tmp.size, size);
      swap(tmp.capacity, capacity);
    }
  }


	~SimpleVector(){
		delete[] data;
	};

	SimpleVector(SimpleVector<T>&& other) : data(other.data), size(other.size), capacity(other.capacity) {
		other.data = nullptr;
		other.size = other.capacity = 0; 
	};

	void operator=(SimpleVector&& other){
		delete[] data;
		data = other.data;
		size = other.size;
		capacity = other.capacity;
		other.data = nullptr;
		other.size = other.capacity = 0;
	};

	T& operator[](size_t index){
		return data[index];
	};

	T* begin() { return data; } 
	T* end() { return data + size; }
	const T* begin() const { return data; }
	const T* end() const { return data + size; }

	size_t Size() const{
		return size;
	};

	size_t Capacity() const{
		return capacity;
	};

	void PushBack(const T& value){    
		if(Size() == Capacity()){
			capacity = capacity == 0 ? 1 : 2 * capacity;

			T* data_temp = new T[capacity];
			copy(begin(),end(),data_temp);
			delete[] data;
			data = data_temp;
		}
		data[size++] = value;
		};

private:
  T* data = nullptr; 
  size_t size = 0;
  size_t capacity = 0;
};







