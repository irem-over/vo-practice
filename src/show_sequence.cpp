#include <opencv2/opencv.hpp>
#include <algorithm>
#include <iostream>
#include <vector>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Kullanim: ./show_sequence <goruntu_klasoru>\n";
        return 1;
    }
    std::vector<cv::String> files;
    cv::glob(std::string(argv[1]) + "/*.png", files, false);  // jpg ise *.jpg yap
    std::sort(files.begin(), files.end());
    if (files.empty()) {
        std::cerr << "Klasorde goruntu bulunamadi!\n";
        return 1;
    }

    for (size_t i = 0; i < files.size(); ++i) {
        cv::Mat img = cv::imread(files[i]);
        if (img.empty()) continue;
        cv::putText(img, "Frame " + std::to_string(i), {10, 30},
                    cv::FONT_HERSHEY_SIMPLEX, 1.0, {0, 255, 0}, 2);
        cv::imshow("Dizi", img);
        int key = cv::waitKey(33);
        if (key == 27) break;       
        if (key == 's') cv::imwrite("results/02_sequence.png", img);
    }
    return 0;
}