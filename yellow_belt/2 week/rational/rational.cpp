#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <numeric>
#include <exception>

using namespace std;

/*
Список требований, предъявляемых к реализации интерфейса класса Rational:
Конструктор по умолчанию должен создавать дробь с числителем 0 и знаменателем 1.
При конструировании объекта класса Rational с параметрами p и q должно выполняться сокращение дроби p/q.
Если дробь p/q отрицательная, то объект Rational(p, q) должен иметь отрицательный числитель и положительный знаменатель.
Если дробь p/q положительная, то объект Rational(p, q) должен иметь положительные числитель и знаменатель (обратите внимание на случай Rational(-2, -3)).
Если числитель дроби равен нулю, то знаменатель должен быть равен 1.
Разработайте набор юнит-тестов, которые будут проверять корректность реализации класса Rational. Тестировать случай, когда знаменатель равен нулю, не надо.
*/

class Rational {
public:
    Rational(){
        numerator = 0;
        denominator = 1;
    };
    
    Rational(int new_numerator, int new_denominator){
        if(new_denominator == 0){
            throw invalid_argument("Invalid Argument!");
        }

        numerator = new_numerator;
        denominator = new_denominator;

        const int divisor = gcd(numerator, denominator);
        numerator /= divisor;
        denominator /= divisor;

        if(denominator < 0){
            numerator *= -1;
            denominator *= -1;
        } 
    };

    int Numerator() const{
        return numerator;
    };
    int Denominator() const{
        return denominator;
    };


private:
        int numerator;
        int denominator;

};

Rational operator+(const Rational& lhs,const Rational& rhs) {
    const int num = lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator();
    const int den = lhs.Denominator() * rhs.Denominator();
    return Rational(num,den);
};
Rational operator-(const Rational& lhs,const Rational& rhs) {
    const int num = lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator();
    const int den = lhs.Denominator() * rhs.Denominator();
    return Rational(num,den);
};
bool operator==(const Rational& lhs,const Rational& rhs) {
    if(lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator()){
        return true;
    } else{
        return false;
    }
};


Rational operator/(const Rational& lhs,const Rational& rhs) {
    if (rhs.Numerator() == 0) {
        throw domain_error("");
    }

    return Rational(lhs.Numerator() * rhs.Denominator(),lhs.Denominator() * rhs.Numerator());
};
Rational operator*(const Rational& lhs,const Rational& rhs) {
    return Rational(lhs.Numerator() * rhs.Numerator(),lhs.Denominator() * rhs.Denominator());
};

ostream& operator<<(ostream& stream, const Rational& rational){
    stream << rational.Numerator() << '/' << rational.Denominator();
    return stream;
}


istream& operator>>(istream& stream, Rational& r) { //возвращать будем ссылку на поток
    //if (stream) return stream;
    int num = 0;
    int den = 0;
	char c;

	stream >> num >> c >> den;

	if (stream && c == '/')
		r = Rational(num, den);

	return (stream);
}

bool operator<(const Rational& lhs, const Rational& rhs) {

    return (lhs - rhs).Numerator() < 0;
}

bool operator>(const Rational& lhs, const Rational& rhs) {


   return (lhs - rhs).Numerator() > 0;
}



template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
        os << " hint: " << hint;
    }
    throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
    try {
        func();
        cerr << test_name << " OK" << endl;
    } catch (exception& e) {
        ++fail_count;
        cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
        ++fail_count;
        cerr << "Unknown exception caught" << endl;
    }
}

    ~TestRunner() {
    if (fail_count > 0) {
        cerr << fail_count << " unit tests failed. Terminate" << endl;
        exit(1);
    }
}

private:
  int fail_count = 0;
};

void TestDefaultConstructor(){
    Rational r;
    AssertEqual(r.Numerator(),0,"Numerator of default constructor is not equal to 0");
    AssertEqual(r.Denominator(),1,"Denominator of default constructor is not equal to 1");
}

void TestNumDenDivision(){
    Rational r(2,4);
    AssertEqual(r.Numerator(),1,"2/4 -> 1/2: Numerator is not 1");
    AssertEqual(r.Denominator(),2,"2/4 -> 1/2: Denomiantor is not 2");

    Rational r2(4,6);
    AssertEqual(r2.Numerator(),2,"4/6 -> 2/3: Numerator is not 2");
    AssertEqual(r2.Denominator(),3,"4/6 -> 2/3: Denominator is not 3");
}


void TestNegativeRational(){
    Rational r(-1,2);
    AssertEqual(r.Numerator(),-1,"-1/2 -> -1/2: Numerator is not -1");
    AssertEqual(r.Denominator(),2,"-1/2 -> -1/2: Denominator is not 2");

    Rational r2(1,-2);
    AssertEqual(r2.Numerator(),-1,"1/-2 -> -1/2: Numerator is not -1");
    AssertEqual(r2.Denominator(),2,"1/-2 -> -1/2: Denominator is not 2");

    Rational r3(-4,6);
    AssertEqual(r3.Numerator(),-2,"-4/6 -> -2/3: Numerator is not -2");
    AssertEqual(r3.Denominator(),3,"-4/6 -> -2/3: Denominator is not 3");

    Rational r4(4,-6);
    AssertEqual(r4.Numerator(),-2,"4/-6 -> -2/3: Numerator is not -2");
    AssertEqual(r4.Denominator(),3,"4/-6 -> -2/3: Denominator is not 3");
}

void TestPositiveNumbers(){
    Rational r(-1,-2);
    AssertEqual(r.Numerator(),1,"-1/-2 -> 1/2: Numerator is not 1");
    AssertEqual(r.Denominator(),2,"-1/-2 -> 1/2: Denominator is not 2");

    Rational r2(-3,-6);
    AssertEqual(r2.Numerator(),1,"-3/-6 -> 1/2: Numerator is not 1");
    AssertEqual(r2.Denominator(),2,"-3/-6 -> 1/2: Denominator is not 2");
}


void TestDenominatorIfNumeratorZero(){
    Rational r(0,9);
    AssertEqual(r.Numerator(),0,"Numerator is not Zero");
    AssertEqual(r.Denominator(),1,"Denominator is not 1, when Numerator is 0");

    Rational r2(0,-6);
    AssertEqual(r2.Numerator(),0,"Numerator is not Zero");
    AssertEqual(r2.Denominator(),1,"Denominator is not 1, when Numerator is 0");
}


int main() {
    TestRunner runner;
    runner.RunTest(TestDefaultConstructor, "TestDefaultConstructor");
    runner.RunTest(TestNumDenDivision, "TestNumDenDivision");

    runner.RunTest(TestNegativeRational, "TestNegativeRational");
    runner.RunTest(TestPositiveNumbers, "TestPositiveNumbers");

    runner.RunTest(TestDenominatorIfNumeratorZero, "TestDenominatorIfNumeratorZero");


    return 0;
}