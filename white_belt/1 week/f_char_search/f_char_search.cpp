#include <iostream>
#include <string>


int main(){
    std::string str;
    int count = 0; 
    std::cin >> str;

    for (int i = 0; i < str.size(); ++i){
        if (str[i] == 'f') {
            count += 1;
        } 

        if (count == 2){
            std::cout << i;
            break;
        }

    }

    if(count == 0){
        std::cout << -2;
    } else if (count == 1){
        std::cout << -1;
    }
    
    return 0;

}