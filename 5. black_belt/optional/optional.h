
#include <utility>
#include <exception>
#include <iostream>

struct BadOptionalAccess {
};

template <typename T>
class Optional {
private:

  alignas(T) unsigned char data[sizeof(T)];
  bool defined = false;

public:
  Optional() = default;

  Optional(const T& elem){
    new(data) T(elem);
    defined = true;
  };

  Optional(T&& elem){
    new(data) T(std::move(elem));
    defined = true;
  };

  Optional(const Optional& other){
    if(other.HasValue()){
      new(data) T(other.Value()); 
      defined = true;
    }
   
  };

  Optional(Optional&& other){
    if(other.HasValue()){
      new(data) T(std::move(other.Value())); 
      defined = true;
    } 
  };

  Optional& operator=(const T& elem){
    if(defined){
      **this = elem;
    } else{
      new(data) T(elem);
      defined = true;
    }
    return *this;
  };
  Optional& operator=(T&& elem){
    if(defined){
      **this = std::move(elem);
    } else{
      new(data) T(std::move(elem));
      defined = true;
    }
    return *this;
  };
  Optional& operator=(const Optional& other){
    if(this == &other){
      return *this;
    }

    if((defined && other.defined)){
      defined = true;
      **this = *other;
    } else if(defined && !other.defined){
        Reset();
    } else if(!defined && other.defined){
        new(data) T(other.Value()); 
        defined = true;
    }
    return *this;
  };

  Optional& operator=(Optional&& other){
    if(defined && other.HasValue()){
      defined = true;
      **this = std::move(*other); 
    } else if(defined && !other.HasValue()){
      Reset();
    } else if((!defined && other.HasValue())){
        new(data) T(std::move(other.Value())); 
        defined = true;
    }
    return *this;
  };

  bool HasValue() const{return defined;};


  T& operator*(){
    if(!HasValue()) throw BadOptionalAccess();
    return *reinterpret_cast<T*>(data);
  };

  const T& operator*() const{
    if(!HasValue()) throw BadOptionalAccess();
    return *reinterpret_cast<const T*>(data);
  };

  T* operator->(){
    if(!HasValue()) throw BadOptionalAccess();
    return reinterpret_cast<T*>(data);
  };

  const T* operator->() const{
    if(!HasValue()) throw BadOptionalAccess();
    return reinterpret_cast<const T*>(data);
  };

  T& Value(){
     if(!HasValue()) throw BadOptionalAccess();
  return *reinterpret_cast<T*>(data);
  };

  const T& Value() const{
    if(!HasValue()) throw BadOptionalAccess();
  return *reinterpret_cast<const T*>(data);
  };

  void Reset(){
    if(HasValue()){
      defined = false;
      reinterpret_cast<T*>(data)->~T();
    }
  };

  ~Optional(){
    if(HasValue()){
      defined = false;
      reinterpret_cast<T*>(data)->~T();
    }
  };
};
