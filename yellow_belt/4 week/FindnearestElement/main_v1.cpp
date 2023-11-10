/*
Write a function called SplitIntoWords that splits a string into words using spaces.

You can be sure that:

The string is not empty.
The string only consists of Latin letters and spaces.
The first and last characters of the string are not spaces.
The string does not contain two consecutive spaces.
*/


#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

vector<string> SplitIntoWords(const string& s){
    vector<string> res;
    string temp;
    for(auto it = s.begin(); it != s.end(); ++it){
        if(*it != ' '){
            temp += *it;
        } else{
            res.push_back(temp);
            temp.clear();
        }
    }
    res.push_back(temp);

    return res;
}


int main() {
  string s = "C Cpp Java Python";

  vector<string> words = SplitIntoWords(s);
  cout << words.size() << " ";
  for (auto it = begin(words); it != end(words); ++it) {
    if (it != begin(words)) {
      cout << "/";
    }
    cout << *it;
  }
  cout << endl;
  
  return 0;
}