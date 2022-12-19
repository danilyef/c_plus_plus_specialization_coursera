#include <iostream>
#include <cstdint>
#include <limits>
#include <tuple>
#include <map>
#include <vector>
#include <string>
#include <exception>


using namespace std;


/*
Реализуйте класс TeamTasks, позволяющий хранить статистику по статусам задач команды разработчиков:
*/

// Перечислимый тип для статуса задачи
enum class TaskStatus {
    NEW,          // новая
    IN_PROGRESS,  // в разработке
    TESTING,      // на тестировании
    DONE          // завершена
};

using TasksInfo = map<TaskStatus, int>;

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
  cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
      ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
      ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
      ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

void RemoveZeros(TasksInfo& task_info){
    vector<TaskStatus> keys_to_del;
    for(const auto& elem:task_info){
        if(elem.second == 0){
            keys_to_del.push_back(elem.first);
        }
    }
    for(const TaskStatus status:keys_to_del){
        task_info.erase(status);
    }
}



class TeamTasks {
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo& GetPersonTasksInfo(const string& person) const{
        if(developers_tasks.count(person) == 0){
             throw runtime_error("Developer " + person + " doesn't belong to the team");
        }
        return developers_tasks.at(person);
    };

    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string& person){
        ++developers_tasks[person][TaskStatus::NEW];
    }

    int CountNotDoneTasks(const string& person){
        int count = 0;
        for(int i = 0; i < 3; ++i){
            count += developers_tasks[person][status[i]];
        }

        return count;
    }

    // Обновить статусы по данному количеству задач конкретного разработчика,
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(
        const string& person, int task_count){
            
        TasksInfo updated_tasks;
        TasksInfo old_tasks = developers_tasks.at(person);
        int not_done_tasks = CountNotDoneTasks(person);

        if(task_count > not_done_tasks){
            task_count = not_done_tasks;
        }

        int status_num = 0;
        for(int i = 0; i < task_count; ++i){
            if(developers_tasks.at(person)[status[status_num]] == 0){
                ++status_num;
            }
            --old_tasks[status[status_num]];
            ++updated_tasks[status[status_num + 1]];
            --developers_tasks[person][status[status_num]];
            ++developers_tasks[person][status[status_num + 1]];

        }
        RemoveZeros(updated_tasks);
        RemoveZeros(old_tasks);

        return tie(updated_tasks,old_tasks);
    };

private:
    map<string,TasksInfo> developers_tasks;
    vector<TaskStatus> status = {TaskStatus::NEW,TaskStatus::IN_PROGRESS,TaskStatus::TESTING,TaskStatus::DONE};
};




int main() {
    TeamTasks tasks;
    for (int i = 0; i < 3; ++i) {
    tasks.AddNewTask("Ivan");
    }
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

    TasksInfo updated_tasks, untouched_tasks;

    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 10);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    return 0;
}

