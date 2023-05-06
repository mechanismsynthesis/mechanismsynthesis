#include <Eigen/Dense>
#include <tuple>
#include <optional>

namespace NewtonRaphson {

struct Options
{
    const double minError = 0.0001;
    const int maxIterations = 100;
};

class Interface
{
    public:
    virtual std::tuple<Eigen::VectorXd, Eigen::MatrixXd> GetFJacobian(Eigen::VectorXd xy) = 0;
};

struct Solution
{
    const std::optional<Eigen::VectorXd> vector; // the solution from Newton Raphson
    const int iterations; // Number of iterations performed to arrive at the solution
    const double error; // Error value at the solution

    // Compare this with other solution for testing purpose bu truncating number to the provided precisions 
    bool CompareForTest(const Solution &other, int precision = 4);
};

Solution GetSolution(Eigen::VectorXd xy, Interface &interface, const Options &options = Options());

} // namespace NewtonRaphson