### Programming Task: Tests for the Rational class 


The _Rational_ class represents a rational number and has the following interface
```objectivec
class Rational {
public:
  Rational();
  Rational(int numerator, int denominator);
  int Numerator() const;
  int Denominator() const;
};
```
List of requirements for implementing the _Rational_ class interface:

- The default constructor should create a fraction with numerator 0 and denominator 1.
- When constructing an object of class _Rational_ with parameters p and q, reduction of the fraction p/q must be performed.
- If p/q is negative, then the _Rational(p, q)_ object must have a negative numerator and a positive denominator.
- If p/q is positive, then the _Rational(p, q)_ object must have a positive numerator and denominator (note the case of _Rational(-2, -3)_).
- If the numerator of a fraction is zero, then the denominator must be equal to 1.

Develop a set of unit tests that will check the correct implementation of the _Rational_ class. **You don't need to test the case when the denominator is zero**.


