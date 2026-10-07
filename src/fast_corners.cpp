#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Kullanim: ./fast_corners <goruntu_yolu>\n";
        return 1;
    }
    cv::Mat img = cv::imread(argv[1]);
    if (img.empty()) { std::cerr << "Goruntu okunamadi\n"; return 1; }

    cv::Mat gray = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);

    std::vector<cv::KeyPoint> keypoints;
    cv::FAST(gray, keypoints, 20, true);
    std::cout << "Frame: " << argv[1] << ", threshold: 20, corners: "
          << keypoints.size() << std::endl;

    cv::Mat out;
    cv::drawKeypoints(img, keypoints, out, cv::Scalar(0, 255, 0));
    cv::imwrite("results/03_fast_corners.png", out);
    cv::imshow("FAST", out);
    cv::waitKey(0);
    return 0;
}