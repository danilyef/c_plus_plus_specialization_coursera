#include <iostream>

int Factorial(int x){
    if(x <= 1){
        return 1;
    } else{
        for(int i = x - 1; i > 0; --i){
            x *= i;
        }
    }
    return x;
}


int main(){
    int num;
    std::cin >> num;
    std::cout << Factorial(num);
    return 0;
}