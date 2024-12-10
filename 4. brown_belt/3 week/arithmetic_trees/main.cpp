#include "Common.h"
#include "test_runner.h"

#include <sstream>

using namespace std;

string Print(const Expression* e) {
  if (!e) {
    return "Null expression provided";
  }
  stringstream output;
  output << e->ToString() << " = " << e->Evaluate();
  return output.str();
}

class ExpressionValue: public Expression {
public:

  ExpressionValue(int value_) : value(value_) {}
  int Evaluate() const override{
    return value;
  };
  std::string ToString() const override{
    return std::to_string(Evaluate());
  };

private:
  int value;
};



class ExpressionSum: public Expression {
public:


  ExpressionSum(ExpressionPtr left_, ExpressionPtr right_) : left(std::move(left_)),right(std::move(right_)) {}
  int Evaluate() const override{
    return left->Evaluate() + right->Evaluate();
  };

  std::string ToString() const override{
    return "(" + left->ToString() + ")" + "+" + "(" + right->ToString() + ")";
  };

private:
  ExpressionPtr left, right;
};

class ExpressionProduct: public Expression {
public:

  ExpressionProduct(ExpressionPtr left_, ExpressionPtr right_) : left(std::move(left_)),right(std::move(right_)) {}
  int Evaluate() const override{
    return left->Evaluate() * right->Evaluate();
  };

  std::string ToString() const override{
    return "(" + left->ToString() + ")" + "*" + "(" + right->ToString() + ")" ;
  };


private:
  ExpressionPtr left, right;
};


void Test() {
  ExpressionPtr e1 = Product(Value(2), Sum(Value(3), Value(4)));
  ASSERT_EQUAL(Print(e1.get()), "(2)*((3)+(4)) = 14");

  ExpressionPtr e2 = Sum(std::move(e1), Value(5));
  ASSERT_EQUAL(Print(e2.get()), "((2)*((3)+(4)))+(5) = 19");

  ASSERT_EQUAL(Print(e1.get()), "Null expression provided");
}



ExpressionPtr Value(int value){
  return make_unique<ExpressionValue>(value);
};

ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right){
  return make_unique<ExpressionSum>(std::move(left),std::move(right));
};

ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right){
  return make_unique<ExpressionProduct>(std::move(left),std::move(right));
};


int main() {
  TestRunner tr;
  RUN_TEST(tr, Test);
  return 0;
}