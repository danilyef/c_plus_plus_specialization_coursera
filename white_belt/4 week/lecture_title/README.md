### Programming Assignment: LectureTitle Structure 

Given a *LectureTitle* structure:
```objectivec
struct LectureTitle {
  string specialization;
  string course;
  string week;
};
```


Add the *Specialization*, *Course*, *Week* constructor and structures so that the *LectureTitle* object can be created using code
```objectivec
LectureTitle title(
    Specialization("C++"),
    Course("White belt"),
    Week("4th")
);
```

but it was not possible with the following code snippets:
```objectivec
LectureTitle title("C++", "White belt", "4th");

LectureTitle title(string("C++"), string("White belt"), string("4th"));

LectureTitle title = {"C++", "White belt", "4th"};

LectureTitle title = {{"C++"}, {"White belt"}, {"4th"}};

LectureTitle title(
    Course("White belt"),
    Specialization("C++"),
    Week("4th")
);

LectureTitle title(
    Specialization("C++"),
    Week("4th"),
    Course("White Belt")
);
```