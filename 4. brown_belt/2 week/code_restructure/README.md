### Programming Assignment: Code Restructuring

In the previous video, we demonstrated how namespaces can be used to structure code and divide it into logical blocks. In this task, you will practice this concept.

You are given a program that can compute various aggregations of a set of integers: minimum, maximum, sum, average, and mode. Each aggregation in the program is implemented as a separate class, which is a descendant of the abstract base class `StatsAggregator`. These classes are named:

- `SumStatsAggregator`
- `MinStatsAggregator`
- `MaxStatsAggregator`
- `AverageStatsAggregator`
- `ModeStatsAggregator`

As you can see, all these classes share a common suffix. Its frequent usage can clutter the code and make it less readable (this is especially true for the class implementation file and the test file). Perform the following code transformations:

1. Remove the common suffix from the names of the `StatsAggregator` descendants (for example, rename `SumStatsAggregator` to `Sum`).
2. Remove the common suffix from the test names (for example, rename `TestSumStatsAggregator` to `TestSum` (see the unit tests in the files `stats_aggregator.h` and `stats_aggregator_test.cpp` below)).
3. Place the descendant classes of `StatsAggregator`, as well as their tests, into the namespace `StatsAggregators`.
4. Update the file `main.cpp` so that it works correctly with the new code structure (including invoking the unit tests).
5. Leave the base class `StatsAggregator` in the global namespace.

As mentioned in the video, moving the base class to a namespace is a matter of taste. In this task, we ask you to leave it in the global namespace because it allows us to avoid modifying the code that works with the abstract interface rather than its implementations. For the sake of experimentation, after submitting the task, you may place `StatsAggregator` in the `StatsAggregators` namespace and see what other code needs to be changed and whether it becomes simpler with this change.