#include <string>
#include <iostream>
#include <vector>

void MoveStrings(std::vector<std::string>& s,std::vector<std::string>& d){
    for(auto w:s){
        d.push_back(w);
    }
    s.clear();
   
}



int main(){
    std::vector<std::string> source = {"a","b","c"};
    std::vector<std::string> destination = {"z"};
    MoveStrings(source,destination);

    return 0;

}