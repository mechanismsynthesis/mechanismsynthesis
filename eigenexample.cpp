#include <Eigen/Dense>
#include <iostream>

#include "eigenexample.h"

void EigenExample()
{
    // Initializing a dynamic matrix
    Eigen::MatrixXd m1(2,3);
    m1 << 1,3,5,6,7,8;
    std::cout << "m1 = " << std::endl << m1 << std::endl;
    std::cout << "size m1: " << m1.rows() << " X " << m1.cols() << std::endl;
    return;
}
