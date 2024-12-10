### Programming Task: Rational Class 

### Description 
In this problem, you need to develop a class to represent rational numbers and embed it into the C++ type system so that it can be used naturally.
```objectivec
#include <iostream>
using namespace std;

int main() {
    // Набор юнит-тестов для вашей реализации
    cout << "OK" << endl;
    return 0;
}
```

### Part 1 
In the first part, you need to implement the *Rational* class, which is a rational number of the form *p/q*, where *p* is an integer and *q* is a natural number. It should have the following interface:
```objectivec
class Rational {
public:
  Rational();
  Rational(int numerator, int denominator);

  int Numerator() const;
  int Denominator() const;
};
```
The *Rational* class must ensure that *p/q* is an irreducible fraction. For example, code
```objectivec
Rational r(4, 6);
cout << r.Numerator() << '/' << r.Denominator();
```
should output "2/3" - which is why we make *Rational* a class, not a struct. The structure would allow this invariant to be violated:
```objectivec
struct Rational {
    int numerator, denominator;
};

Rational r{2, 3};
r.numerator = 6; // Violated irreducibility invariant
```

List of requirements for the implementation of the *Rational* class interface:

- The default constructor should create a fraction with numerator *0* and denominator *1*.
- When constructing an object of the Rational class with parameters *p* and *q*, the fraction *p/q* must be reduced (this is where the Greatest Common Divisor solution can come in handy).
- If the fraction *p/q* is negative, then the object *Rational(p, q)* must have a negative numerator and a positive denominator.
- If the fraction *p/q* is positive, then the object *Rational(p, q)* must have a positive numerator and denominator (note the case of *Rational(-2, -3)*).
- If the numerator of the fraction is equal to zero, then the denominator must be equal to *1*.

**It is guaranteed that none of the tests that will test your implementation will have a denominator equal to zero.**

### Part 2 
Implement the ==, +, and - operators for the *Rational* class so that fractional operations can be written naturally. For example, the following code must be valid:
```objectivec
const Rational r = Rational(1, 2) + Rational(1, 3) - Rational(1, 4);
if (r == Rational(7, 12)) {
  cout << "equal";
}
```

### Part 3 
Similar to the previous part, implement the * and / operators. For example, the following code must be valid:
```objectivec
const Rational r = Rational(1, 2) * Rational(1, 3) / Rational(1, 4);
if (r == Rational(2, 3)) {
  cout << "equal";
}
```

**It is guaranteed that none of the tests that will test your implementation will perform division by zero.**

### Part 4 
In this part, you need to implement the input and output operators for the *Rational* class. As a result, the following code should work for you, for example
```objectivec
Rational r;
cin >> r;
cout << r;
```

### Part 5 
Finally, you need to implement the ability to use objects of the *Rational* class as elements of the *set* container and keys in the *map* container. Example:
```objectivec
set<Rational> rationals;
rationals.insert(Rational(1, 2));
rationals.insert(Rational(1, 3));
map<Rational, string> name;
name[Rational(1, 2)] = "one half";
```
