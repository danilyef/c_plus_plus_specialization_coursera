

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

using namespace std;

int main(){

    vector<int> temp;
    vector<int> above_avg;
    int N;
    int64_t sum = 0;
    int64_t avg_t;

    /* add temperatures into the vector*/
    cin >> N;
    for(int i = 0; i < N; ++i){
        int t;
        cin >> t;
        sum += t;
        temp.push_back(t);
    }
    /* calculate average of the vecor of temperatures */
    avg_t = sum / N;

    /* find number which are larger than average temperature and save it index*/
    for(int i = 0; i < N; ++i){
        if(temp[i] > avg_t){
            above_avg.push_back(i);
        }
    }
    /* Print numbers which are larger than average temperature */
    cout << above_avg.size() << endl;
    for (int num:above_avg){
        cout << num << " ";
    }


    return 0;
}