#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <numeric>
#include "profile.h"



vector<string_view> SplitIntoWordsView(string_view line) {
    std::vector<std::string_view> result;
    size_t start = 0;
    size_t end = 0;

    while (end != std::string_view::npos) {
        end = line.find(' ', start);
        if (start != end && line.substr(start, end - start) != "") {
            result.emplace_back(line.substr(start, end - start));
        }
        start = end + 1;
    }

    return result;
}


void UpdateIndex(istream& document_input, Synchronized<InvertedIndex>& index) {
  InvertedIndex new_index(document_input);
  swap(index.GetAccess().ref_to_value, new_index);
}


void SearchServer::UpdateDocumentBase(istream& document_input) {
  futures.push_back(async(UpdateIndex,ref(document_input), ref(index)));
}

void SingleQueriesStream(istream& query_input, ostream& search_results_output, Synchronized<InvertedIndex>& index){
  vector<size_t> docid_count(50000);
  for (string current_query; getline(query_input, current_query); ) {
    {
      vector<string_view> words = SplitIntoWordsView(current_query);
      for (string_view word : words) {
        for (const auto& docid : index.GetAccess().ref_to_value.Lookup(word)) {
          docid_count[docid.first] += docid.second;
        }
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
};


void SearchServer::AddQueriesStream(
  istream& query_input, ostream& search_results_output
) {
  futures.push_back(async(SingleQueriesStream,ref(query_input),ref(search_results_output),ref(index)));
}

InvertedIndex::InvertedIndex() : doc_size(0){};
InvertedIndex::InvertedIndex(istream& document_input):doc_size(0){
  for (string current_document; getline(document_input, current_document); ) {
    ++doc_size;
    docs.push_back(std::move(current_document));
    const size_t docid = doc_size - 1;
    for (string_view word : SplitIntoWordsView(docs.back())) {
      auto& word_index = index[word];
      if (word_index.empty() || word_index.back().first != docid) {
        word_index.emplace_back(docid, 1);
      } else {
          ++word_index.back().second;
      }
    }
  }
}

//index: word -> list of doc_ids; 
//retrievs list of doc id's , in which word appears
vector<pair<size_t,size_t>> InvertedIndex::Lookup(string_view word) const {
  if (auto it = index.find(word); it != index.end()) {
    return it->second;
  } else {
    return {};
  }
}