#include "test_runner.h"
#include <iostream>
#include <map>
#include <vector>

using namespace std;



template <typename T>
class Table{
public:

    Table(std::size_t val_1, std::size_t val_2) {
        Resize(val_1,val_2);
    };

    void Resize(size_t val_1, size_t val_2){
       
        table.resize(val_1);
        for(auto &col: table){
            col.resize(val_2);
    }
}


    std::pair<size_t, size_t> Size() const {
        return std::make_pair(table.size(),table[0].size());
    };

    const std::vector<T>& operator[] (std::size_t idx_row) const {return table[idx_row];}
    std::vector<T>& operator[] (std::size_t idx_row) {return table[idx_row];}

private:
    std::vector<std::vector<T>> table;

};

void TestTable() {
    Table<int> t(1, 1);
    ASSERT_EQUAL(t.Size().first, 1u);
    ASSERT_EQUAL(t.Size().second, 1u);
    t[0][0] = 42;
    ASSERT_EQUAL(t[0][0], 42);
    t.Resize(3, 4);
    ASSERT_EQUAL(t.Size().first, 3u);
    ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}
