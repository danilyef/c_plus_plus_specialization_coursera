#include "test_runner.h"
#include <vector>
#include <future>
#include <algorithm>
#include <numeric>
using namespace std;


template <typename Iterator>
class IteratorRange { 
public:
    IteratorRange(Iterator f, Iterator l): first(f), last(l) {};

    Iterator begin() const { 
        return first;
    }

    Iterator end() const {
        return last;
    }

    size_t size() const {
       return last - first;
    }

private:
    Iterator first;
    Iterator last;
};


template <typename Iterator>
class Paginator {
public:
    Paginator(Iterator begin_, Iterator end_, size_t page_size_): page_size(page_size_) {
        size_t cont_size = std::distance(begin_, end_);
        size_t num_pages = (cont_size + (page_size - 1)) / page_size;

        for(size_t page = 0; page < num_pages; ++page){
            auto first = begin_ + (page_size * page);
            auto second = begin_ + std::min(page_size * (page + 1),cont_size);
            elements.push_back(IteratorRange<Iterator>(first,second));
        }
    };
    
    auto begin() const {
        return elements.begin();
    };

    auto end() const {
        return elements.end();
    };


    size_t size() const {
        return elements.size();
    };


private:
    size_t page_size;
    std::vector<IteratorRange<Iterator>> elements;
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
    return Paginator {c.begin(),c.end(),page_size};
}


template <typename ContainerOfVectors>
int64_t SumVector(ContainerOfVectors& vectors){
	int64_t sum = 0;
	for(auto v: vectors){
		sum = accumulate(v.begin(), v.end(), sum);
	}
	return sum;
}



int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
	int page_size = 2000;
	vector<future<int64_t>> futures;
	int64_t sum = 0;
	for (auto page : Paginate(matrix , page_size)){
		futures.push_back(
			async([page]{
				return SumVector(page);
			})
		);
	}

	for(int i = 0; i < futures.size(); ++i){
		sum += futures[i].get();
	}
	return sum;
}


void TestCalculateMatrixSum() {
	const vector<vector<int>> matrix = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 10, 11, 12},
		{13, 14, 15, 16}
	};
	ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestCalculateMatrixSum);
}
