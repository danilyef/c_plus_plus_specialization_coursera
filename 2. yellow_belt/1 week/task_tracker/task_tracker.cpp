#include <map>
#include <vector>
#include <tuple>
#include <string>
#include <iostream>

using namespace std;


enum class TaskStatus {
  NEW,              
  IN_PROGRESS,  
  TESTING,      
  DONE          
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
    const TasksInfo& GetPersonTasksInfo(const string& person) const{
        return board.at(person);
    };

    void AddNewTask(const string& person){
        ++board[person][TaskStatus::NEW];
    };


    tuple<TasksInfo, TasksInfo> PerformPersonTasks(
        const string& person, int task_count){
            
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