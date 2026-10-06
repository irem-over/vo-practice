#include <iostream>
#include <opencv2/core.hpp>
#include <Eigen/Dense>

int main() {
    std::cout << "Merhaba dunya!\n";
    std::cout << "OpenCV surumu: " << CV_VERSION << "\n";

    Eigen::Matrix3d R = Eigen::Matrix3d::Identity();
    std::cout << "Eigen 3x3 birim matris:\n" << R << "\n";
    return 0;
}