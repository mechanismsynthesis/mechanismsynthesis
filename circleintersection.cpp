#include <Eigen/Dense>
#include <iostream>
#include <optional>
#include <vector>

#include "circleintersection.h"

struct TwoCircles
{
    double x1 = 0.0, y1 = 0.0, r1 = 0.0, x2 = 0.0, y2 = 0.0, r2 = 0.0;
};

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
// Deltax (aka dx) = -Jinv * F
// Increment x = x + dx till f(x) is below the threshold
std::optional<Eigen::Vector2d> GetCircleIntersection(double x1, double y1, double r1, double x2, double y2, double r2)
{
    const double minError = 0.0001;
    const int maxIterations = 100;
    Eigen::Matrix2d J; J << 0.0, 0.0, 0.0, 0.0; // Jacobian
    Eigen::Vector2d xy(1.11, 2.22); // initial guess, midpoint of two 
    Eigen::Vector2d fxy(0.0, 0.0); // function
    double error = 1.0;
    int iteration = 0;
    while (error > minError && iteration < maxIterations)
    {
        auto x = xy[0];
        auto y = xy[1];
        fxy = {(x1-x)*(x1-x) + (y1-y)*(y1-y) - r1*r1, (x2-x)*(x2-x) + (y2-y)*(y2-y) - r2*r2};
        error = abs(fxy.sum());
        J << -2*x1+2*x, -2*y1+2*y, -2*x2+2*x, -2*y2+2*y;
        xy += -J.inverse()*fxy;
        ++iteration;
    }

    std::cout << "Iterations: " << iteration << " Error: " << error << std::endl;

    if (error <= minError)
    {
        return xy;
    }
    else
    {
        return std::nullopt;
    }
}

// Prints intersection point from x1, y1, r1 defining first circle, x2, y2, r2 defining second circle
void CircleIntersection()
{
    std::vector<TwoCircles> circlePairs{
        {1.0, 2.0, 3.0, 2.0, 0.0, 3.0},
        {1.0, 2.0, 3.0, 10.0, 15.0, 3.0},
        {10.0, 250.0, 335.0, 58.0, 92.0, 400.0},
    };
    for (auto c: circlePairs)
    {
        auto intersection = GetCircleIntersection(c.x1, c.y1, c.r1, c.x2, c.y2, c.r2);
        std::cout << "Intersection of circles:" << "x1: " << c.x1 << " y1: " << c.y1 << " r1: " << c.r1 << " x2: " << c.x2 << " y2: " << c.y2 << " r2: " << c.r2 ;
        if (intersection)
        {
            std::cout << " is x: " << (*intersection)[0] << " y: " << (*intersection)[1] << std::endl;
        }
        else
        {
            std::cout << " Not found" << std::endl;
        }   
    }
}