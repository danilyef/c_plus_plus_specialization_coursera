#include <iostream>
#include <algorithm>
#include <deque>
#include <string>

using namespace std;




int main() {
    std::deque<std::string> math_expr;
    int x,y;
    size_t N;
    std::string op;
    
    std::cin >> x >> N;
    math_expr.push_back(std::to_string(x));
    for(int i = 0; i < N; ++i){
        cin >> op >> y;
        math_expr.push_front("(");
        math_expr.push_back(") ");
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