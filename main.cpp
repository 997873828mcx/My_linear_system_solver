#include <iostream>
#include<iomanip>
#include<math.h>
#include<stdlib.h>
#include<vector>
#include <cassert>
//using namespace std;
//#define n 3
/*void SwapRows(double mat[n][n+1], int i, int j)
{
    for(int k=0; k<n; k++)
    {
        double temp = mat[i][k];
        mat[i][k]=mat[j][k];
        mat[j][k]=temp;
    }
}
void GaussianElimination(double mat[n][n+1])
{
    for(int col=0; col<n; ++col)
    {
        int MaxValueIndex=col;
        double MaxValue=abs(mat[col][col]);
        for(int row=col+1; row<n;++row)
        {
            if(abs(mat[row][col])>MaxValue)
            {
                MaxValue=mat[row][col];
                MaxValueIndex=row;
            }
        }
        if(MaxValue=0)
        {
            continue;
        }
        else
            SwapRows(mat, col, MaxValueIndex);
        for (int row=col+1; row<n; ++row )
        {
            double f = mat[row][col]/mat[col][col];
            for (int i=col+1; i<n+1; ++i)
            {
                mat[row][i] -= mat[col][i] * f;
            }
        }

    }
}
int main() {
    int n;
    cin>>n;

    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<n+1; ++j)
        {
            cin>>
        }
    }
    double mat[n][n+1];
    GaussianElimination(mat);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}*/
#include <iostream>

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

/*    MyLinearSystemSolver x(10, 10);

    for (std::size_t row=0; row < x.nrows(); ++row) {
        for (std::size_t col=0; col < x.ncols(); ++col) {
            if (row == col) {
                x(row, col) = 1.0;
            }
        }
    }

    std::cout << x << std::endl;*/
    /*x.SwapRows(1,2);
    std::cout << x << std::endl;*/
    MyLinearSystemSolver a = matrix;
    a.GaussianElimination();
    MyLinearSystemSolver solution =
            a.BackSub();
    std::cout << "The solution is: \n"<< solution << std::endl;
    //using verify function to calculate value of A*sol-b
    //MyLinearSystemSolver verify = matrix.MatrixMultiplication(solution) -
    std::cout<<"The verify result A * sol - b is: \n"<< matrix.verify(solution)<<std::endl;



}