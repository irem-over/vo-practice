#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Kullanim: ./klt_tracking <kare1> <kare2>\n";
        return 1;
    }
    cv::Mat g1 = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
    cv::Mat g2 = cv::imread(argv[2], cv::IMREAD_GRAYSCALE);
    cv::Mat color2 = cv::imread(argv[2]);
    if (g1.empty() || g2.empty()) { std::cerr << "Goruntu okunamadi\n"; return 1; }

    std::vector<cv::KeyPoint> kps;
    cv::FAST(g1, kps, 20, true);
    std::vector<cv::Point2f> p1, p2;
    cv::KeyPoint::convert(kps, p1);

    std::vector<uchar> status;
    std::vector<float> err;
    cv::calcOpticalFlowPyrLK(g1, g2, p1, p2, status, err,
                             cv::Size(21, 21), 3);

    int tracked = 0;
    for (size_t i = 0; i < p1.size(); ++i) {
        if (!status[i]) continue;
        cv::arrowedLine(color2, p1[i], p2[i], cv::Scalar(0, 255, 0), 1,
                        cv::LINE_AA, 0, 0.3);
        cv::circle(color2, p2[i], 2, cv::Scalar(0, 0, 255), -1);
        ++tracked;
    }
    std::cout << "Frames: " << argv[1] << " -> " << argv[2]
          << ", tracked: " << tracked << " / " << p1.size() << std::endl;

    cv::imwrite("results/04_klt_tracking.png", color2);
    cv::imshow("KLT", color2);
    cv::waitKey(0);
    return 0;
}