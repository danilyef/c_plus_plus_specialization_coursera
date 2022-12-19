#include <iostream>
#include <vector>

int main(){
    int n;
    std::vector<int> binary_num;
    std::cin >> n;

    //successive division method

    while(n != 0){
        binary_num.push_back(n%2);
        n /=2;
    }

    for(int i = binary_num.size()-1; i >= 0; --i){
        std::cout << binary_num[i];
    }
    return 0;
}