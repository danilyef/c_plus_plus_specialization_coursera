/*

Construction of an arithmetic expression: Part 2

Implement the construction of an arithmetic expression according to the following scheme:

Initially, there is an expression consisting of some integer x.
At each step, a certain operation is applied to the current expression: 
- addition of a number
- subtraction of a number
- multiplication by a number or division by a number; 

Modify the solution from the previous part to enclose the previous expression in parentheses only when the current operation has a higher priority than the previous one.


*/


#include <iostream>
#include <algorithm>
#include <deque>
#include <string>

using namespace std;




int main() {
    std::deque<std::string> math_expr;
    int x,y;
    size_t N;
    std::string op, prev_op;
    
    std::cin >> x >> N;
    math_expr.push_back(std::to_string(x));
    for(int i = 0; i < N; ++i){
        cin >> op >> y;
        
        if((prev_op == "-"  || prev_op == "+") && (op == "*"  || op == "/")){
            math_expr.push_front("(");
            math_expr.push_back(")");   
        }
        prev_op = op;
        math_expr.push_back(" ");
        math_expr.push_back(op);
        math_expr.push_back(" ");
        math_expr.push_back(std::to_string(y));
    }

    for (string value : math_expr) {
        std::cout << value;
    }
    std::cout << std::endl;

    return 0;
}