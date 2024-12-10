### Programming Task: `operator[]` in the `Polynomial` class

In the lectures, we clearly demonstrated that constancy limits the set of operations you can perform on an object, protecting it from unwanted changes. However, the possibilities of constancy are limited, and in some cases, it does not achieve the desired effect. In such situations, the type system comes to the rescue, allowing you to create classes with the required properties. In this task, we will explore such a situation.

You are provided with an implementation of the `Polynomial` template, which represents a polynomial of a single variable. The type `T` of this template specifies the type of the coefficients and the variable. That is, `Polynomial<int>` is a polynomial with integer coefficients from an integer variable, and `Polynomial<double>` is a polynomial with floating-point coefficients from a floating-point variable. Let's consider the interface of the `Polynomial<T>` class:

```cpp
template<typename T>
class Polynomial {
private:
  ...
public:
  // Takes a vector of coefficients (coefficients are given from lowest to highest)
  // For example, Polynomial({10, 2, 3, 4}) creates the polynomial 4*x^3 + 3*x^2 + 2*x + 10
  Polynomial(vector<T> coeffs);

  // Creates a polynomial where all coefficients are zero
  Polynomial();

  // Similar to the constructor from a vector but accepts a pair of iterators
  template<typename Iterator>
  Polynomial(Iterator first, Iterator last);

  // Equality and inequality operators. Two polynomials are equal if and only if
  // their corresponding coefficients are pairwise equal
  bool operator ==(const Polynomial& other) const;
  bool operator !=(const Polynomial& other) const;

  // Returns the degree of the polynomial — the highest degree for which the coefficient is non-zero.
  // For example, the degree of 2*x is 1, the degree of 4*x^5 + x^3 - 10 is 5,
  // and the degree of 5 is zero.
  // This method works in O(1)
  int Degree() const;

  Polynomial& operator +=(const Polynomial& r);
  Polynomial& operator -=(const Polynomial& r);

  // Returns the coefficient for a given degree.
  // If the passed value exceeds the polynomial's degree, the method returns 0
  T operator [](size_t degree) const;
  // Computes the value of the polynomial at a point with the given value
  T operator ()(const T& x) const;

  using const_iterator = typename std::vector<T>::const_iterator;

  // Iterators to the polynomial's coefficients
  const_iterator begin() const;
  const_iterator end() const;
};
```

In the above implementation, there is only one way to set the values of a polynomial's coefficients — by passing them to the constructor. However, in practice, it might be useful to set coefficients one by one (this is especially useful for sparse polynomials):

```cpp
Polynomial<int> p;
p[1] = 5;
p[24] = -8;
p[61] = 12;
p[314] = 272;
```

Your task is to add this feature, specifically implementing a non-const `operator[]` for the `Polynomial` template that:

1. Allows setting the coefficient for a given degree (as in the example above).
2. Allows reading the coefficient for a given degree (i.e., code like `int cv = p[4];` should work).
3. Works in `O(1)` when the degree of the polynomial does not change.
4. Does not change the degree of the polynomial if no write operation occurs.

The last requirement can be expressed by the following test:

```cpp
Polynomial<int> p;
p[2] = 1;
ASSERT_EQUAL(p.Degree(), 2);
int x = p[5];
ASSERT_EQUAL(x, 0);
ASSERT_EQUAL(p.Degree(), 2); // We didn't write anything to p[5], so the polynomial's degree didn't change
```

See also the unit tests in the provided solution template.

Submit a `cpp` file with the full implementation of the `Polynomial` template.