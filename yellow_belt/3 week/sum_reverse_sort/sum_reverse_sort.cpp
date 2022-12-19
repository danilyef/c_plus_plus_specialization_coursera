#include <string>
#include <vector>
#include "sum_reverse_sort.h"
#include <algorithm>
using namespace std;


/* 
Вам дан заголовочный файл sum_reverse_sort.h, содержащий объявления трёх функций.
Вам надо прислать cpp-файл, содержащий определения этих функций.
*/

int Sum(int x, int y){
    return x+y;
}


string Reverse(string s){
    reverse(s.begin(),s.end());
}


void Sort(vector<int>& nums){
    sort(nums.begin(),nums.end());
}




