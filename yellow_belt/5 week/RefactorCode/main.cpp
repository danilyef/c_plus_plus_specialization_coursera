/*
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