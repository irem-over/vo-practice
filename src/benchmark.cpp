#include <opencv2/opencv.hpp>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>

using clk = std::chrono::steady_clock;
static double ms(clk::time_point a, clk::time_point b) {
    return std::chrono::duration<double, std::milli>(b - a).count();
}

int main(int argc, char** argv) {
    if (argc < 2) { std::cerr << "Kullanim: ./benchmark <klasor>\n"; return 1; }
    std::vector<cv::String> files;
    cv::glob(std::string(argv[1]) + "/*.png", files, false);
    std::sort(files.begin(), files.end());
    size_t n = std::min<size_t>(files.size(), 200);   // ilk 200 kare
    if (n < 2) { std::cerr << "Yeterli goruntu yok\n"; return 1; }

    double tRead = 0, tFast = 0, tKlt = 0, tDraw = 0;
    int pairs = 0;
    cv::Mat prev = cv::imread(files[0], cv::IMREAD_GRAYSCALE);

    for (size_t i = 1; i < n; ++i) {
        auto t0 = clk::now();
        cv::Mat cur = cv::imread(files[i], cv::IMREAD_GRAYSCALE);
        auto t1 = clk::now();

        std::vector<cv::KeyPoint> kps;
        cv::FAST(prev, kps, 20, true);
        std::vector<cv::Point2f> p1, p2;
        cv::KeyPoint::convert(kps, p1);
        auto t2 = clk::now();

        std::vector<uchar> status; std::vector<float> err;
        if (!p1.empty())
            cv::calcOpticalFlowPyrLK(prev, cur, p1, p2, status, err,
                                     cv::Size(21, 21), 3);
        auto t3 = clk::now();

        cv::Mat vis;
        cv::cvtColor(cur, vis, cv::COLOR_GRAY2BGR);
        for (size_t k = 0; k < p2.size(); ++k)
            if (status[k]) cv::arrowedLine(vis, p1[k], p2[k], {0, 255, 0}, 1);
        auto t4 = clk::now();

        tRead += ms(t0, t1); tFast += ms(t1, t2);
        tKlt += ms(t2, t3);  tDraw += ms(t3, t4);
        ++pairs;
        prev = cur;
    }

    double total = (tRead + tFast + tKlt + tDraw) / pairs;
    char buf[512];
    std::snprintf(buf, sizeof(buf),
        "| Asama | Ortalama sure (ms) |\n|---|---|\n"
        "| Goruntu okuma | %.3f |\n| FAST | %.3f |\n"
        "| KLT | %.3f |\n| Cizim | %.3f |\n| **Toplam / kare** | **%.3f** |\n",
        tRead / pairs, tFast / pairs, tKlt / pairs, tDraw / pairs, total);
    std::cout << buf << "(" << pairs << " kare cifti ortalamasi)\n";

    std::ofstream("results/05_timing.md") << buf;
    return 0;
}