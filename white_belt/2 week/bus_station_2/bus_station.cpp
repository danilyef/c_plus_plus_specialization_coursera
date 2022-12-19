
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

void NumerationRoute(map<vector<string>, int>& r, const int& n){
    vector<string> s(n);
    for(int i = 0; i<n;i++){
        string stop;
        cin >> stop;
        s.push_back(stop);
    }
    if(r.count(s) == 0){
        int index = r.size() + 1;
        r[s] = index;
        cout << "New bus " << to_string(index) << endl;
    } else{
        int index = r[s];
        cout << "Already exists for " << to_string(index) << endl;
    }
    
}

int main(){
    int Q;

    cin >> Q;
    map<vector<string>, int> route;
    for(int i = 0; i< Q; i++){
        int N;
        cin >> N;
        NumerationRoute(route, N);
    }

    return 0;
}





