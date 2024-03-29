#include "newtonraphson.h"

namespace NewtonRaphson {

 bool Solution::CompareForTest(const Solution &other, int precision)
 {
    if (this->iterations != other.iterations)
        return false;

    // Compare for optional vector. If oen if optional, both should be optional
    if (this->vector == std::nullopt || other.vector == std::nullopt)
        return other.vector == std::nullopt && other.vector == std::nullopt;

    int p = std::pow(10, -precision);
    // Only compare error if vector is not optional. Else error might vary a lot on paltforms (aka Butterfly effect).
    if (std::abs(this->error - other.error) <= p)
        return false;

    if (this->vector.value().size() != other.vector.value().size())
        return false;

    for (size_t i = 0; i < this->vector->size(); ++i)
    {
        if (std::abs(this->vector.value()[i] - other.vector.value()[i]) <= p)
            return false;
    }

    return true;
 }

// Newton Raphson method of finding solution to a non-liner set of equations
// Wiki - https://en.wikipedia.org/wiki/Newton%27s_method
// F is the Function, Eg:
// f = [(x1 - x)^2 + (y1 - y)^2 - r1^2
//      (x2 - x)^2 + (y2 - y)^2 = r2^2]
// J is Jacobian, Eg:
// J = [(-2x1 + 2x) (-2y1 + 2y)
//      (-2x2 + 2x) (-2y2 + 2y)]
// Deltax (aka dx) = -Jinv * F
// Increment x = x + dx till f(x) is below the threshold
Solution GetSolution(Eigen::VectorXd xy, Interface &interface, const Options &options)
{
    int size = xy.size();
    Eigen::MatrixXd J(size, size); // Jacobian
    Eigen::VectorXd fxy(size); // function
    double error = options.minError + 1.0; // initial error should be greater than minError
    int iteration = 0;
    while (error > options.minError && iteration < options.maxIterations)
    {
        std::tie(fxy, J) = interface.GetFJacobian(xy);
        error = abs(fxy.sum());
        xy += -J.inverse()*fxy;
        ++iteration;
    }

    return {error <= options.minError ? std::optional(xy) : std::nullopt, iteration, error};
}

} // namespace NewtonRaphson
