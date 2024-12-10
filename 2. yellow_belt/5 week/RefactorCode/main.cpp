#include <iostream>
#include <string>
#include <vector>

#include <memory>

 

using namespace std;

 

class Person {

public:

    Person(string name,string type) : name_(name), type_(type) {};

    string get_name() const {return name_;}
    string get_type() const {return type_;}
    virtual void Walk(const string& destination) const = 0;

private:
    const string name_;
    const string type_;

};



 

class Student : public Person {

public:

    Student(string name, string favouriteSong) : Person(name,"Student"), favourite_song_(favouriteSong) {}

 

    void Learn() const {
        cout << "Student: " << get_name() << " learns" << endl;
    }

 

    void Walk(const string& destination) const override {
        cout << "Student: " << get_name() << " walks to: " << destination << endl;
        SingSong();
    }

 

    void SingSong() const {
        cout << "Student: " << get_name() << " sings a song: " << favourite_song_ << endl;
    }

 

private:
    const string favourite_song_;
};


 

class Teacher : public Person {

public:

    Teacher(string name, string subject) : Person(name,"Teacher"), subject_(subject) {}

    void Teach() const {
        cout << "Teacher: " << get_name() << " teaches: " << subject_ << endl;
    }

 

    void Walk(const string& destination) const override {
        cout << "Teacher: " << get_name() << " walks to: " << destination << endl;
    }

 

private:
    const string subject_;

};


 

class Policeman : public Person{

public:

    Policeman(const string& name) : Person(name,"Policeman") {}

    void Check (const Person& p ) const{
        cout << "Policeman: " << get_name() << " checks " << p.get_type() << ". " << p.get_type() << "'s name is: " << p.get_name() << endl;
    }

    void Walk(const string& destination) const override {
        cout << "Policeman: " << get_name() << " walks to: " << destination << endl;
    }

};


 

void VisitPlaces(const Person& pers, vector<string> places) {
    for (auto p : places) {
        pers.Walk(p);
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