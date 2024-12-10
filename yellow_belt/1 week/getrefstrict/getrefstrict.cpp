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