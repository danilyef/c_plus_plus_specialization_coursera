#include "test_runner.h"
#include <map>
#include <set>
#include <string>
#include <future>
#include <functional>
#include <sstream>
using namespace std;


std::vector<std::string> StringSplit(const std::string& line, char delimiter){
   std::vector<std::string> words;
   std::stringstream ss(line);
   std::string word;
   while (getline (ss, word, delimiter)) {
        words.push_back(word);
    }
    return words;
};

struct Stats {
    map<string, int> word_frequences;
    void operator+= (const Stats& other){
        for (const auto& pair : other.word_frequences) {
            word_frequences[pair.first] += pair.second;
        }
    };
};

Stats ExploreLine(const set<string>& key_words, const string& line) {
    Stats result;
    std::vector<std::string> words = StringSplit(line,' ');
    for(auto word: words){
        if(key_words.count(word)>0){
            result.word_frequences[word]++;
        }
    }
    return result;
}

Stats ExploreMultipleLines(const set<string>& key_words, const vector<string>& lines) {
    Stats result;
    for(auto& line: lines){
       result += ExploreLine(key_words, line);
    }
    return result;
}


Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
    int i = 0;
    int num_threads = 4;
    vector<vector<string>> threads(num_threads);    
    for (string line; getline(input, line);){
        threads[i++ % num_threads].push_back(std::move(line));
    }


    vector<future<Stats>> futures;
    for(auto& thread: threads){
        futures.push_back(async(ExploreMultipleLines, ref(key_words),ref(thread)));
    }

    Stats result;
    for (auto& f : futures) {
        result += f.get();
    }
    return result;

}
   


void TestBasic() {
    const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

    stringstream ss;
    ss << "this new yangle service really rocks\n";
    ss << "It sucks when yangle isn't available\n";
    ss << "10 reasons why yangle is the best IT company\n";
    ss << "yangle rocks others suck\n";
    ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

    const auto stats = ExploreKeyWords(key_words, ss);
    const map<string, int> expected = {
        {"yangle", 6},
        {"rocks", 2},
        {"sucks", 1}
    };
    ASSERT_EQUAL(stats.word_frequences, expected);
    }

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestBasic);
}
