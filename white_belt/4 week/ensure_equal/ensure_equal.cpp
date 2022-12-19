#include <string>
#include <exception>
#include <iostream>   
#include <sstream> 

using namespace std;

void EnsureEqual(const string& left, const string& right){
    if(left != right){
        throw runtime_error(left + " != " + right);
    }

}




