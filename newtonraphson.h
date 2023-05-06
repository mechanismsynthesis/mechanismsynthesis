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

std::optional<Eigen::VectorXd> GetSolution(Eigen::VectorXd xy, Interface &interface, const Options &options = Options());

} // namespace NewtonRaphson