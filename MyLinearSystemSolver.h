//
// Created by Chenxi Ma on 4/25/22.
//

#ifndef LINEAR_SYSTEM_SOLVER_MyLinearSystemSolver_H
#define LINEAR_SYSTEM_SOLVER_MyLinearSystemSolver_H
#include <vector>
#include <iostream>
#include <cassert>

class MyLinearSystemSolver {
public:
    MyLinearSystemSolver (std::size_t , std::size_t , double val=0.0);
    ~MyLinearSystemSolver();
    inline std::size_t ncols() const { return _cols;}
    inline std::size_t nrows() const { return _rows;}
    inline double& operator()(std::size_t row, std::size_t col) {
        assert (row >= 0 && row < _rows);
        assert (col >= 0 && col < _cols);
        return _data[row*_cols + col];
    }

    inline const double& operator()(std::size_t row, std::size_t col) const {
        assert (row >= 0 && row < _rows);
        assert (col >= 0 && col < _cols);
        return _data[row*_cols + col];
    }
    MyLinearSystemSolver operator-(const MyLinearSystemSolver& x);
    bool operator==(const MyLinearSystemSolver& x);


    void SwapRows(std::size_t i, std::size_t j);
    void GaussianElimination();
    MyLinearSystemSolver BackSub();
    MyLinearSystemSolver MatrixMultiplication(MyLinearSystemSolver& x);
    MyLinearSystemSolver verify(const MyLinearSystemSolver& sol);




private:
    std::size_t _rows;
    std::size_t _cols;
    std::vector<double> _data;


};

std::ostream& operator<< (std::ostream& os, const MyLinearSystemSolver& a);
#endif //LINEAR_SYSTEM_SOLVER_MyLinearSystemSolver_H
