#pragma once

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
  SimpleVector() = default;
  
  explicit SimpleVector(size_t size) : data(new T[size]), end_(data + size), capacity(size), size(size) {};

  ~SimpleVector(){
    delete[] data;
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

private:
  T* data = nullptr; 
  T* end_ = nullptr;
  size_t size = 0;
  size_t capacity = 0;
};







/*
void PushBack(const T& value){

    T* data_temp;
    if(Size() == Capacity()){
      if(Capacity() == 0){
        T* data_temp = new T[1];
        capacity = 1;
      } else{
        T* data_temp = new T[2 * Capacity()];
        capacity = 2 * Capacity();
      }
      
      for(int i = 0; i < last_elem; ++i){
        data_temp[i] = data[i];
      }
      delete[] data;
      T* data = data_temp;
      T* end_ = data + last_elem;
    }

    data[last_elem + 1] = value;
    last_elem +=1;
    capacity = 2 * capacity;


  };


*/