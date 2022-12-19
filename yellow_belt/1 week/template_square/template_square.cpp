#include <iostream>
#include <cstdint>
#include <limits>
#include <tuple>
#include <map>
#include <vector>
#include <utility>
#include <exception>
/*
Реализуйте шаблонную функцию Sqr, которая работает не только для чисел, но и для контейнеров. Функция должна возвращать копию исходного контейнера, модифицировав его следующим образом:
для vector элементы нужно возвести в квадрат;
для map в квадрат нужно возвести только значения, но не ключи;
для pair в квадрат нужно возвести каждый элемент пары.
*/


using namespace std;

template<typename T> T Sqr(T x);
template<typename T> vector<T> Sqr(const vector<T>& vec);
template<typename T> vector<T> Sqr(const vector<T>& vec);
template<typename First, typename Second> pair<First,Second> Sqr(const pair<First,Second>& p);
template<typename Key, typename Value> map<Key,Value> Sqr(const map<Key,Value>& m);

/* Basic function */
template<typename T>
T Sqr(T x){
    return x * x;
}

/* Vectors Sqr*/
template<typename T>
vector<T> Sqr(const vector<T>& vec){
    vector<T> result;
    for(T elem:vec){
        result.push_back(Sqr(elem));
    }
    return result;
}

template <typename First,typename Second>
pair<First,Second> Sqr(const pair<First,Second>& p){
    return make_pair(Sqr(p.first),Sqr(p.second));
}



template <typename Key,typename Value>
map<Key,Value> Sqr(map<Key,Value>& m){
    map<Key,Value> res;
    for(auto elem:m){
        res[elem.first] = Sqr(elem.second);
    }
    return res;
}

int main(){
map<int, pair<int, int>> map_of_pairs = {
  {4, {2, 2}},
  {7, {4, 3}}
};
cout << "map of pairs:" << endl;
for (const auto& x : Sqr(map_of_pairs)) {
  cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
}

    return 0;
}