#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

void Reverse(std::vector<int>& v){
    int n = v.size();  
    for (int i = 0; i < n / 2; ++i) {
        int tmp = v[i];
        v[i] = v[n - 1 - i];
        v[n - 1 - i] = tmp;
        }
    }


int main(){
    std::vector<int> v = {1,6,2,5};
    Reverse(v);

}