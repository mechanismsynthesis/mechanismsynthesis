#include <Eigen/Dense>
#include <optional>

// Calculatign Intersection between two circles using Newton Raphson method
std::optional<Eigen::VectorXd> GetCircleIntersection(double x1, double y1, double r1, double x2, double y2, double r2);
