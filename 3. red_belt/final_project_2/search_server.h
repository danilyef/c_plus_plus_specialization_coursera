#pragma once

#include "synchronized.h"
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
#include <future>
#include <mutex>
#include <thread>
#include <deque>
#include <string_view>
using namespace std;

class InvertedIndex {
public:
  InvertedIndex();
  explicit InvertedIndex(istream& document_input);
  vector<pair<size_t,size_t>> Lookup(string_view word) const;

  const size_t Size(){
    return index.size();
  }
  const deque<string>& GetDocuments() const {
    return docs;
  }

private:
  unordered_map<string_view, vector<pair<size_t,size_t>>> index;
  size_t doc_size;
  deque<string> docs;
};

class SearchServer {
public:
  SearchServer() = default;
  explicit SearchServer(istream& document_input) : index(InvertedIndex(document_input)){};
  void UpdateDocumentBase(istream& document_input);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);
private:
  Synchronized<InvertedIndex> index;
  vector<future<void>> futures;
};
