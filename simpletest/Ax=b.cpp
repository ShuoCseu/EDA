#include <iostream>
#include <amgcl/amg.hpp>
#include <amgcl/backend/builtin.hpp>
#include <amgcl/adapter/crs_tuple.hpp>

int main() {
    typedef amgcl::backend::builtin<double> Backend;

    // 定义矩阵A和向量b
    const int n = 3;  // 矩阵A的维度
    std::vector<int>    ptr = {0, 2, 5, 7};  // 行指针数组
    std::vector<int>    col = {0, 2, 1, 2, 0, 1, 2};  // 列索引数组
    std::vector<double> val = {4, -1, 2, -1, 6, 8, 2};  // 非零元素值数组
    std::vector<double> b   = {1, 1, 1};  // 向量b

    // 创建AMGCL求解器
    typedef amgcl::make_solver<
        amgcl::amg<Backend>,
        amgcl::runtime::preconditioner::wrapper
    > Solver;
    
    amgcl::adapter::crs_tuple<double, int> A(std::make_tuple(n, ptr, col, val));
    Solver solve(A);

    // 解决线性系统
    std::vector<double> x(n, 0.0);  // 初始解向量
    int iters;
    double resid;
    std::tie(iters, resid) = solve(b, x);

    // 输出结果
    std::cout << "Iterations: " << iters << std::endl;
    std::cout << "Residual: " << resid << std::endl;
    std::cout << "Solution: ";
    for (int i = 0; i < n; ++i) {
        std::cout << x[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}