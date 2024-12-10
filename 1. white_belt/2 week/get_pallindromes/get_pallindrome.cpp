#include <string>
#include <iostream>
#include <vector>


bool IsPalindrom(std::string word){
   
    for(int i = 0;i < word.size()/2;++i){
        if(word[i] != word[word.size() - (i+1)]){
            return false;
        }
    }
    return true;
}

std::vector<std::string> PalindromFilter(std::vector<std::string> words,int minLength){
    std::vector<std::string> palindromes;
    for(auto word: words){

        if(IsPalindrom(word) == true && word.size() >= minLength){
            palindromes.push_back(word);
        }
    }

    return palindromes;
}


int main(){
    std::vector<std::string> words= {"abacaba", "aba", "code"};
    std::vector<std::string> pal;
    pal = PalindromFilter(words,5);
    for(auto w:pal){
        std::cout << w << std::endl;
    }
    return 0;
}
