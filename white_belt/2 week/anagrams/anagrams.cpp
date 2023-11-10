

/*
Anagrams detection programm
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

map<char, int> BuildCharCounters(const string& s){
    map<char,int> s_map;
    for(auto c:s){
            s_map[c] += 1;
    }
    return s_map;
}




int main(){
    // q - number of pairs to compare

    int q;
    string s1,s2;
    cin >> q;
    for(int i = 0;i<q; i++){
        cin >> s1 >> s2; 
        int warning = 0;
        map<char, int> s1_map = BuildCharCounters(s1);
        map<char, int> s2_map = BuildCharCounters(s2);

        if(s1_map == s2_map){
            cout << "YES" << endl;
        } else{
            cout << "NO" << endl;
        }
    }
    return 0;
}