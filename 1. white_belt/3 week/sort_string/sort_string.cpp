#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;




auto cmp = [](const string& a,const string& b){ 
    string new_a = "";
    string new_b = "";
    
    for(char& c:a){
        new_a += tolower(c);
    }

    for(char& c:b){
        new_b += tolower(c);
    }
    
    return new_a < new_b;
    };

int main(){
    int n;
    cin >> n;
    vector<string> v(n);
    for (string& x : v) {
        cin >> x;
    }
    sort(begin(v),end(v),cmp);

    for(const string& elem: v){
        cout << elem << " ";
    }

    return 0;
}