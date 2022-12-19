#include <iostream>
#include <string>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

/*
Два слова называются синонимами друг друга, если они имеют похожие значения. Реализуйте следующие операции над словарём синонимов:

ADD word1 word2 — добавить в словарь пару синонимов (word1, word2).
COUNT word — узнать количество синонимов слова word.
CHECK word1 word2 — проверить, являются ли слова word1 и word2 синонимами. Слова word1 и word2 считаются синонимами, если среди запросов ADD был хотя бы один запрос ADD word1 word2 или ADD word2 word1.
*/

void add(set< set<string> >& s,map<string,int>& c,const string& w1,const string& w2){
    set<string> str = {w1,w2};
    if(s.count(str) == 0){
        s.insert(str);
        c[w1] +=1;
        c[w2] +=1;
    }  
}

void count(map<string,int>& c,const string& w){
    if(c.count(w) == 0){
        cout << 0 << endl;
    } else{
        cout << c[w] << endl;
    }   
}

void check(const set< set<string> >& s,const string& w1,const string& w2){
    set<string> check = {w1,w2};
    if(s.count(check) > 0){
        cout << "YES" << endl;
    } else{
        cout << "NO" << endl;
    }
    
}

int main(){
    set< set<string> > synonyms;
    map<string,int> counts; 
    int Q;
    cin >> Q;
    for(int i = 0; i<Q; i++){
        string operation;
        cin >> operation;
        if(operation == "ADD"){
            string word1,word2;
            cin >> word1 >> word2;
            add(synonyms,counts,word1,word2);
        } else if(operation == "COUNT"){
            string word;
            cin >> word;
            count(counts,word);

        } else if(operation == "CHECK"){
            string word1,word2;
            cin >> word1 >> word2;
            check(synonyms,word1,word2);
        }
    }

    return 0;
}