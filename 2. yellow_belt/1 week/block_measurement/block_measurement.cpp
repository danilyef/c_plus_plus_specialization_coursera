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