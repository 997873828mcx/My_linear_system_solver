#include <iostream>
#include<math.h>
#include "MyLinearSystemSolver.h"

int main() {

    std::size_t n;
    std::cout<<"please input the dimension of the equations"<<std::endl;
    std::cin>>n;
    std::cout<<"please input the parameters of linear equations"<<std::endl;
    MyLinearSystemSolver matrix(n,n+1);
    for (std::size_t row=0; row< matrix.nrows(); ++row){
        for (std::size_t col=0; col < matrix.ncols(); ++col){
            std::cin>>matrix(row,col);
        }
    }
    MyLinearSystemSolver a = matrix;
    a.GaussianElimination();
    MyLinearSystemSolver solution =
            a.BackSub();
    std::cout << "The solution is: \n"<< solution << std::endl;

    //using verify function to calculate value of A*sol-b
    std::cout<<"The verify result A * sol - b is: \n"<< matrix.verify(solution)<<std::endl;


}