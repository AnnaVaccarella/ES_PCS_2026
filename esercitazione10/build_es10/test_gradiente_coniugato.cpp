#include <iostream>
#include <Eigen/Dense>
#include "gradiente_coniugato.hpp"

int main() {
    const double err_tol = 1.0e-11; 
    const unsigned int it_max = 10000;
    const double res_tol = 1.0e-12;
    
    std::cout << "Test gradiente coniugato (Caso Standard)\n";
    Eigen::MatrixXd B1 = Eigen::MatrixXd::Random(3, 3);
    Eigen::MatrixXd A1 = B1.transpose() * B1;
    Eigen::VectorXd x_ex1 = Eigen::VectorXd::Random(3);
    Eigen::VectorXd b1 = A1 * x_ex1;
    Eigen::VectorXd x1 = Eigen::VectorXd::Zero(3);
    
    gradiente_coniugato(A1, b1, x1, res_tol, it_max);
    
    double err_rel_1 = (x1 - x_ex1).norm() / x_ex1.norm();
    if (err_rel_1 < err_tol) {
        std::cout << "Test gradiente coniugato passato! Err: " << err_rel_1 << "\n";
    } else {
        std::cout << "Test gradiente NON passato! Err: " << err_rel_1 << "\n";
    }
    
    std::cout << "Test gradiente coniugato (Caso b = 0)\n";
    Eigen::MatrixXd B2 = Eigen::MatrixXd::Random(3, 3);
    Eigen::MatrixXd A2 = B2.transpose() * B2;
    
    Eigen::VectorXd b2 = Eigen::VectorXd::Zero(3); 
    Eigen::VectorXd x_ex2 = Eigen::VectorXd::Zero(3); 
    Eigen::VectorXd x2 = Eigen::VectorXd::Random(3);  
    
    gradiente_coniugato(A2, b2, x2, res_tol, it_max);
    
    double err_ass_2 = (x2 - x_ex2).norm();
    if (err_ass_2 < err_tol) {
        std::cout << "Test gradiente coniugato passato per b=0! Err: " << err_ass_2 << "\n";
    } else {
        std::cout << "Test gradiente NON passato per b=0! Err: " << err_ass_2 << "\n";
    }
    
    return 0;
}