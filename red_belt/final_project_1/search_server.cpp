#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <numeric>
#include "profile.h"

vector<string> SplitIntoWords(const string& line) {
  istringstream words_input(line);
  return {istream_iterator<string>(words_input), istream_iterator<string>()};
}


SearchServer::SearchServer(istream& document_input) {
  UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
  InvertedIndex new_index;

  for (string current_document; getline(document_input, current_document); ) {
    new_index.Add(std::move(current_document));
  }

  index = std::move(new_index);
}

void SearchServer::AddQueriesStream(
  istream& query_input, ostream& search_results_output
) {
  
  vector<size_t> docid_count(50000);
  for (string current_query; getline(query_input, current_query); ) {
    
    const auto words = SplitIntoWords(current_query);
    for (const auto& word : words) {
      for (const auto& docid : index.Lookup(word)) {
        docid_count[docid.first] += docid.second;
      }
    }

    
    vector<pair<size_t, size_t>> search_results;
    for (size_t i = 0; i < docid_count.size(); ++i){
      if(docid_count[i] > 0){
         search_results.emplace_back(i, docid_count[i]);
         docid_count[i] = 0;
      }
    }
      
    partial_sort(
        search_results.begin(),
        search_results.begin() + std::min<size_t>(5,search_results.size()),
        search_results.end(),
        [](pair<size_t, size_t>& lhs, pair<size_t, size_t>& rhs) {
          int64_t lhs_docid = lhs.first;
          auto lhs_hit_count = lhs.second;
          int64_t rhs_docid = rhs.first;
          auto rhs_hit_count = rhs.second;
          return std::make_pair(lhs_hit_count, -lhs_docid) > std::make_pair(rhs_hit_count, -rhs_docid);
        }
      );

    search_results_output << std::move(current_query) << ':';
    for (auto [docid, hitcount] : Head(search_results, 5)) {
      search_results_output << " {"
        << "docid: " << docid << ", "
        << "hitcount: " << hitcount << '}';
    }
    search_results_output << '\n';
  }
}

InvertedIndex::InvertedIndex() : doc_size(0){};

//add into index: each word as key - push_back doc_id into a list(as value) 
void InvertedIndex::Add(const string& document) {
  ++doc_size;
  
  const size_t docid = doc_size - 1;
  for (const auto& word : SplitIntoWords(document)) {
    auto& word_index = index[word];
    if (word_index.empty() || word_index.back().first != docid) {
      word_index.emplace_back(docid, 1);
    } else {
        ++word_index.back().second;
    }
  }

}
//index: word -> list of doc_ids; 
//retrievs list of doc id's , in which word appears
vector<pair<size_t,size_t>> InvertedIndex::Lookup(const string& word) const {
  if (auto it = index.find(word); it != index.end()) {
    return it->second;
  } else {
    return {};
  }
}