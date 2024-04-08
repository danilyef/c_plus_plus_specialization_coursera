#include "test_runner.h"

#include <vector>
#include <utility>

using namespace std;


template <typename Token>
using Sentence = vector<Token>;

template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
    vector<Sentence<Token>> sentences;
	bool end_sent_prev = false;
	sentences.push_back(Sentence<Token>());
	
	for(auto& token: tokens){
        bool end_sent = token.IsEndSentencePunctuation();
		if(end_sent){
            sentences[sentences.size() - 1].push_back(std::move(token));
			end_sent_prev = true;
        } else{
			if(end_sent_prev){
				sentences.push_back(Sentence<Token>());
				sentences[sentences.size() - 1].push_back(std::move(token));
				end_sent_prev = false;
			} else{
				sentences[sentences.size() - 1].push_back(std::move(token));
			}
		}
    }
    return sentences;
}


struct TestToken {
    string data;
    bool is_end_sentence_punctuation = false;

    bool IsEndSentencePunctuation() const {
    return is_end_sentence_punctuation;
    }
    bool operator==(const TestToken& other) const {
    return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
    }
};

ostream& operator<<(ostream& stream, const TestToken& token) {
    return stream << token.data;
}


void TestSplitting() {

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!"}}
    })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}}
    })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
        {{"Without"}, {"copies"}, {".", true}},
    })
  );

}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSplitting);
  return 0;
}
