#include <iostream>
#include <vector> 
#include <cstdint>

using namespace std;


int64_t avg_temp(const vector<int>& v){
    int64_t sum = 0;
    for(int elem:v){
        sum += elem;
    }
    int64_t avg = sum / static_cast<int64_t>(v.size());
    return avg;
}

int main(){
    int N;
    vector<int> temp;
    vector<int> above_avg;
    cin >> N;
    for(int i = 0; i< N; ++i){
        int temp_day;
        cin >> temp_day;
        temp.push_back(temp_day);
    }

    int64_t avg_t = avg_temp(temp);

    for(int i = 0; i < static_cast<int>(temp.size()); ++i){
        if(temp[i] > avg_t){
            above_avg.push_back(i);
        }
    }

    cout << above_avg.size() << endl;
    for(int elem:above_avg){
        cout << elem << " ";
    }


    return 0;
}