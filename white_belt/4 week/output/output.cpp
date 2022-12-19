#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;



int main(){
    ifstream input("input.txt");
    double number;
    cout << fixed << setprecision(3);
    if(input){
        while(input >> number){
            cout << number << endl;

        }
    }

    return 0;
}