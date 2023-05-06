#include "circleintersection.h"

#include "doctest.h"

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
class TwoCircles: public NewtonRaphson::Interface
{
    double x1 = 0.0, y1 = 0.0, r1 = 0.0, x2 = 0.0, y2 = 0.0, r2 = 0.0;

    public:
    TwoCircles (double x1, double y1, double r1, double x2, double y2, double r2):x1(x1), y1(y1), r1(r1), x2(x2), y2(y2), r2(r2)
    {
    }

    private:
    virtual std::tuple<Eigen::VectorXd, Eigen::MatrixXd> GetFJacobian(Eigen::VectorXd xy)
    {
        auto x = xy[0];
        auto y = xy[1];
        Eigen::Vector2d fxy((x1-x)*(x1-x) + (y1-y)*(y1-y) - r1*r1, (x2-x)*(x2-x) + (y2-y)*(y2-y) - r2*r2);
        Eigen::Matrix2d J;
        J << -2*x1+2*x, -2*y1+2*y, -2*x2+2*x, -2*y2+2*y;
        return {fxy, J};
    }
};

NewtonRaphson::Solution GetCircleIntersection(double x1, double y1, double r1, double x2, double y2, double r2)
{
    Eigen::Vector2d xy(1.11, 2.22); // initial guess, midpoint of two 
    auto c = TwoCircles(x1, y1, r1, x2, y2, r2);
    return NewtonRaphson::GetSolution(xy, c);

}

TEST_CASE("testing the circleintersection function") {
    CHECK(GetCircleIntersection(1, 2, 3, 2, 0, 3).CompareForTest({Eigen::Vector2d(3.9899, 2.2449), 8, 0.0}));
    CHECK(GetCircleIntersection(1, 2, 3, 10, 15, 3).CompareForTest({std::nullopt, 100, 146.6366}));
    CHECK(GetCircleIntersection(10, 250, 335, 58, 92, 400).CompareForTest({Eigen::Vector2d(-323.0298, 213.7219), 8, 0.0}));
}