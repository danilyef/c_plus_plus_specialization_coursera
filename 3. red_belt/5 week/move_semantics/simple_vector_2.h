#pragma once
#include <cstdlib>
#include <algorithm>
using namespace std;

// Реализуйте SimpleVector в этом файле
// и отправьте его на проверку

template <typename T>
class SimpleVector {
public:
	SimpleVector() = default;
	explicit SimpleVector(size_t size) : data(new T[size]), end_(data + size), capacity(size), size(size) {};
	SimpleVector(const SimpleVector<T>& other) : data(new T[other.capacity]), size(other.size), capacity(other.capacity) {
		copy(other.begin(). other.end(), begin()); 
	};
	SimpleVector(SimpleVector<T>&& other) : data(other.data), size(other.size), capacity(other.capacity) {
		other.data = nullptr;
		other.size = other.capacity = 0; 
	};

	~SimpleVector(){
		delete[] data;
	};


	void operator=(SimpleVector&& other){
		delete[] data;
		data = other.data;
		size = other.size;
		capacity = other.capacity;
		other.data = nullptr;
		other.size = other.capacity = 0;
	};


	void operator=(const SimpleVector& other){
		size_t new_size = other.size;
		size_t new_capacity = other.capacity;
		T* new_data =  new T[other.capacity];
		copy(other.begin(),other.end(),new_data);

		delete[] data;
		size = new_size;
		capacity = new_capacity;
		data = new_data;
		end_ = new_data + size;
	};


	T& operator[](size_t index){
		return data[index];
	};

	T* begin() { return data; } 
	T* end() { return end_; }
	const T* begin() const { return data; }
	const T* end() const { return end_; }

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
		end_ = data + size;
	};

	void PushBack(T&& value){    
		if(Size() == Capacity()){
			capacity = capacity == 0 ? 1 : 2 * capacity;

			T* data_temp = new T[capacity];
			move(begin(),end(),data_temp);
			delete[] data;
			data = data_temp;
		}
		data[size++] = std::move(value);
		end_ = data + size;
	};
private:

	T* data = nullptr; 
	T* end_ = nullptr;
	size_t size = 0;
	size_t capacity = 0;

};
