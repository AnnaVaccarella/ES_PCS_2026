#include <iostream>
#include <Eigen/Dense>
#include "gradiente_coniugato.hpp"

int main(int argc, char **argv) 
{
    const double tol = 1.0e-15;
    unsigned int n = 3;

    Eigen::MatrixXd B = Eigen::MatrixXd::Random(n, n);

    if (std::abs(B.determinant()) < tol)
        return -1;

    Eigen::MatrixXd A = B.transpose() * B;
    Eigen::VectorXd x_ex = Eigen::VectorXd::Ones(n);
    Eigen::VectorXd b = A * x_ex;

    const unsigned int it_max = 10000;
    const double res_tol = 1.0e-12;
    
    std::cout << std::scientific;
    std::cout << "Condizionamento della Matrice A: " << condA(A) << "\n";

    //Test gradiente classico
    Eigen::VectorXd x_g = Eigen::VectorXd::Zero(n);
    double res_norm_0_g = (b - A * x_g).norm();
    unsigned int it_g = gradiente_classico(A, b, x_g, res_tol, it_max);
    double err_rel_g = (x_g - x_ex).norm() / x_ex.norm();

    std::cout << "GRADIENTE CLASSICO \n";
    std::cout << "Le iterazioni effettuate sono: " << it_g << "/" << it_max << "\n";
    std::cout << "L'errore relativo è:       " << err_rel_g << "\n";

    //Test gadiente coniugato
    Eigen::VectorXd x_gc = Eigen::VectorXd::Zero(n);
    double res_norm_0_gc = (b - A * x_gc).norm();
    unsigned int it_gc = gradiente_coniugato(A, b, x_gc, res_tol, it_max);
    double err_rel_gc = (x_gc - x_ex).norm() / x_ex.norm();

    std::cout << "GRADIENTE CONIUGATO \n";
    std::cout << "Le iterazioni effettuate sono: " << it_gc << "/" << it_max << "\n";
    std::cout << "L'errore relativo è:       " << err_rel_gc << "\n";
    std::cout << "Soluzione calcolata:\n" << x_gc << "\n";

    return 0;
}