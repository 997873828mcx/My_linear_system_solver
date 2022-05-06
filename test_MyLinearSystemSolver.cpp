//
// Created by Chenxi Ma on 4/30/22.
//
#include <vector>
#include <iostream>
#include <cassert>
#include "MyLinearSystemSolver.h"
#include <math.h>
int main(){
    std::cout<<"Now we verify the root solver of the matrix which appeared in 'Example of the algorithm' "
               "section of wikipedia" << std::endl;
    MyLinearSystemSolver x(3,4);
    std::vector<double> container{2.0, 1.0, -1.0, 8.0, -3.0, -1.0, 2.0, -11.0,
                                  -2.0, 1.0, 2.0, -3.0};
    for (std::size_t row=0; row< x.nrows(); ++row){
        for (std::size_t col=0; col < x.ncols(); ++col){
            x(row,col)=container[row * (x.ncols())+col];
        }
    }
    //this is the result of x,y, and z
    //of above matrix, which is provided at wikipedia
    std::vector<double> container2{2.0, 3.0, -1.0};
    MyLinearSystemSolver y(3,1);
    for (std::size_t row=0; row< y.nrows(); ++row){
        y(row,0)=container2[row];
    }
    x.GaussianElimination();
    MyLinearSystemSolver solution = x.BackSub();
    std::cout<<"testing root finding"<<std::endl;
    assert(solution==y);
    std::cout << "all tests passed" << std::endl;
}
