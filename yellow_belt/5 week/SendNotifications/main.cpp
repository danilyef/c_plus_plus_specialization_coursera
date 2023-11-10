/*
Notification Sending
In this task, you need to develop classes SmsNotifier and EmailNotifier that send notifications as SMS and email, respectively, as well as an abstract base class for them.

You are given the functions SendSms and SendEmail, which simulate sending SMS and email.

void SendSms(const string& number, const string& message);
void SendEmail(const string& email, the string& message);

Develop:

1. An abstract base class INotifier with one purely virtual method void Notify(const string& message).

2. The SmsNotifier class, which:

   - is a subclass of the INotifier class.
   - accepts one parameter of type string in its constructor, which is the phone number.
   - overrides the Notify method and calls the SendSms function from within it.

3. The EmailNotifier class, which:

   - is a subclass of the INotifier class.
   - accepts one parameter of type string in its constructor, which is the email address.
   - overrides the Notify method and calls the SendEmail function from within it.

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