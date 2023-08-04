
/*
Implement a template function called GetRefStrict that takes as input a map and a key value k. 
If the element with key k is not present in the collection, the function should throw a runtime_error exception; 
otherwise, it should return a reference to the element in the collection.
*/

#include <iostream>
#include <map>
#include <stdexcept>

using namespace std;


template<typename first,typename second, typename key>
second& GetRefStrict(map<first,second>& m,key v){
    if(m.count(v) == 0){
        throw runtime_error("Error"); 
    }

    return m[v];
}


int main(){

    map<int, string> m = {{0, "value"}};
    string& item = GetRefStrict(m, 0);
    item = "newvalue";
    cout << m[0] << endl; // выведет newvalue

    return 0;
}