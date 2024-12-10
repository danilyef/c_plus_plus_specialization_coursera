#include "test_runner.h"

#include <algorithm>
#include <numeric>
using namespace std;

template <typename T>
void Swap(T* first, T* second){
  T first_val = *first;
  *first = *second;
  *second = first_val;
};


auto compareFunc = [](const int* a, const int* b){return *a < *b;};
template <typename T>
void SortPointers(vector<T*>& pointers){
  sort(pointers.begin(), pointers.end(),compareFunc);
};

template <typename T>
void ReversedCopy(T* source, size_t count, T* destination)
{
    if ((destination + count <= source) || (source + count <= destination))
    {
        std::reverse_copy(source, source + count, destination);
    }
    else
    {
        auto left_border = destination;
        auto right_border = destination + count;

        if (destination < source) {
            for (size_t i = 0, j = count - 1 ; j >= destination + count - source; ++i, --j)
            {
                destination[i] = source[j];
            }
            left_border = source;
        }

        if (source < destination)
        {
            for (size_t i = 0, j = count - 1; i < destination - source; ++i, --j)
            {
                destination[j] = source[i];
            }
            right_border = source + count;
        }
        std::reverse(left_border, right_border);
    }
}

void TestSwap() {
  int a = 1;
  int b = 2;
  Swap(&a, &b);
  ASSERT_EQUAL(a, 2);
  ASSERT_EQUAL(b, 1);

  string h = "world";
  string w = "hello";
  Swap(&h, &w);
  ASSERT_EQUAL(h, "hello");
  ASSERT_EQUAL(w, "world");
}

void TestSortPointers() {
  int one = 1;
  int two = 2;
  int three = 3;

  vector<int*> pointers;
  pointers.push_back(&two);
  pointers.push_back(&three);
  pointers.push_back(&one);

  SortPointers(pointers);

  ASSERT_EQUAL(pointers.size(), 3u);
  ASSERT_EQUAL(*pointers[0], 1);
  ASSERT_EQUAL(*pointers[1], 2);
  ASSERT_EQUAL(*pointers[2], 3);
}

void TestReverseCopy() {
  const size_t count = 7;

  int* source = new int[count];
  int* dest = new int[count];

  for (size_t i = 0; i < count; ++i) {
    source[i] = i + 1;
  }
  //ReversedCopy(source, count, dest);
  //const vector<int> expected1 = {7, 6, 5, 4, 3, 2, 1};
  //ASSERT_EQUAL(vector<int>(dest, dest + count), expected1);

  // Области памяти могут перекрываться
  ReversedCopy(source, count - 1, source + 1);
  const vector<int> expected2 = {1, 6, 5, 4, 3, 2, 1};
  ASSERT_EQUAL(vector<int>(source, source + count), expected2);

  delete[] dest;
  delete[] source;
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSwap);
  RUN_TEST(tr, TestSortPointers);
  RUN_TEST(tr, TestReverseCopy);
  return 0;
}
