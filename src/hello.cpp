#include <iostream>
#include <opencv2/core.hpp>
#include <Eigen/Dense>

int main() {
    std::cout << "Hello world!\n";
    std::cout << "OpenCV version: " << CV_VERSION << "\n";

    Eigen::Matrix3d R = Eigen::Matrix3d::Identity();
    std::cout << "Eigen 3x3 identity matrix:\n" << R << "\n";
    return 0;
}