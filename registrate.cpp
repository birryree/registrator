#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <vector>
#include <string>

int main(int argc, char** argv) {
    std::vector<std::string> args(argv, argv + argc);

    for(auto a : args) {
        std::cout << a << "\n";
    }

    cv::Mat base = cv::imread(args[1]);
    cv::Mat dest = cv::imread(args[2]);

    cv::Mat base_gray, dest_gray;

    cv::cvtColor(base, base_gray, CV_BGR2GRAY);
    cv::cvtColor(dest, dest_gray, CV_BGR2GRAY);

    const int warp_mode = cv::MOTION_EUCLIDEAN;

    cv::Mat warp_matrix = 
        warp_mode == cv::MOTION_HOMOGRAPHY ?
            cv::Mat::eye(3, 3, CV_32F) :
            cv::Mat::eye(2, 3, CV_32F);

    int iterations = 5000;
    double termination_eps = 1e-10;


    cv::TermCriteria criteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS, iterations, termination_eps);

    cv::Mat fusedImage;

    cv::findTransformECC(base_gray, dest_gray, warp_matrix, warp_mode, criteria);

    if (warp_mode != cv::MOTION_HOMOGRAPHY) {
        cv::warpAffine(dest, fusedImage, warp_matrix, base.size(), cv::INTER_LINEAR + cv::WARP_INVERSE_MAP);
    }

    cv::imwrite("fishexample.png", fusedImage);
}
