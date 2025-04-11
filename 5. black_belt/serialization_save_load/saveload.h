#include <map>
#include <iostream>
#include <string>
#include <vector>

// Serialization

template <typename T>
void Serialize(T pod, std::ostream& out);

void Serialize(const std::string& str, std::ostream& out);

template <typename T>
void Serialize(const std::vector<T>& data, std::ostream& out);

template <typename T1, typename T2>
void Serialize(const std::map<T1, T2>& data, std::ostream& out);


// Deserialization

template <typename T>
void Deserialize(std::istream& in, T& pod);

void Deserialize(std::istream& in, std::string& str);

template <typename T>
void Deserialize(std::istream& in, std::vector<T>& data);

template <typename T1, typename T2>
void Deserialize(std::istream& in, std::map<T1, T2>& data);




//Serialization implementation
template <typename T>
void Serialize(T pod, std::ostream& out){
    out.write(reinterpret_cast<const char*>(&pod), sizeof(pod));
}

void Serialize(const std::string& str, std::ostream& out){
    size_t size = str.size();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    out.write(str.data(), str.size());
}

template <typename T>
void Serialize(const std::vector<T>& data, std::ostream& out){
    size_t size = data.size();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    for(size_t i = 0; i < data.size(); ++i){
        Serialize(data[i],out);
    }
}


template <typename T1, typename T2>
void Serialize(const std::map<T1, T2>& data, std::ostream& out){
    size_t size = data.size(); 
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    for(auto const& [key, val]: data){
        Serialize(key, out);
        Serialize(val, out);
    }
}


// Deserialization implementation
template <typename T>
void Deserialize(std::istream& in, T& pod){
    in.read(reinterpret_cast<char*>(&pod), sizeof(pod));
};

void Deserialize(std::istream& in, std::string& str){
    size_t size;
    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    str.resize(size);
    in.read(str.data(), size);
    
};

template <typename T>
void Deserialize(std::istream& in, std::vector<T>& data){
    size_t size_v;
    in.read(reinterpret_cast<char*>(&size_v), sizeof(size_v));
    data.resize(size_v);
    for (size_t i = 0; i< size_v ; ++i){
        Deserialize(in, data[i]);
    }

};

template <typename T1, typename T2>
void Deserialize(std::istream& in, std::map<T1, T2>& data){
    size_t size_m;
    in.read(reinterpret_cast<char*>(&size_m), sizeof(size_m));
    data.clear();
    for (size_t i = 0; i< size_m ; ++i){
        T1 tmp_k;
        T2 tmp_v;
        
        Deserialize(in, tmp_k);
        Deserialize(in, tmp_v);

        data[tmp_k] = tmp_v;

    }

};