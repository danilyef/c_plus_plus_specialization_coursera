#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> Reversed(const std::vector<int>& v){
    std::vector<int> res;
    for(int i = v.size() -1; i>=0;i--){
        res.push_back(v[i]);
    }
    return res;
}
    


int main(){
    std::vector<int> v = {1,6,2,5};
    std::vector<int> res;
    res = Reversed(v);

    for(int i = 0;i< res.size();i++){
        std::cout << res[i];
    }

}