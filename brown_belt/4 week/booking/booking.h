#pragma once

#include <utility>



namespace RAII {

template <typename Provider> 
class Booking {

public:
    Booking(Provider* p, int counter) : provider_(p), counter_(counter) {};
    Booking(const Booking&) = delete;
    Booking(Booking&& other) : provider_(other.provider_), counter_(other.counter_) {
        other.provider_ = nullptr;
    }
    Booking& operator= (const Booking&) = delete;
    Booking& operator=(Booking&& other){
        std::swap(counter_,other.counter_);
        std::swap(provider_,other.provider_);
        return *this;
    };

    ~Booking(){
        if (provider_ != nullptr) {
            provider_->CancelOrComplete(*this);
        }
    };


private:
    int counter_;
    Provider* provider_;
    };



};


