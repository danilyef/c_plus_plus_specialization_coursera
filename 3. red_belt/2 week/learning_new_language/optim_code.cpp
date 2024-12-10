#include "test_runner.h"
#include "profile.h"

#include <algorithm>
#include <string>
#include <vector>
#include <set>
using namespace std;






class Learner {
public:
    int Learn(const vector<string>& words) {
        int newWords = 0;
        for (const auto& word : words) {
            if(dict.count(word) == 0){
                dict.insert(word);
                ++newWords;
            }
            
        }
        return newWords;
    }

    vector<string> KnownWords() {

        return vector(dict.begin(),dict.end());
    }

private:
    set<string> dict;
};


int main() {
    Learner learner;
    string line;
    while (getline(cin, line)) {
        vector<string> words;
        stringstream ss(line);
        string word;
        while (ss >> word) {
            words.push_back(word);
        }
        cout << learner.Learn(words) << "\n";
        }
    cout << "=== known words ===\n";
    for (auto word : learner.KnownWords()) {
        cout << word << "\n";
    }
}