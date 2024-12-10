#include <string>
#include <iostream>
#include <tuple>
#include <map>

using namespace std;


enum class TaskStatus {
  NEW,          // new
  IN_PROGRESS,  // in progress
  TESTING,      // in testing
  DONE          // completed
};


using TasksInfo = map<TaskStatus, int>;


class TeamTasks {
public:
  // Get statistics on task statuses for a specific developer
    const TasksInfo& GetPersonTasksInfo(const string& person) const{ 
        return  task_tracker.at(person);
    };
  
  // Add a new task (with NEW status) for a specific developer
    void AddNewTask(const string& person){
        task_tracker[person][TaskStatus::NEW]++;
    };
  
    // Update statuses for the given number of tasks for a specific developer,
    // see details below
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count){
        TasksInfo updated_tasks;
        TasksInfo& person_tracker = task_tracker[person];
        
        // Make a copy for untouched tasks
        TasksInfo untouched_tasks = task_tracker[person];
        
        //Find a minimum of task_count and open tasks
        int total_open_tasks =  untouched_tasks[TaskStatus::NEW] + untouched_tasks[TaskStatus::IN_PROGRESS] + untouched_tasks[TaskStatus::TESTING];
        task_count = std::min(task_count,total_open_tasks);

        for(int i = 0; i < task_count; ++i) {
            auto current_status = FirstNonZeroTask(untouched_tasks);
            if(current_status.first == TaskStatus::DONE) {
                break;
            }
            
            // Update the counts
            person_tracker[current_status.first]--;
            person_tracker[current_status.second]++;
            
            // Track the updates
            updated_tasks[current_status.second]++;
            untouched_tasks[current_status.first]--;

        }
        
        // Clean up
        removeZeroValues(updated_tasks);
        removeZeroValues(untouched_tasks);
        removeZeroValues(person_tracker);
        
        // DONE tasks shouldn't be included in untouched
        untouched_tasks.erase(TaskStatus::DONE);
        
        return {updated_tasks, untouched_tasks};
    };

private:
    std::map< std::string, TasksInfo> task_tracker;

    const pair<TaskStatus,TaskStatus> FirstNonZeroTask(TasksInfo& person_tracker) {
        if (person_tracker[TaskStatus::NEW] > 0) {
            return std::make_pair(TaskStatus::NEW,TaskStatus::IN_PROGRESS);
        } else if (person_tracker[TaskStatus::IN_PROGRESS] > 0) {
            return std::make_pair(TaskStatus::IN_PROGRESS,TaskStatus::TESTING);
        } else if (person_tracker[TaskStatus::TESTING] > 0) {
            return std::make_pair(TaskStatus::TESTING,TaskStatus::DONE);
        } else {
            return std::make_pair(TaskStatus::DONE,TaskStatus::DONE);
        }
    }

    void removeZeroValues(TasksInfo& task_map) {
        for (auto it = task_map.begin(); it != task_map.end(); ) {
            if (it->second <= 0) { 
                it = task_map.erase(it); // Erase and get the next iterator
            } else {
                ++it; // Move to the next element
            }
        }
    }



};


// Accept dictionary by value to be able to
// access missing keys using [] and get 0,
// without modifying the original dictionary
void PrintTasksInfo(TasksInfo tasks_info) {
  cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
      ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
      ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
      ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
    TeamTasks tasks;
    TasksInfo updated_tasks;
    TasksInfo untouched_tasks;
   

    // TEST 1 
    std::cout << "Alice" << std::endl;
    
    std::cout << "Added 5 new tasks" << endl;
    for (auto i = 0; i < 5; ++i) {
       tasks.AddNewTask("Alice");
    }
    
    std::cout << "Performed 5 tasks" << endl;
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
    cout << "Alice updated tasks:";
    PrintTasksInfo(updated_tasks); // [{"IN_PROGRESS": 5}, {}]
    cout << "Alice untouched tasks:";
    PrintTasksInfo(untouched_tasks);
    cout << "#################################" << endl;
 
    std::cout << "Performed 5 tasks" << endl;
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
    cout << "Alice updated tasks:";
    PrintTasksInfo(updated_tasks); // [{"TESTING": 5}, {}]
    cout << "Alice untouched tasks:";
    PrintTasksInfo(untouched_tasks);
    cout << "#################################" << endl;
 
    std::cout << "Performed 1 task" << endl;
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 1);
    cout << "Alice updated tasks:";
    PrintTasksInfo(updated_tasks); // [{"DONE": 1}, {"TESTING": 4}]
    cout << "Alice untouched tasks:";
    PrintTasksInfo(untouched_tasks);
    cout << "#################################" << endl;
 
    std::cout << "Added 5 new tasks" << endl;
    for (auto i = 0; i < 5; ++i) {
       tasks.AddNewTask("Alice");
    }
    
    std::cout << "Performed 2 task" << endl;
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice",2);
    // [{"IN_PROGRESS": 2}, {"NEW": 3, "TESTING": 4}]
    cout << "Alice updated tasks:";
    PrintTasksInfo(updated_tasks);
    cout << "Alice untouched tasks:";
    PrintTasksInfo(untouched_tasks);
    cout << "#################################" << endl;
    cout << "Alice all tasks:";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice")); // {"NEW": 3, "IN_PROGRESS": 2, "TESTING": 4, "DONE": 1}
    cout << "#################################" << endl;
 
    std::cout << "Performed 4 task" << endl;
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 4);
    cout << "Alice updated tasks:";
    PrintTasksInfo(updated_tasks);
    cout << "Alice untouched tasks:";
    PrintTasksInfo(untouched_tasks);
    cout << "#################################" << endl;
    // [{"IN_PROGRESS": 3, "TESTING": 1}, {"IN_PROGRESS": 1, "TESTING": 4}]
    
    cout << "Alice all tasks:";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice")); // {"IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}
    cout << "#################################" << endl;

    

    // TEST 2
    std::cout << "\nJack" << std::endl;
 
    std::cout << "Added 1 task" << endl;
    tasks.AddNewTask("Jack");
 
    std::cout << "Performed 1 task" << endl;
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 1);
    cout << "Jack updated tasks:";
    PrintTasksInfo(updated_tasks);// [{"IN_PROGRESS": 1}, {}]
    cout << "Jack untouched tasks:";
    PrintTasksInfo(untouched_tasks);
    cout << "#################################" << endl;

    std::cout << "Added 1 task" << endl;
    tasks.AddNewTask("Jack");
    std::cout << "Performed 2 tasks" << endl;
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 2);
    cout << "Jack updated tasks:";
    PrintTasksInfo(updated_tasks); // [{"IN_PROGRESS": 1, "TESTING": 1}, {}]
    cout << "Jack untouched tasks:";
    PrintTasksInfo(untouched_tasks);
    cout << "#################################" << endl;

    std::cout << "Added 1 task" << endl;
    tasks.AddNewTask("Jack");
    
    cout << "Jack all tasks:";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Jack")); // {"NEW": 1, "IN_PROGRESS": 1, "TESTING": 1}
    cout << "#################################" << endl;
    
    std::cout << "Performed 3 tasks" << endl;
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 3);
    cout << "Jack updated tasks:";
    PrintTasksInfo(updated_tasks); // [{"IN_PROGRESS": 1, "TESTING": 1, "DONE": 1}, {}]
    cout << "Jack untouched tasks:";
    PrintTasksInfo(untouched_tasks);
    cout << "#################################" << endl;
    
    cout << "Jack all tasks:";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Jack")); // {"IN_PROGRESS": 1, "TESTING": 1, "DONE": 1}
    cout << "#################################" << endl;
    std::cout << std::endl;


    //TEST 3
    
    std::cout << "\nLisa" << std::endl;
 
    std::cout << "Added 5 tasks" << endl;
    for (auto i = 0; i < 5; ++i) {
       tasks.AddNewTask("Lisa");
    }
    
    std::cout << "Performed 5 tasks" << endl;
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
    cout << "Lisa updated tasks:";
    PrintTasksInfo(updated_tasks); // [{"IN_PROGRESS": 5}, {}]
    cout << "Lisa untouched tasks:";
    PrintTasksInfo(untouched_tasks);
    cout << "#################################" << endl;

    std::cout << "Performed 5 tasks" << endl;
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
    cout << "Lisa updated tasks:";
    PrintTasksInfo(updated_tasks);  // [{"TESTING": 5}, {}]
    cout << "Lisa untouched tasks:";
    PrintTasksInfo(untouched_tasks);
    cout << "#################################" << endl;

    std::cout << "Performed 1 task" << endl;
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 1);
    cout << "Lisa updated tasks:";
    PrintTasksInfo(updated_tasks); // [{"DONE": 1}, {"TESTING": 4}]
    cout << "Lisa untouched tasks:";
    PrintTasksInfo(untouched_tasks);
    cout << "#################################" << endl;

    std::cout << "Added 5 tasks" << endl;
    for (auto i = 0; i < 5; ++i) {
       tasks.AddNewTask("Lisa");
    }
 
    std::cout << "Performed 2 tasks" << endl;
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 2);
    cout << "Lisa updated tasks:";
    PrintTasksInfo(updated_tasks); // [{"IN_PROGRESS": 2}, {"NEW": 3, "TESTING": 4}]
    cout << "Lisa untouched tasks:";
    PrintTasksInfo(untouched_tasks);
    cout << "#################################" << endl;
    cout << "Lisa all tasks:";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa")); // {"NEW": 3, "IN_PROGRESS": 2, "TESTING": 4, "DONE": 1}
    cout << "#################################" << endl;
 
    std::cout << "Performed 4 tasks" << endl;
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 4);
    cout << "Lisa updated tasks:";
    PrintTasksInfo(updated_tasks);
    cout << "Lisa untouched tasks:";
    PrintTasksInfo(untouched_tasks);
    cout << "#################################" << endl;
    // [{"IN_PROGRESS": 3, "TESTING": 1}, {"IN_PROGRESS": 1, "TESTING": 4}]
    cout << "Lisa all tasks:";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa")); // {"IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}
    cout << "#################################" << endl;
 
    std::cout << "Performed 5 tasks" << endl;
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
    cout << "Lisa updated tasks:";
    PrintTasksInfo(updated_tasks); // [{"TESTING": 4, "DONE": 1}, {"TESTING": 4}]
    cout << "Lisa untouched tasks:";
    PrintTasksInfo(untouched_tasks);
    cout << "#################################" << endl;
 
    cout << "Lisa all tasks:";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa")); // {"TESTING": 8, "DONE": 2}
    cout << "#################################" << endl;
 
    std::cout << "Performed 10 tasks" << endl;
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 10);
    cout << "Lisa updated tasks:";
    PrintTasksInfo(updated_tasks);  // [{"DONE": 8}, {}]
    cout << "Lisa untouched tasks:";
    PrintTasksInfo(untouched_tasks);
    cout << "#################################" << endl;
    
    cout << "Lisa all tasks:";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa")); // {"DONE": 10}
    cout << "#################################" << endl;
 
    std::cout << "Performed 10 tasks" << endl;
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 10);
    cout << "Lisa updated tasks:";
    PrintTasksInfo(updated_tasks); // [{}, {}]
    cout << "Lisa untouched tasks:";
    PrintTasksInfo(untouched_tasks);
    cout << "#################################" << endl;

    cout << "Lisa all tasks:";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa")); // {"DONE": 10}
    cout << "#################################" << endl;
 
    std::cout << "Added 1 task" << endl;
    tasks.AddNewTask("Lisa");
    
    cout << "Lisa all tasks:";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa")); // {"NEW": 1, "DONE": 10}
    cout << "#################################" << endl;
 
    std::cout << "Performed 2 tasks" << endl;
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 2);
    cout << "Lisa updated tasks:";
    PrintTasksInfo(updated_tasks); // [{"IN_PROGRESS": 1}, {}]
    cout << "Lisa untouched tasks:";
    PrintTasksInfo(untouched_tasks);
    cout << "#################################" << endl;

    cout << "Lisa all tasks:";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa")); // {"IN_PROGRESS": 1, "DONE": 10}
    cout << "#################################" << endl;
 
 
    std::cout << "Performed 3 tasks" << endl;
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Bob", 3);
    cout << "Bob updated tasks:";
    PrintTasksInfo(updated_tasks); // [{}, {}]
    cout << "Bob untouched tasks:";
    PrintTasksInfo(untouched_tasks);

    return 0;
}