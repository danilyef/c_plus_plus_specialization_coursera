#include <iostream>
#include <cstdint>
#include <limits>
using namespace std;


/*
Вычислите суммарную массу имеющих форму прямоугольного параллелепипеда бетонных блоков одинаковой плотности, но разного размера.
*/


int main(){

    int N,R,W,H,D;
    uint64_t sum = 0;
    cin >> N >> R;
    for(int i = 0; i < N ; ++i){
        cin >> W >> H >> D;
        sum += static_cast<uint64_t>(W) * H * D;
    }

    cout << sum * R << endl;

    return 0;
}

