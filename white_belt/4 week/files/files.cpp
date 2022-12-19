#include <iostream>
#include <fstream>
#include <string>
using namespace std;
 
int main() {
    ifstream input("input.txt");
    string line;
    ofstream output("output.txt");
    while (getline(input, line)) {
        cout << line << << endl; 
        output << line << endl; 
    }
    return 0;
}