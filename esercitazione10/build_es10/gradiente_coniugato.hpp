#pragma once
#include <iostream>
#include <Eigen/Dense>

// Funzione ausiliaria per calcolare il condizionamento della matrice
double condA(const Eigen::MatrixXd& A)
{
    Eigen::JacobiSVD<Eigen::MatrixXd> svd(A);
    Eigen::VectorXd singularValuesA = svd.singularValues();
    return singularValuesA.maxCoeff() / singularValuesA.minCoeff();
}

// Metodo del Gradiente classico
unsigned int gradiente_classico(const Eigen::MatrixXd& A, const Eigen::VectorXd& b, Eigen::VectorXd& x, double res_tol, unsigned int it_max)
{
    Eigen::VectorXd res = b - A * x;
    double res_norm_0 = res.norm();
    unsigned int it = 0;
	
	if(res_norm_0 < 1e-16) return 0;

    while (it < it_max && res.norm() > res_tol * res_norm_0)
    {
		Eigen::VectorXd A_res = A * res;
        const double alpha_k = res.squaredNorm() / (res.transpose() * A_res).value();

        x = x + alpha_k * res;
        res = res - alpha_k * A * res;

        it++;
    }

    return it;
}

// Metodo del Gradiente coniugato 
unsigned int gradiente_coniugato(const Eigen::MatrixXd& A, const Eigen::VectorXd& b, Eigen::VectorXd& x, double res_tol, unsigned int it_max)
{
    Eigen::VectorXd r = b - A * x; 
    Eigen::VectorXd p = r;         
    double res_norm_0 = r.norm();
    unsigned int it = 0;
	
	//Gestione del caso in cui b=0 e x_iniziale = 0 
	if(res_norm_0 < 1e-16) return 0; 
	double r_old_squared_norm = r.squaredNorm();

    while (it < it_max && r.norm() > res_tol * res_norm_0)
    {
        Eigen::VectorXd Ap = A * p;
		
        const double alpha_k = r_old_squared_norm / (p.transpose() * Ap).value();
        x = x + alpha_k * p;
		r = r - alpha_k * Ap;
        
		double r_new_squared_norm = r.squaredNorm();
		
		
        if (std::sqrt(r_new_squared_norm) <= res_tol * res_norm_0) {
            it++;
            break;
        }
        
        const double beta_k = r_new_squared_norm / r_old_squared_norm;
		p = r + beta_k * p;
        r_old_squared_norm = r_new_squared_norm;
        
        it++; 
    }
    return it;
}