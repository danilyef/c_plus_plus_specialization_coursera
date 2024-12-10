#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <memory>
#include <vector>

using namespace std;


class Figure{
public:
    virtual string Name() const = 0;
    virtual double Perimeter() const = 0;
    virtual double Area() const = 0;

private:
    const string type_ = "figure";

};


class Rect : public Figure {
public:
    Rect(const int& width, const int& height) : width_(width), height_(height) {}

    string Name() const override{
        return type_;
    };

    double Perimeter() const override{
        return 2 * width_ + 2 * height_;
    };

    double Area() const override{
        return width_ * height_;
    };

private:
    const double width_;
    const double height_;
    const string type_ = "RECT";
};


class Triangle : public Figure {
public:
    Triangle(const int& a, const int& b,  const int& c ) : a_(a), b_(b), c_(c) {}

    string Name() const override{
        return type_;
    };

    double Perimeter() const override{
        return a_ + b_ + c_;
    };

    double Area() const override{
        double s = (a_ + b_ + c_)/2;
        return std::sqrt(s * (s - a_) * (s - b_) * (s - c_));
    };

private:
    const double a_;
    const double b_;
    const double c_;
    const string type_ = "TRIANGLE";
};


class Circle : public Figure {
public:
    Circle(const int& r) : r_(r) {}

    string Name() const override{
        return type_;
    };

    double Perimeter() const override{
        return 2 * r_ * 3.14;
    };

    double Area() const override{
        return 3.14 * r_ * r_;
    };

private:
    const int r_;
    const string type_ = "CIRCLE";
};


std::shared_ptr<Figure> CreateFigure(std::istringstream& ss){
    string figure_name;
    ss >> figure_name;
    if (figure_name == "RECT"){
        int w,h;
        ss >> w >> h;
        return std::make_shared<Rect>(w,h); 
    } else if(figure_name == "TRIANGLE"){
        int a,b,c;
        ss >> a >> b >> c;
        return std::make_shared<Triangle>(a,b,c);
    } else if(figure_name == "CIRCLE"){
        int r;
        ss >> r;
        return std::make_shared<Circle>(r);
    } else{
        throw std::invalid_argument( "Wrong name of the figure");
    }

};
 




int main() {
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line); ) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD") {
            figures.push_back(CreateFigure(is));
        } else if (command == "PRINT") {
            for (const auto& current_figure : figures) {
                cout << fixed << setprecision(3)
                    << current_figure->Name() << " "
                    << current_figure->Perimeter() << " "
                    << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}


