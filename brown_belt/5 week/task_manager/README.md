#### Programming Task: "Task Tracker"

Implement the `TeamTasks` class to keep track of task statuses for a team of developers.

```cpp
// Enumeration for task status
enum class TaskStatus {
  NEW,          // new
  IN_PROGRESS,  // in development
  TESTING,      // in testing
  DONE          // completed
};

// Type alias for map<TaskStatus, int>,
// which allows tracking the count of tasks in each status
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
  // Retrieve the task status statistics for a specific developer
  const TasksInfo& GetPersonTasksInfo(const string& person) const;
  
  // Add a new task (with status NEW) for a specific developer
  void AddNewTask(const string& person);
  
  // Update statuses of a specified number of tasks for a specific developer,
  // see details below
  tuple<TasksInfo, TasksInfo> PerformPersonTasks(
      const string& person, int task_count);
};
```

The `PerformPersonTasks` method should follow this algorithm:

1. Review all of developer `person`'s incomplete tasks.
2. Sort these tasks by status: first all `NEW`, then all `IN_PROGRESS`, and finally `TESTING`.
3. Take the first `task_count` tasks and change each to the next status in the natural order: `NEW → IN_PROGRESS → TESTING → DONE`.
4. Return a tuple of two elements: 
   - Information on the statuses of updated tasks (including any moved to `DONE`).
   - Information on the statuses of other remaining incomplete tasks.

It’s guaranteed that `task_count` is a positive integer. If `task_count` exceeds the current number of incomplete tasks, treat `task_count` as equal to the number of incomplete tasks—no need to update the status of any task twice in this case.

Additionally, the method `GetPersonTasksInfo` is guaranteed not to be called for a developer with no tasks.

**Example of `PerformPersonTasks` Execution**

Suppose a developer has 10 tasks with the following statuses:

- `NEW` — 3
- `IN_PROGRESS` — 2
- `TESTING` — 4
- `DONE` — 1

A `PerformPersonTasks` command with `task_count = 4` would update the statuses for 3 `NEW` tasks to `IN_PROGRESS` and for 1 `IN_PROGRESS` task to `TESTING`. The new task statuses would then be:

- `IN_PROGRESS` — 3 updated, 1 old
- `TESTING` — 1 updated, 4 old
- `DONE` — 1 old

This would return a tuple with two dictionaries:

- **Updated tasks**: `IN_PROGRESS` — 3, `TESTING` — 1.
- **Unchanged tasks, excluding completed ones**: `IN_PROGRESS` — 1, `TESTING` — 4.

Dictionaries should not contain extra elements, meaning statuses with zero tasks should be omitted.

**Note**
Updating a dictionary while iterating over it can lead to unpredictable results. If needed, gather updates in a temporary dictionary first, then apply them to the main dictionary.

```cpp
// We accept the dictionary by value to allow access to
// missing keys with [] and get a default value of 0,
// without modifying the original dictionary.
void PrintTasksInfo(TasksInfo tasks_info) {
  cout << tasks_info[TaskStatus::NEW] << " new tasks"
       << ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress"
       << ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested"
       << ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
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

**Expected Output**

```
Ilia's tasks: 1 new tasks, 0 tasks in progress, 0 tasks are being tested, 0 tasks are done
Ivan's tasks: 3 new tasks, 0 tasks in progress, 0 tasks are being tested, 0 tasks are done
Updated Ivan's tasks: 0 new tasks, 2 tasks in progress, 0 tasks are being tested, 0 tasks are done
Untouched Ivan's tasks: 1 new tasks, 0 tasks in progress, 0 tasks are being tested, 0 tasks are done
Updated Ivan's tasks: 0 new tasks, 1 tasks in progress, 1 tasks are being tested, 0 tasks are done
Untouched Ivan's tasks: 0 new tasks, 1 tasks in progress, 0 tasks are being tested, 0 tasks are done
```
