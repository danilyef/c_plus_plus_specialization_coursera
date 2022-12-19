#include <iostream>
#include <cstdint>
#include <limits>
#include <tuple>
#include <map>
#include <vector>
#include <utility>
#include <exception>
/*
Задание по программированию: Ссылка на элемент
Реализуйте шаблонную функцию GetRefStrict, которая на вход принимает: map и значение ключа k. Если элемент по ключу k в коллекции отсутствует, то функция должна бросить исключение runtime_error, иначе вернуть ссылку на элемент в коллекции.

Пример использования функции
*/

using namespace std;


template<typename Key, typename Value>
Value& GetRefStrict(map<Key,Value>& m,Key k){
    if(m.count(k) == 0){
        throw runtime_error("Element does not exist in map");
    }
    return m.at(k);

}



int main(){ 

    map<int, string> m = {{0, "value"}};
    string& item = GetRefStrict(m, 0);
    item = "newvalue";
    cout << m[0] << endl; // выведет newvalue


    return 0;
}