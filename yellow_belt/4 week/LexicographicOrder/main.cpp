/*
Given a positive integer N, not exceeding 9, output all permutations of numbers from 1 to N in reverse lexicographical order (see example).
*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>

using namespace std;


int main() {
    int N;
    cin >> N;
    int permutations = 1;
    vector<vector<int>> combinations;
    vector<int> num;
    
    for (int i = 0; i < N; ++i) {
        num.push_back(i + 1);
        permutations *= (i + 1);
    }
    for (int i = 0; i < permutations; ++i) {
        next_permutation(num.begin(), num.end());
        combinations.push_back(num);
    }

    sort(combinations.begin(), combinations.end(),
         [](const vector<int> &a, const vector<int> &b){
             return lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
         });

    for (auto it = combinations.rbegin(); it != combinations.rend(); ++it) {
        for (int &n: *it ) {
            cout << n << " ";
        }
        cout << endl;
    }

    return 0;
}


/*
int main() {
    int N;
    cin >> N;
    
    vector<int> nums(N);
    for (int i = 0; i < N; ++i) {
        nums[i] = N - i;
    }

    do {
        for (int num : nums) {
            cout << num << " ";
        }
        cout << endl;
    } while (prev_permutation(nums.begin(), nums.end()));

    return 0;
}
*/