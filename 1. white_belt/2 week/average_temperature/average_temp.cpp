#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

/*
if number in vector is bigger than average -> print index of the vector

*/
int main(){
    int n;
    int count;
    double avg;
    std::cin >> n;
    std::vector<int> temp(n);
    std::vector<int> result;

    for(int& num : temp){
        std::cin >> num; 
        avg += num;
    }

    avg /= n;


    for(int i = 0; i < temp.size();i++){
        if(temp[i]>avg){
            result.push_back(i);
            count +=1;
        }    
    }

    std::cout << result.size() << std::endl;
    for(auto ind:result){
        std::cout << ind << ' ';
    }
        

    return 0;
   

}