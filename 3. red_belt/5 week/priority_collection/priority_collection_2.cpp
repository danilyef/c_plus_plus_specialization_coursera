#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <typeinfo>

using namespace std;


template <typename T>
class PriorityCollection {
public:
    
    using Id = size_t;
    
    // Add an object with zero priority
   // by moving it and return its identifier
    Id Add(T object){
        id_objects.emplace(0,id);
        objects.emplace_back(std::move(object),0);
        return Id(id++);
    };


   // Add all elements in the range [range_begin, range_end)
   // by moving them, writing the issued identifiers
   // to the range [ids_begin, ...)
    
    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end, IdOutputIt ids_begin){
        while (range_begin != range_end){
            *ids_begin++ = Add(std::move(*range_begin++));
        } 

    };
    
    // Determine whether the identifier belongs to any
    // object stored in the container
    bool IsValid(Id id) const {
        if(objects[id].second == -1){
            return false;
        }
        return id < objects.size();
    };

    // Get the object by identifier
    const T& Get(Id id) const{
        return objects[id].first;
    };

    // Increase the priority of the object by 1
    void Promote(Id id) {
        id_objects.erase({objects[id].second,id});
        objects[id].second++;
        id_objects.insert(std::make_pair(objects[id].second,id));
    };

    // Get the object with the maximum priority and its priority
    pair<const T&, int> GetMax() const {
        auto id = id_objects.begin()->second;
        return objects[id];
    };


    // Similar to GetMax, but removes the element from the container
    pair<T, int> PopMax(){
        auto id = id_objects.begin()->second;
        id_objects.erase(id_objects.begin());
        auto result = std::move(objects[id]);
        objects[id] = {T(), -1};
        return result;
    };

private:
    int id = 0;
    vector<pair<T,int>> objects;
    set<pair<int,Id>, std::greater<>> id_objects;
};


class StringNonCopyable : public string {
public:
    using string::string;  
    StringNonCopyable(const StringNonCopyable&) = delete;
    StringNonCopyable(StringNonCopyable&&) = default;
    StringNonCopyable& operator=(const StringNonCopyable&) = delete;
    StringNonCopyable& operator=(StringNonCopyable&&) = default;
};


void TestNoCopy() {
    PriorityCollection<StringNonCopyable> strings;
    const auto white_id = strings.Add("white");
    const auto yellow_id = strings.Add("yellow");
    const auto red_id = strings.Add("red");

    strings.Promote(yellow_id);
    for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
    }
    strings.Promote(yellow_id);
    {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
    }
    {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
    }
    {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
    }
}


int main() {
    TestRunner tr;
    RUN_TEST(tr, TestNoCopy);
   
    return 0;
}

