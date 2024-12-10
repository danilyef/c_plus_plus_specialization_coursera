### Figures 

You are given the main function, which reads commands from the standard input to work with a set of geometric shapes:

As seen in the code, there are two types of commands:

- ADD — add a shape to the set;
- PRINT — for each shape in the set, print the name, perimeter, and area.

The program supports three types of shapes: rectangle, triangle, and circle. Their addition is described as follows:

- ADD RECT width height — add a rectangle with dimensions width and height (for example, ADD RECT 2 3).

- ADD TRIANGLE a b c — add a triangle with sides a, b, and c (for example, ADD TRIANGLE 3 4 5).

- ADD CIRCLE r — add a circle with radius r (for example, ADD CIRCLE 5).

Without changing the main function, implement the missing functions and classes:

A base class Figure with pure virtual methods Name, Perimeter, and Area;
Classes Triangle, Rect, and Circle, which inherit from the Figure class and override its virtual methods;
A function CreateFigure that, depending on the input stream's content, creates shared_ptr<Rect>, shared_ptr<Triangle>, or shared_ptr<Circle>.

It is guaranteed that all ADD commands are correct; the dimensions of all shapes are natural numbers not exceeding 1000. Use the value of π as 3.14.



main function: 

- Input: 
```objectivec
int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
  return 0;
}
```

**Input:**
```objectivec
ADD RECT 2 3
ADD TRIANGLE 3 4 5
ADD RECT 10 20
ADD CIRCLE 5
PRINT
```

**Output:**
```objectivec
RECT 10.000 6.000
TRIANGLE 12.000 6.000
RECT 60.000 200.000
CIRCLE 31.400 78.500
```
