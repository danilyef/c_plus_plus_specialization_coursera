#include <iostream>
#include <numeric>
#include <exception>
#include <sstream>
using namespace std;

// class Rational



class Rational {
public:
    Rational(){
        numerator = 0;
        denominator = 1;
    };
    
    Rational(int new_numerator, int new_denominator){
        if(new_denominator == 0){
            throw invalid_argument("Invalid argument");
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
        throw domain_error("Division by zero");
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

int main() {    
    Rational x;
    Rational y;
    char z;

    

    try{

        cin >> x >> z >> y; 
        if(z == '+'){
            cout << x + y;
        } else if(z == '-'){
            cout << x - y;
        }else if(z == '/'){
            cout << x / y;
        }else if(z == '*'){
            cout << x * y;
        }
    }catch(exception& ex){
        cout << ex.what() << endl;

    }
    return 0;


}
