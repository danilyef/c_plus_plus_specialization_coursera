#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

/*
Реализуйте обработку следующих операций над очередью:

WORRY i: пометить i-го человека с начала очереди как беспокоящегося;

QUIET i: пометить i-го человека как успокоившегося;

COME k: добавить k спокойных человек в конец очереди;

COME -k: убрать k человек из конца очереди;

WORRY_COUNT: узнать количество беспокоящихся людей в очереди.

Изначально очередь пуста.

Формат ввода
Количество операций Q, затем описания операций.

Для каждой операции WORRY i и QUIET i гарантируется, что человек с номером i существует в очереди на момент операции.

Для каждой операции COME -k гарантируется, что k не больше текущего размера очереди.

Формат вывода
Для каждой операции WORRY_COUNT выведите одно целое число — количество беспокоящихся людей в очереди.

*/

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

void come(std::vector<bool>& v,int k){
    if(k>0){
        for(int i = 0;i < k; i++){
            v.push_back(false);
        }
    } else{
        for(int i = 0;i < -k; i++){
            v.pop_back();
        }
              
    }

}

void quiet(std::vector<bool>& v,int k){
    v[k] = false;
}

void worry(std::vector<bool>& v,int k){
    v[k] = true;
}

void worry_count(std::vector<bool>& v){
    std::cout << std::count(v.begin(),v.end(),true) << std::endl;      
}


int main(){
    int q; // number of oeprations
    std::string operation; //name of the operation
    std::cin >> q; // what operation to do
    std::vector<bool> queue; //bool vector of queue: false = quiet, true = worried
    
    int num; // number of operation other than worry_count
    for(int i = 0; i<q; i++){
        std::cin >> operation;
        if(operation == "WORRY_COUNT"){
            worry_count(queue);
        }

        else {
            std::cin >> num;
            if(operation == "COME"){
                come(queue,num);

            } else if(operation == "WORRY"){
                worry(queue,num);
            } else if(operation == "QUIET"){
                quiet(queue,num);
            }  

        }   
        
    }

    return 0;

}