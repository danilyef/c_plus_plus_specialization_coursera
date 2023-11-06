/*
You are given the main function, which reads commands from the standard input to work with a set of geometric shapes:

As seen in the code, there are two types of commands:

ADD — add a shape to the set;
PRINT — for each shape in the set, print the name, perimeter, and area.

The program supports three types of shapes: rectangle, triangle, and circle. Their addition is described as follows:

ADD RECT width height — add a rectangle with dimensions width and height (for example, ADD RECT 2 3).

ADD TRIANGLE a b c — add a triangle with sides a, b, and c (for example, ADD TRIANGLE 3 4 5).

ADD CIRCLE r — add a circle with radius r (for example, ADD CIRCLE 5).

Without changing the main function, implement the missing functions and classes:

A base class Figure with pure virtual methods Name, Perimeter, and Area;
Classes Triangle, Rect, and Circle, which inherit from the Figure class and override its virtual methods;
A function CreateFigure that, depending on the input stream's content, creates shared_ptr<Rect>, shared_ptr<Triangle>, or shared_ptr<Circle>.

It is guaranteed that all ADD commands are correct; the dimensions of all shapes are natural numbers not exceeding 1000. Use the value of π as 3.14.



*/


#include <iostream>
#include <string>

using namespace std;

void SendSms(const string& number, const string& message) {
    cout << "Send '" << message << "' to number " << number << endl;
}

void SendEmail(const string& email, const string& message) {
    cout << "Send '" << message << "' to e-mail "  << email << endl;
}

/*
 Реализуйте здесь классы INotifier, SmsNotifier, EmailNotifier
 */

class INotifier {
public:
    virtual void Notify(const string& message) const = 0;

};


class SmsNotifier : public INotifier {
public:
    SmsNotifier(const string& phone_num) : phone_num_(phone_num) {}

    void Notify(const string& message) const override{
        SendSms(phone_num_,message);
    }

private:
    const string phone_num_;
};

class EmailNotifier : public INotifier {
public:
    EmailNotifier(const string& email_adr) : email_adr_(email_adr) {}

    void Notify(const string& message) const override{
        SendEmail(email_adr_,message);
    }

private:
    const string email_adr_;
};



void Notify(INotifier& notifier, const string& message) {
    notifier.Notify(message);
}


int main() {
    SmsNotifier sms{"+7-495-777-77-77"};
    EmailNotifier email{"na-derevnyu@dedushke.ru"};

    Notify(sms, "I have White belt in C++");
    Notify(email, "And want a Yellow one");
    return 0;
}