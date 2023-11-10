
/*
Implement the TeamTasks class that allows storing statistics on the statuses of the developer team's tasks.

The method PerformPersonTasks should implement the following algorithm:

1. Consider all the tasks of the developer person that are not completed.
2. Order them by statuses: first, all tasks with the status NEW, then all tasks with the status IN_PROGRESS, and finally, tasks with the status TESTING.
3. Take the first task_count tasks and change each of them to the next status according to the natural order: NEW → IN_PROGRESS → TESTING → DONE.
4. Return a tuple of two elements: information about the updated tasks' statuses (including those that are now in the DONE status) and information about the statuses of the remaining incomplete tasks.

It is guaranteed that task_count is a positive number. If task_count exceeds the current number of incomplete tasks of the developer, it is sufficient to consider task_count equal to the number of incomplete tasks. In this case, there is no need to update the status of any task twice.

Also, it is guaranteed that the method GetPersonTasksInfo will not be called for a developer who has no tasks.

Example of the PerformPersonTasks method:
Suppose a specific developer has 10 tasks with the following statuses:

NEW — 3
IN_PROGRESS — 2
TESTING — 4
DONE — 1

The PerformPersonTasks method is called with the parameter task_count = 4, which means updating the status for 3 tasks from NEW to IN_PROGRESS and for 1 task from IN_PROGRESS to TESTING. Thus, the new task statuses will be as follows:

IN_PROGRESS — 3 updated, 1 old
TESTING — 1 updated, 4 old
DONE — 1 old

In this case, you need to return a tuple of 2 dictionaries:

Updated tasks: IN_PROGRESS — 3, TESTING — 1.
Non-updated tasks, excluding completed ones: IN_PROGRESS — 1, TESTING — 4.

The dictionaries should not contain unnecessary elements, meaning statuses that have zero tasks associated with them.

Note:
Updating a dictionary while iterating over it can lead to unpredictable consequences. If necessary, it is recommended to first gather information about updates in a separate temporary dictionary and then apply them to the main dictionary.
*/


#include <map>
#include <vector>
#include <tuple>
#include <string>
#include <iostream>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
  NEW,          // новая
  IN_PROGRESS,  // в разработке
  TESTING,      // на тестировании
  DONE          // завершена
};



TaskStatus int_to_task(int status) {
    switch (status) {
        case 1: return TaskStatus::NEW;
        case 2: return TaskStatus::IN_PROGRESS;
        case 3: return TaskStatus::TESTING;
        case 4: return TaskStatus::DONE;
        default: return TaskStatus::NEW;
    }
}




// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

int total_not_done_tasks(TasksInfo& developer) {
    int num = 0;
    for(int i = 1; i < 4;++i){
        num += developer[int_to_task(i)];
    }
    return num;
}

void DeleteZeros (TasksInfo& dict){
    for(int i = 1; i < 4;++i){
        if(dict[int_to_task(i)] == 0){
            dict.erase(int_to_task(i));
        }
    }

};



class TeamTasks {
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo& GetPersonTasksInfo(const string& person) const{
        return board.at(person);
    };

    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string& person){
        ++board[person][TaskStatus::NEW];
    };


    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(
        const string& person, int task_count){
            
            /*Board of one developer*/
            TasksInfo reference_developer = board[person];
            TasksInfo board_developer = board[person];
            TasksInfo updated;
            TasksInfo not_updated = board[person];
            
            int not_done_tasks = total_not_done_tasks(board_developer);
            if(task_count > not_done_tasks){
                task_count = not_done_tasks;
            }
            int current_status = 1;
            int next_status = 2;
            
            while(board_developer[int_to_task(current_status)] == 0){
                ++current_status;
                ++next_status;
                if(next_status == 5){
                    return tie(updated,updated);
                }
            }

            while(task_count !=0){
                for (int j = 0; j < reference_developer.at(int_to_task(current_status)); ++j){
                    --board_developer[int_to_task(current_status)];
                    ++board_developer[int_to_task(next_status)];
                    ++updated[int_to_task(next_status)];
                    --not_updated[int_to_task(current_status)];
                    --task_count;
                    if(task_count == 0) break;    
                }
                ++current_status;
                ++next_status;
            }


            DeleteZeros(updated);
            DeleteZeros(not_updated);
            not_updated.erase(int_to_task(4));
            
            board[person] = board_developer;
           

            return tie(updated,not_updated);


        };

private:
    map<string,TasksInfo> board;
    
};




// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(const TasksInfo& tasks_info) {
    if (tasks_info.count(TaskStatus::NEW)) {
        std::cout << "NEW: " << tasks_info.at(TaskStatus::NEW) << " ";
    }
    if (tasks_info.count(TaskStatus::IN_PROGRESS)) {
        std::cout << "IN_PROGRESS: " << tasks_info.at(TaskStatus::IN_PROGRESS) << " ";
    }
    if (tasks_info.count(TaskStatus::TESTING)) {
        std::cout << "TESTING: " << tasks_info.at(TaskStatus::TESTING) << " ";
    }
    if (tasks_info.count(TaskStatus::DONE)) {
        std::cout << "DONE: " << tasks_info.at(TaskStatus::DONE) << " ";
    }
}
 
void PrintTasksInfo(const TasksInfo& updated_tasks, const TasksInfo& untouched_tasks) {
    std::cout << "Updated: [";
    PrintTasksInfo(updated_tasks);
    std::cout << "] ";
 
    std::cout << "Untouched: [";
    PrintTasksInfo(untouched_tasks);
    std::cout << "] ";
 
    std::cout << std::endl;
}

int main() {
    TeamTasks tasks;
    TasksInfo updated_tasks;
    TasksInfo untouched_tasks;
 
    /* TEST 1 */
    std::cout << "Alice" << std::endl;
 
    for (auto i = 0; i < 5; ++i) {
        tasks.AddNewTask("Alice");
    }
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 5}, {}]
 
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"TESTING": 5}, {}]
 
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 1);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"DONE": 1}, {"TESTING": 4}]
 
    for (auto i = 0; i < 5; ++i) {
        tasks.AddNewTask("Alice");
    }
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice",
                                                                   2);  // [{"IN_PROGRESS": 2}, {"NEW": 3, "TESTING": 4}]
    PrintTasksInfo(updated_tasks, untouched_tasks);
 
    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));  // {"NEW": 3, "IN_PROGRESS": 2, "TESTING": 4, "DONE": 1}
    std::cout << std::endl;
 
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 4);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 3, "TESTING": 1}, {"IN_PROGRESS": 1, "TESTING": 4}]
 
    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));  // {"IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}
    std::cout << std::endl;
 
    /* TEST 2 */
    std::cout << "\nJack" << std::endl;
 
    tasks.AddNewTask("Jack");
 
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 1);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1}, {}]
 
    tasks.AddNewTask("Jack");
 
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 2);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1, "TESTING": 1}, {}]
 
    tasks.AddNewTask("Jack");
 
    PrintTasksInfo(tasks.GetPersonTasksInfo("Jack"));  // {"NEW": 1, "IN_PROGRESS": 1, "TESTING": 1, "DONE": 0}
    std::cout << std::endl;
 
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 3);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1, "TESTING": 1, "DONE": 1}, {}]
 
    PrintTasksInfo(tasks.GetPersonTasksInfo("Jack"));  // {"IN_PROGRESS": 1, "TESTING": 1, "DONE": 1}
    std::cout << std::endl;
 
    /* TEST 3 */
    std::cout << "\nLisa" << std::endl;
 
    for (auto i = 0; i < 5; ++i) {
        tasks.AddNewTask("Lisa");
    }
 
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 5}, {}]
 
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"TESTING": 5}, {}]
 
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 1);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"DONE": 1}, {"TESTING": 4}]
 
    for (auto i = 0; i < 5; ++i) {
        tasks.AddNewTask("Lisa");
    }
 
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 2);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 2}, {"NEW": 3, "TESTING": 4}]
 
    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"NEW": 3, "IN_PROGRESS": 2, "TESTING": 4, "DONE": 1}
    std::cout << std::endl;
 
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 4);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 3, "TESTING": 1}, {"IN_PROGRESS": 1, "TESTING": 4}]
 
    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}
    std::cout << std::endl;
 
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"TESTING": 4, "DONE": 1}, {"TESTING": 4}]
 
    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"TESTING": 8, "DONE": 2}
    std::cout << std::endl;
 
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 10);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"DONE": 8}, {}]
 
    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"DONE": 10}
    std::cout << std::endl;
 
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 10);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{}, {}]
 
    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"DONE": 10}
    std::cout << std::endl;
 
    tasks.AddNewTask("Lisa");
 
    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"NEW": 1, "DONE": 10}
    std::cout << std::endl;
 
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 2);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1}, {}]
 
    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"IN_PROGRESS": 1, "DONE": 10}
    std::cout << std::endl;
 
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Bob", 3);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{}, {}]
 
    return 0;
}