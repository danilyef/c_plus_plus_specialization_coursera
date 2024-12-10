#include <iostream>
#include <set>
#include <string>

using namespace std;
/*
Дан набор строк. Найдите количество уникальных строк в этом наборе.
*/

int main(){
    int N;
    set<string> str;
    cin >> N;

    for(int i = 0;i< N;i++){
        string s;
        cin >> s;
        str.insert(s);
    }

    cout << str.size();
    return 0;
}