#include "fourbarmechanism.h"

#include "../doctest.h"

// Four bar equations
// Fixed Link
// 1 -> X1 = 0
// 2 -> Y1 = 0
// 3 -> Ɵ1 = 0
// Revolute Joint 1
// 4 -> X1 – l1*cos(Ɵ1) = X2 – l2*cos(Ɵ2)
// 5 -> Y1 – l1*sin(Ɵ1)  = Y2 – l2*sin(Ɵ2)
// Revolute Joint 2
// 6 -> X2 – l2*cos(Ɵ2) = X3 – l3*cos(Ɵ3)
// 7 -> Y2 – l2*sin(Ɵ2)  = Y3 – l3*sin(Ɵ3)
// Revolute Joint 3
// 8 -> X3 – l3*cos(Ɵ3) = X4 – l4*cos(Ɵ4)
// 9 -> Y3 – l3*sin(Ɵ3)  = Y4 – l4*sin(Ɵ4)
// Revolute Joint 4
// 10 -> X1 + l1*cos(Ɵ1) = X4 + l4*cos(Ɵ4)
// 11 -> Y1 + l1*sin(Ɵ1)  = Y4 + l4*sin(Ɵ4)
// Driver
// 12 -> Ɵ2 = α -> 0 to 360
// 12 Variables – 12 Equations -> Newton Raphson

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
class FourBar: public NewtonRaphson::Interface
{
    double x1 = 0.0, y1 = 0.0, r1 = 0.0, x2 = 0.0, y2 = 0.0, r2 = 0.0;

    public:
    FourBar (double x1, double y1, double r1, double x2, double y2, double r2):x1(x1), y1(y1), r1(r1), x2(x2), y2(y2), r2(r2)
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

NewtonRaphson::Solution GetFourBarSolution()
{
    Eigen::Vector2d xy(1.11, 2.22); // initial guess, midpoint of two 
    auto c = FourBar(1, 2, 3, 2, 0, 3);
    return NewtonRaphson::GetSolution(xy, c);

}

TEST_CASE("testing the circleintersection function") {
    CHECK(GetFourBarSolution().CompareForTest({Eigen::Vector2d(3.9899, 2.2449), 8, 0.0}));
}
