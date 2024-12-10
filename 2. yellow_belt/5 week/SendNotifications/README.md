### Notification Sending 

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

Example: 

- Input: 
```objectivec
#include <iostream>
#include <string>

using namespace std;

void SendSms(const string& number, const string& message) {
  cout << "Send '" << message << "' to number " << number << endl;
}

void SendEmail(const string& email, const string& message) {
  cout << "Send '" << message << "' to e-mail "  << email << endl;
}


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
```

- Output:
```objectivec
Send 'I have White belt in C++' to number +7-495-777-77-77
Send 'And want a Yellow one' to e-mail na-derevnyu@dedushke.ru
```
