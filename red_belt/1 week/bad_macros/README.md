#### Programming Assignment "Bad Macro" ####

You are given a macro that prints two values passed to it into the given output stream. There is a drawback in the implementation of the macro that limits its applicability in real programs. Your task is to identify and eliminate the drawback.

```cpp
#define PRINT_VALUES(out, x, y) out << (x) << endl; out << (y) << endl
```