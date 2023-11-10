
/*
Block Mass
Calculate the total mass of rectangular parallelepiped concrete blocks of the same density but different sizes.

Instructions:
Assume that the dimensions of the blocks are measured in centimeters, the density is in grams per cubic centimeter, and the total mass is in grams. Therefore, the mass of each block can be computed as a simple product of the density and volume.

Input Format:
The first line contains two positive integers: N (the number of blocks) and R (the density of each block). Each of the following N lines contains three positive integers: W, H, D — the dimensions of each respective block.

Guarantees:

The number of blocks N does not exceed 10^5.
The density of blocks R does not exceed 100.
The dimensions of blocks W, H, D do not exceed 10^4.
Example:
Input
2 14
1 2 3
30 40 50

Output
840084
*/

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

using namespace std;

int main(){
    int N;
    u_int16_t R;
    u_int64_t W,H,D;

    u_int64_t overall_mass = 0;

    cin >> N >> R;

    for(int i = 0; i < N;++i){
        cin >> W >> H >> D;
        overall_mass += (R * W * H * D);
    }

    cout << overall_mass;

    return 0;
}