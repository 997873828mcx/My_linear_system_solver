//
// Created by Chenxi Ma on 4/25/22.
//
#include <iostream>
#include <cassert>
#include "MyLinearSystemSolver.h"
MyLinearSystemSolver::MyLinearSystemSolver (std::size_t rows, std::size_t cols, double val)
: _rows{rows},
_cols{cols},
_data(rows * cols, val)
{
    assert (rows > 0);
    assert (cols > 0);
}
MyLinearSystemSolver::~MyLinearSystemSolver() {

}
void MyLinearSystemSolver::SwapRows(std::size_t i, std::size_t j)
{

    for(std::size_t k=0; k<_cols; k++)
    {
        double temp = (*this)(i,k);
        (*this)(i,k)=(*this)(j,k);
        (*this)(j,k)=temp;
    }
}
void MyLinearSystemSolver::GaussianElimination()
{
    for(std::size_t col=0; col<_cols-1; ++col)
    {
        std::size_t MaxValueIndex=col;
        double MaxValue=std::abs((*this)(col,col));
        for(std::size_t row=col+1; row<_rows;++row)
        {
            if(std::abs((*this)(row,col))>std::abs(MaxValue))
            {
                MaxValue=(*this)(row,col);
                MaxValueIndex=row;
            }
        }
        if(MaxValue==0)
        {
            continue;
        }
        if(MaxValueIndex!=col)
            this->SwapRows(col, MaxValueIndex);
      //  std::cout<< (*this) <<std::endl;
        for (std::size_t row=col+1; row<_rows; ++row )
        {
            //(*this)(row,col)=0;
            double f = (*this)(row,col)/(*this)(col,col);
            for (std::size_t i=col; i<_cols; ++i)
            {
                (*this)(row,i) -= (*this)(col,i) * f;
            }
        }

    }
}

MyLinearSystemSolver MyLinearSystemSolver::BackSub()
{
    MyLinearSystemSolver x(_rows,1);

    for (int i = _rows-1; i>=0; --i)
    {
        x._data[i] = (*this)(i,_rows);
        for (std::size_t j=i+1; j<_rows; ++j)
        {
            x._data[i] -= (*this)(i,j) * x._data[j];
        }

        x._data[i] = x._data[i]/(*this)(i,i);
    }
    return x;
}

MyLinearSystemSolver MyLinearSystemSolver::MatrixMultiplication(MyLinearSystemSolver &x)
{
    //补上确保维度要相同的代码
    MyLinearSystemSolver y(_rows,x._cols);
    for (std::size_t i=0; i<_rows; ++i)
    {
        for (std::size_t j=0; j<x._cols; ++j) {
            for (std::size_t k=0; k<_cols; ++k)
                y(i, j) += (*this)(i,k) * x(k,j);
        }
    }
    return y;
}

MyLinearSystemSolver MyLinearSystemSolver::operator-(const MyLinearSystemSolver& x)
{
    MyLinearSystemSolver M(_rows,_cols);
    for (std::size_t i=0; i<_rows; ++i)
    {
        for (std::size_t j=0; j<_cols; ++j)
        {
            M(i,j) = (*this)(i,j) - x(i,j);
        }
    }
    return M;
}

bool MyLinearSystemSolver::operator==(const MyLinearSystemSolver& x)
{
    int n = 0;
    if((_rows != x._rows)||(_cols != x._cols))
    {
        return false;
    }
    else
    {
        for (std::size_t i=0; i<_rows; ++i)
        {
            for (std::size_t j=0; j<_cols; ++j)
            {
                if ((*this)(i,j)!=x(i,j))
                    n+=n;
            }
        }
        if (n==0)
            return true;
        else
            return false;
    }
}
//MyLinearSystemSolver&
MyLinearSystemSolver MyLinearSystemSolver::verify(const MyLinearSystemSolver& sol)
{
    MyLinearSystemSolver y(_rows,1);
    for (std::size_t i=0; i<_rows; ++i)
    {
            for (std::size_t k=0; k<_rows; ++k)
                y(i, 0) += (*this)(i,k) * sol(k,0);
    }
    for (std::size_t i=0; i<_rows; ++i)
    {
        y(i,0) -= (*this)(i,_cols-1);
    }
    return y;
}
std::ostream& operator<< (std::ostream& os, const MyLinearSystemSolver& a) {

    for (std::size_t row=0; row < a.nrows(); ++row) {
        for (std::size_t col=0; col < a.ncols(); ++col) {
            os << a(row, col) << " ";
        }
        os << std::endl;
    }

    return os;
}