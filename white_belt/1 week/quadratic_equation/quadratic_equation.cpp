//compute roots of Quadratic equation

#include <iostream>
#include <cmath>

int main(){
    double a,b,c;
    double x1,x2;
    double disriminant;
    std::cin >> a >> b >> c;
    
    if(a != 0){
        disriminant = b*b - 4*a*c;
    
        if (disriminant >= 0){
            x1 = ( -b + sqrt(disriminant))/(2*a);
            x2 = ( -b - sqrt(disriminant))/(2*a);
             
            if (x1 == x2) {
                std::cout << x1; 
            } else {
                std::cout << x1 << ' ' << x2;
            }
        }
            
    } else {
        
        if(b != 0){
            std::cout << -c/b;
        } 
    }   
    return 0;      
}
        
   
    
