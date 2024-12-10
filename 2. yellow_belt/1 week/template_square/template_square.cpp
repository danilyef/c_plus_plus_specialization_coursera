#include <iostream>
#include <map>
#include <vector>
#include <utility>

using namespace std;
//-------------------------------------------------------------------------------------------------
template<typename T>
T Sqr(T x);

template<typename T>
vector<T> Sqr(const vector<T>& v);

template<typename key, typename value>
map<key, value> Sqr(const map<key, value>& m);

template<typename first, typename second>
pair<first, second> Sqr(const pair<first, second>& p);
//-------------------------------------------------------------------------------------------------


template<typename T>
T Sqr(T x){
    return x * x;
}

//-------------------------------------------------------------------------------------------------
template<typename T>
vector<T> Sqr(const vector<T>& v){
    vector<T> temp;
    for(int i = 0; i < v.size(); ++i){
        temp.push_back(Sqr(v[i]));
    }
    return temp;
}

//-------------------------------------------------------------------------------------------------
template<typename key, typename value>
map<key, value> Sqr(const map<key, value>& m){
   map<key, value> temp;
    for(auto const elem: m){
        temp[elem.first] = Sqr(elem.second);
    }
    return temp;
}

//-------------------------------------------------------------------------------------------------

template<typename first, typename second>
pair<first, second> Sqr(const pair<first, second>& p){
    return {Sqr(p.first), Sqr(p.second)};
}

//-------------------------------------------------------------------------------------------------


int main()
{
    // Пример вызова функции
    vector<int> v = { 1, 2, 3 };
   
    cout << "vector:";
   
    for (int x : Sqr(v))
    {
        cout << ' ' << x;
    }
    cout << endl;

    map<int, pair<int, int>> map_of_pairs =
    {
      {4, {2, 2}},
      {7, {4, 3}}
    };
    cout << "map of pairs:" << endl;

    for (const auto& x : Sqr(map_of_pairs))
    {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }
    return 0;
}