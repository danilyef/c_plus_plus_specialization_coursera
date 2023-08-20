/*
Write a function PrintVectorPart that takes a vector of integers called numbers. 
This function should search for the first negative number in the vector and print all the numbers located to the left of it in reverse order to the standard output. 
If the vector does not contain any negative numbers, print all the numbers in reverse order.
*/


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void PrintVectorPart(const vector<int>& numbers){
    auto it = find_if(begin(numbers),end(numbers),
    [](int num){
        return num < 0;
    } );
    while(it != begin(numbers)){
        --it;
        if(*it >= 0){
            cout << *it << " "; 
        }
    }

}


int main() {
  PrintVectorPart({6, 1, 8, -5, 4});
  cout << endl;
  PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
  cout << endl;
  PrintVectorPart({6, 1, 8, 5, 4});
  cout << endl;
  return 0;
}