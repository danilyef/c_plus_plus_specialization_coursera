#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

/*
Определите структуру «Студент» со следующими полями: имя, фамилия, день, месяц и год рождения. Создайте вектор из таких структур, заполните его из входных данных и затем по запросам выведите нужные поля. Чтение и запись данных в этой задаче производится с использованием стандартных потоков.

Формат ввода

Первая строка содержит одно целое число N от 0 до 10000 — число студентов.

Далее идут N строк, каждая из которых содержит две строки длиной от 1 до 15 символов — имя и фамилию очередного студента, и три целых числа от 0 до 1000000000 — день, месяц и год рождения.

Следующая строка содержит одно целое число M от 0 до 10000 — число запросов.

Следующие M строк содержат строку длиной от 1 до 15 символов — запрос, и целое число от 1 до 1000000000 — номер студента (нумерация начинается с 1).

Формат вывода

Для запроса вида name K, где K от 1 до N, выведите через пробел имя и фамилию K-го студента.

Для запроса вида date K, где K от 1 до N, выведите через точку день, месяц и год рождения K-го студента.

Для остальных запросов выведите bad request.
*/

struct Student{
    string name;
    string surname;
    int day;
    int month;
    int year;
    Student(string new_name,string new_surname,int new_day,int new_month,int new_year){
        name = new_name;
        surname = new_surname;
        day = new_day;
        month = new_month;
        year = new_year;
    }

    void print_request(const string& user_request){
        if(user_request == "name"){
            cout << name << ' ' << surname << endl;
        } else if(user_request == "date"){
            cout << day << '.' << month << '.' << year << endl;
        } else{
            cout << "bad request" << endl;
        }
    }
};



int main(){
    int N = 0;
    int M = 0;
    vector<Student> vec_student;
    cin >> N;
    for(int i = 0;i< N; i++){
        
        string name,surname;
        int day = 0,month = 0,year = 0;
        cin >> name >> surname >> day >> month >> year;
        
        Student s(name,surname,day,month,year);
        vec_student.push_back(s);
    }
    
    cin >> M;
    string request;
    int student_id = 0;
    
    for(int i = 0;i< M; i++){
        
        cin >> request >> student_id;
        --student_id;

        if(student_id > vec_student.size() || student_id < 0){
            cout << "bad request" << endl;
        } else{
            vec_student[student_id].print_request(request);
        } 
    }
    return 0;
}