### Programming Task: Issue Tracker 


Implement the _TeamTasks_ class, which allows you to store statistics on the status of tasks of the development team:
```objectivec

enum class TaskStatus {
  NEW,          
  IN_PROGRESS,  
  TESTING,      
  DONE         
};


using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
  const TasksInfo& GetPersonTasksInfo(const string& person) const;
  
  void AddNewTask(const string& person);
  
  tuple<TasksInfo, TasksInfo> PerformPersonTasks(
      const string& person, int task_count);
};

```
The _PerformPersonTasks_ method must implement the following algorithm:

1. Consider all the outstanding tasks of the person developer.
2. Let's sort them by status: first, all tasks in the NEW status, then all tasks in the IN_PROGRESS status, and, finally, tasks in the TESTING status.
3. Consider the first task_count of tasks and move each of them to the next status in accordance with the natural order: NEW → IN_PROGRESS → TESTING → DONE.
4. Let's return a tuple of two elements: information about the statuses of updated tasks (including those that turned out to be in the DONE status) and information about the statuses of the remaining tasks that were not completed.

*task_count* is guaranteed to be a positive number. If *task_count* is greater than the current number of outstanding developer tasks, it is sufficient to assume that *task_count* is equal to the number of outstanding tasks: in this case, there is no need to update the status of any task twice.

In addition, it is guaranteed that the _GetPersonTasksInfo_ method will not be called for a developer who does not have tasks.

### An example of how the PerformPersonTasks method works 
Suppose a particular developer has 10 tasks with the following statuses:

- NEW — 3
- IN_PROGRESS — 2
- TESTING — 4
- DONE — 1

The _PerformPersonTasks_ command arrives with the *task_count = 4* parameter, which means that the status is updated for 3 tasks from *NEW* to *IN_PROGRESS* and for 1 task from *IN_PROGRESS* to *TESTING*. Thus, the new task statuses will be as follows:

- IN_PROGRESS - 3 updated, 1 old
- TESTING - 1 updated, 4 old
- DONE - 1 old

In this case, you need to return a tuple of 2 dictionaries:

- Updated tasks: IN_PROGRESS - 3, TESTING - 1.
- Not updated tasks, excluding completed ones: IN_PROGRESS - 1, TESTING - 4.

**Dictionaries should not contain extra elements**, that is, statuses that correspond to zero tasks.

### Note 
Updating a dictionary at the same time as iterating over it can lead to unpredictable results. If such a need arises, it is recommended that you first collect information about updates in a separate temporary dictionary, and then apply them to the main dictionary.

### Example 
```objectivec
void PrintTasksInfo(TasksInfo tasks_info) {
  cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
      ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
      ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
      ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
  TeamTasks tasks;
  tasks.AddNewTask("Ilia");
  for (int i = 0; i < 3; ++i) {
    tasks.AddNewTask("Ivan");
  }
  cout << "Ilia's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
  cout << "Ivan's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
  
  TasksInfo updated_tasks, untouched_tasks;
  
  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);
  
  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);

  return 0;
}

```

**Output**
```commandline
Ilia's tasks: 1 new tasks, 0 tasks in progress, 0 tasks are being tested, 0 tasks are done
Ivan's tasks: 3 new tasks, 0 tasks in progress, 0 tasks are being tested, 0 tasks are done
Updated Ivan's tasks: 0 new tasks, 2 tasks in progress, 0 tasks are being tested, 0 tasks are done
Untouched Ivan's tasks: 1 new tasks, 0 tasks in progress, 0 tasks are being tested, 0 tasks are done
Updated Ivan's tasks: 0 new tasks, 1 tasks in progress, 1 tasks are being tested, 0 tasks are done
Untouched Ivan's tasks: 0 new tasks, 1 tasks in progress, 0 tasks are being tested, 0 tasks are done
```