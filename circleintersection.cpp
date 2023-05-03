#include <Eigen/Dense>
#include <iostream>

#include "circleintersection.h"

// Circle intersection equations
// (x1 - x)^2 + (y1 - y)^2 = r1^2
// (x2 - x)^2 + (y2 - y)^2 = r2^2
// Giving the following for Newton Raphson method
// Function
// f = [(x1 - x)^2 + (y1 - y)^2 - r1^2
//      (x2 - x)^2 + (y2 - y)^2 = r2^2]
// Jacobian
// J = [(-2x1 + 2x) (-2y1 + 2y)
//      (-2x2 + 2x) (-2y2 + 2y)]
// Deltax (aks dx) = -Jinv * F
// Increment x = x + dx where f(x) is below the threshold
std::pair<double, double> GetCircleIntersection(double x1, double y1, double r1, double x2, double y2, double r2)
{
    const double minError = 0.0001;
    const int maxIterations = 100;
    Eigen::MatrixXd J(2, 2); J << 0.0, 0.0, 0.0, 0.0; // Jacobian
    Eigen::MatrixXd xy(2,1); xy << 1.11, 2.22; // initial guess
    Eigen::MatrixXd dxy(2, 1); dxy << 0.0, 0.0; // delta x and y
    Eigen::MatrixXd fxy(2, 1); fxy << 0.0, 0.0; // function
    double error = 1.0;
    int iteration = 0;
    while(error > minError && iteration < maxIterations)
    {
        xy = xy + dxy;
        auto x = xy(0,0);
        auto y = xy(1,0);
        fxy(0,0) = (x1-x)*(x1-x) + (y1-y)*(y1-y) - r1*r1; fxy(1,0) = (x2-x)*(x2-x) + (y2-y)*(y2-y) - r2*r2;
        error = abs(fxy.sum());
        J(0,0) = -2*x1+2*x; J(0,1) = -2*y1+2*y; J(1,0) = -2*x2+2*x; J(1,1) = -2*y2+2*y;
        dxy = -J.inverse()*fxy;
        std::cout << "Iteration:" << iteration << " Error: " << error << std::endl;
        ++iteration;
    }

    return {xy(0,0), xy(1,0)};
}

// Prints intersection point from x1, y1, r1 defining first circle, x2, y2, r2 defining second circle
void CircleIntersection()
{
    double x1 = 1.0, y1 = 2.0, r1 = 3.0, x2 = 2.0, y2 = 1.0, r2 = 3.0;
    auto intersection = GetCircleIntersection(x1, y1, r1, x2, y2, r2);
    std::cout << "Intersection of circles:" << std::endl;
    std::cout << "x1: " << x1 << " y1: " << y1 << " r1: " << r1 << std::endl;
    std::cout << "x2: " << x2 << " y2: " << y2 << " r2: " << r2 << std::endl;
    std::cout << "is x: " << intersection.first << " y: " << intersection.second << std::endl;
}