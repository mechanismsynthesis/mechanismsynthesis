#include "newtonraphson.h"

namespace NewtonRaphson {

std::optional<Eigen::VectorXd> GetSolution(Eigen::VectorXd xy, NewtonRaphsonInterface &interface)
{
    const double minError = 0.0001;
    const int maxIterations = 100;

    int size = xy.size();
    Eigen::MatrixXd J(size, size); // Jacobian
    Eigen::VectorXd fxy(size); // function
    double error = 1.0;
    int iteration = 0;
    while (error > minError && iteration < maxIterations)
    {
        std::tie(fxy, J) = interface.GetFJacobian(xy);
        error = abs(fxy.sum());
        xy += -J.inverse()*fxy;
        ++iteration;
    }

    return error <= minError ? xy std::nullopt:
}

} // namespace NewtonRaphson