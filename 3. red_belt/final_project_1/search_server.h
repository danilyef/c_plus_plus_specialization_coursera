#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <functional>
using namespace std;

class InvertedIndex {
public:
  InvertedIndex();
  void Add(const string& document);
  vector<pair<size_t,size_t>> Lookup(const string& word) const;

  const size_t Size(){
    return index.size();
  }

private:
  unordered_map<string, vector<pair<size_t,size_t>>> index;
  size_t doc_size;
};

class SearchServer {
public:
  SearchServer() = default;
  explicit SearchServer(istream& document_input);
  void UpdateDocumentBase(istream& document_input);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);
  //////////////
  vector<string> SplitWords(istream& query_input, ostream& search_results_output);
  vector<pair<size_t, size_t>> ManyLookups(const vector<string> words);
  void SortResults(vector<pair<size_t, size_t>> search_results);
  void PrintResults(vector<pair<size_t, size_t>> search_results,ostream& search_results_output);

private:
  InvertedIndex index;
};
