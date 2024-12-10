#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;
/*

У каждого из нас есть повторяющиеся ежемесячные дела, каждое из которых нужно выполнять в конкретный день каждого месяца: оплата счетов за электричество, абонентская плата за связь и пр. Вам нужно реализовать работу со списком таких дел на месяц, а именно, реализовать набор следующих операций:

ADD i s
Назначить дело с названием s на день i текущего месяца.

DUMP i
Вывести все дела, запланированные на день i текущего месяца.

NEXT
Перейти к списку дел на новый месяц. При выполнении данной команды вместо текущего (старого) списка дел на текущий месяц создаётся и становится активным (новый) список дел на следующий месяц: все дела со старого списка дел копируются в новый список. После выполнения данной команды новый список дел и следующий месяц становятся текущими, а работа со старым списком дел прекращается.  При переходе к новому месяцу необходимо обратить внимание на разное количество дней в месяцах:

если следующий месяц имеет больше дней, чем текущий, «дополнительные» дни необходимо оставить пустыми (не содержащими дел);

если следующий месяц имеет меньше дней, чем текущий, дела со всех «лишних» дней необходимо переместить на последний день следующего месяца.

Замечания
Историю списков дел хранить не требуется, работа ведется только с текущим списком дел текущего месяца. Более того, при создании списка дел на следующий месяц, он «перетирает» предыдущий список.

Обратите внимание, что количество команд NEXT в общей последовательности команд при работе со списком дел может превышать 11.

Начальным текущим месяцем считается январь.

Количества дней в месяцах соответствуют Григорианскому календарю с той лишь разницей, что в феврале всегда 28 дней.

Формат ввода
Сначала число операций Q, затем описания операций.

Названия дел s уникальны и состоят только из латинских букв, цифр и символов подчёркивания. Номера дней i являются целыми числами и нумеруются от 1 до размера текущего месяца.

Формат вывода
Для каждой операции типа DUMP в отдельной строке выведите количество дел в соответствующий день, а затем их названия, разделяя их пробелом. Порядок вывода дел в рамках каждой операции значения не имеет.

*/


void add(vector<vector<string> >& v,int d , string task){
    v[d-1].push_back(task);
}

void dump(vector<vector<string> >& v,int d){
    cout << v[d-1].size() << " " ;
    for(int i = 0; i < v[d-1].size(); i++){
        cout << v[d-1][i] << " ";
    }
    cout << endl;

}

void next(vector<vector<string> >& v,const vector<int>& m,int& size_c){
    // size_n - size of the next month
    // size_c - size of the current month
    int size_n = size_c;
    if(size_c == 11){
        size_n = 0;
    } else{
        size_n += 1;
    }
    //define vector for the next month
    vector<vector<string> > next_month; 

    //copy current month into the next month
    next_month = v;

    //if next month is shorter than current month, 
    //than copy extra elements to the last element 
    // of the next month. For this we compare length of months
    int day_diff = m[size_c] - m[size_n];

    if(day_diff > 0){
        for (int i = 0; i< day_diff; i++){
            next_month[m[size_n]-1].insert(end(next_month[m[size_n]-1]), begin(v[m[size_n]+i]), end(v[m[size_n]+i]));
        }
    }

    next_month.resize(m[size_n]);
    v = next_month;
    size_c = size_n; 

    next_month.clear();

    


}


int main(){
    //q - number of oeprations.
    //m_ind - month index. 
    //day - on which day to plan operation.
    //to_do - what exactly to do on some day.
    //operation - which kind of operation to perform.

    const vector<int>day_mon = {31,28,31,30,31,30,31,31,30,31,30,31};
    int m_ind = 0;
    int q,day;
    string operation;
    string to_do; 
    
  


    //vector of the current month
    vector<vector<string> > current_month(31);
    
    cin >> q;
    //for q operations:
    for(int i = 0;i< q;i++){
        cin >> operation;
        if(operation == "NEXT"){
            next(current_month,day_mon,m_ind);
        } else if(operation == "ADD"){
            cin >> day >> to_do;
            add(current_month,day,to_do);
        } else if(operation == "DUMP"){
            cin >> day;
            dump(current_month,day);
        }
    }

    return 0;
    
    
}

