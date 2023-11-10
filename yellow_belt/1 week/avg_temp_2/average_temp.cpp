
/*
Given temperature values observed over N consecutive days, find the days' indices (starting from zero) with temperatures higher than the arithmetic mean for all N days.

It is guaranteed that the arithmetic mean of the temperature values is an integer.

Input Format:
The input consists of an integer N, followed by N integers representing the temperature values on the 0th, 1st, ..., (N-1)th day. N is guaranteed not to exceed one million (10^6), and the temperature values, measured in millionths of a degree Celsius, range from -10^8 to 10^8. There is no need to validate these constraints; you can assume appropriate variable types based on them.

Output Format:
The output consists of the first number K, which is the count of days with temperatures higher than the arithmetic mean. After that, K integers represent the indices of these days.
*/

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