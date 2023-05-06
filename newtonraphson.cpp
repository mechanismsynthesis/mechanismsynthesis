#include "newtonraphson.h"

namespace NewtonRaphson {

// F is the Function, Eg:
// f = [(x1 - x)^2 + (y1 - y)^2 - r1^2
//      (x2 - x)^2 + (y2 - y)^2 = r2^2]
// J is Jacobian, Eg:
// J = [(-2x1 + 2x) (-2y1 + 2y)
//      (-2x2 + 2x) (-2y2 + 2y)]
// Deltax (aka dx) = -Jinv * F
// Increment x = x + dx till f(x) is below the threshold
std::optional<Eigen::VectorXd> GetSolution(Eigen::VectorXd xy, Interface &interface, const Options &options)
{
    int size = xy.size();
    Eigen::MatrixXd J(size, size); // Jacobian
    Eigen::VectorXd fxy(size); // function
    double error = options.minError + 1.0; // initial error should be greter than minError
    int iteration = 0;
    while (error > options.minError && iteration < options.maxIterations)
    {
        std::tie(fxy, J) = interface.GetFJacobian(xy);
        error = abs(fxy.sum());
        xy += -J.inverse()*fxy;
        ++iteration;
    }

    return error <= options.minError ? std::optional(xy) : std::nullopt;
}

} // namespace NewtonRaphson