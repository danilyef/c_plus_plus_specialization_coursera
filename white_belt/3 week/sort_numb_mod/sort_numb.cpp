#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

/*
В стандартном потоке дана одна строка, состоящая из N + 1 целых чисел. Первым числом идёт само число N. Далее следуют ещё N чисел, обозначим их за массив A. Между собой числа разделены пробелом.
Отсортируйте массив А по модулю и выведите его в стандартный поток.
*/


auto cmp = [](int a, int b){ return abs(a) < abs(b);};

int main(){
    int N;
    cin >> N;
    vector<int> numbers;
    for(int i = 1; i <= N; ++i){
        int num;
        cin >> num;
        numbers.push_back(num);
    }
    sort(begin(numbers),end(numbers),cmp);

    for(const int& elem: numbers){
        cout << elem << " ";
    }

    return 0;
}