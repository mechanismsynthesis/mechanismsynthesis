#include <Eigen/Dense>
#include <tuple>
#include <optional>

namespace NewtonRaphson {

class NewtonRaphsonInterface
{
    public:
    virtual std::tuple<Eigen::VectorXd, Eigen::MatrixXd> GetFJacobian(Eigen::VectorXd xy) = 0;
};

std::optional<Eigen::VectorXd> GetSolution(Eigen::VectorXd xy, NewtonRaphsonInterface &interface);

} // namespace NewtonRaphson