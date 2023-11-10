#### Refactoring the code effectively ####

Refactoring the code effectively

In this task, you are required to modify the code in such a way that it adheres to the principles outlined in the course.

Imagine that this code has been passed down to you as an inheritance from a colleague, and now you are responsible for maintaining and improving it. The first thing you decided to do is to conduct refactoring.

The ultimate goals of refactoring are:

1. Simplify the future maintenance of the code.
2. Reduce the complexity of the code.
3. Simplify the addition of new abstractions to the program.

Evaluation Criteria:
The task will be evaluated based on the following criteria:

1. Effectiveness of code execution.
2. Code duplication.
3. Effectiveness of using code refactoring techniques as shown in the lectures.

Additionally, the code you submit should be compilable.

Task:
Conduct refactoring of the given code.

Code: 

```objectivec
#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Student {
public:

    Student(string name, string favouriteSong) {
        Name = name;
        FavouriteSong = favouriteSong;
    }

    void Learn() {
        cout << "Student: " << Name << " learns" << endl;
    }

    void Walk(string destination) {
        cout << "Student: " << Name << " walks to: " << destination << endl;
        cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;
    }

    void SingSong() {
        cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;
    }

public:
    string Name;
    string FavouriteSong;
};


class Teacher {
public:

    Teacher(string name, string subject) {
        Name = name;
        Subject = subject;
    }

    void Teach() {
        cout << "Teacher: " << Name << " teaches: " << Subject << endl;
    }

    void Walk(string destination) {
        cout << "Teacher: " << Name << " walks to: " << destination << endl;
    }

public:
    string Name;
    string Subject;
};


class Policeman {
public:
    Policeman(string name) {
        Name = name;
    }

    void Check(Teacher t) {
        cout << "Policeman: " << Name << " checks Teacher. Teacher's name is: " << t.Name << endl;
    }

    void Check(Student s) {
        cout << "Policeman: " << Name << " checks Student. Student's name is: " << s.Name << endl;
    }

    void Check(Policeman p) {
        cout << "Policeman: " << Name << " checks Policeman. Policeman's name is: " << p.Name << endl;
    }

    void Walk(string destination) {
        cout << "Policeman: " << Name << " walks to: " << destination << endl;
    }

public:
    string Name;
};


void VisitPlaces(Teacher t, vector<string> places) {
    for (auto p : places) {
        t.Walk(p);
    }
}

void VisitPlaces(Student s, vector<string> places) {
    for (auto p : places) {
        s.Walk(p);
    }
}

void VisitPlaces(Policeman pol, vector<string> places) {
    for (auto p : places) {
        pol.Walk(p);
    }
}


int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
```

