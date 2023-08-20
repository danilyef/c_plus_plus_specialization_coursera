#include "sum_reverse_sort.h"
#include <algorithm>
using namespace std;


/*
You are given a header file named sum_reverse_sort.h containing declarations of three functions.
You need to submit a cpp file containing the definitions of these functions.
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




