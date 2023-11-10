#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;


int main(){
    ifstream input("input.txt");


    if(input){
        int rows = 0;
        int columns = 0;
        input >> rows >> columns;
        int number;
       for(int i = 0; i< rows; ++i ){
           for(int j = 0; j < columns; ++j){
               input >> number;
               cout << setw(10) << number;
               input.ignore(1);
               
               if(j != columns - 1){
                   cout << " ";
               }
               
           }
           if (i != rows - 1) {
                cout << endl;
            }
        }
       
    }



    return 0;

}

