#include <iostream>
#include <string>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

/*
В этой задаче вам нужно присваивать номера автобусным маршрутам.
А именно, для каждого маршрута, заданного множеством названий остановок, нужно либо выдать новый номер (первому маршруту — 1, второму — 2 и т. д.), 
либо вернуть номер существующего маршрута, которому соответствует такое множество остановок.
В отличие от задачи «Автобусные остановки — 2», наборы остановок, которые можно получить друг из друга перестановкой элементов или добавлением/удалением повторяющихся, следует считать одинаковыми.  


*/

void NumerationRoute(map<set<string>, int>& r, const int& n){
    set<string> s;
    for(int i = 0; i<n;i++){
        string stop;
        cin >> stop;
        s.insert(stop);
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
    map<set<string>, int> route;
    for(int i = 0; i< Q; i++){
        int N;
        cin >> N;
        NumerationRoute(route, N);
    }

    return 0;
}





