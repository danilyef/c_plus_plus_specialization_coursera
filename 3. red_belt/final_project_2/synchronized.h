#pragma once

#include <mutex>
using namespace std;

template <typename T>
class Synchronized {
public:
	explicit Synchronized(T initial = T()): value(std::move(initial)){};

	struct Access {
		Access(T& value,mutex& m): ref_to_value(value), lock(m){};
		~Access(){};
		T& ref_to_value;
		lock_guard<mutex> lock;
	};

	Access GetAccess(){
		return {value,m};
	};
	
private:
	T value;
	mutex m;
};