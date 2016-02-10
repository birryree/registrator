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

/*    cv::cuda::GpuMat gpuBase;
    cv::cuda::GpuMat gpuDest;
    gpuBase.download(base);
    gpuDest.download(dest);
*/
    std::cout << "done image loading" << std::endl;

    cv::Mat bgray, dgray;

    //cv::cuda::GpuMat base_gray, dest_gray;
    //cv::cuda::GpuMat base_gray, dest_gray;

    std::cout << "Converting color" << std::endl;

    cv::cvtColor(base, bgray, CV_BGR2GRAY);
    cv::cvtColor(dest, dgray, CV_BGR2GRAY);

    std::cout << "Making warp matrices" << std::endl;

    const int warp_mode = cv::MOTION_EUCLIDEAN;

    cv::Mat warp_matrix = 
        warp_mode == cv::MOTION_HOMOGRAPHY ?
            cv::Mat::eye(3, 3, CV_32F) :
            cv::Mat::eye(2, 3, CV_32F);

    std::cout << "setting iterations" << std::endl;

    int iterations = 5000;
    double termination_eps = 1e-10;


    cv::TermCriteria criteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS, iterations, termination_eps);

    std::cout << "Preparing to fuse" << std::endl;

    cv::cuda::GpuMat base_gray, dest_gray;
    base_gray.download(bgray);
    dest_gray.download(dgray);

    cv::cuda::GpuMat fusedGpuImage;

    cv::Mat fusedImage;

    //cv::findTransformECC(base_gray, dest_gray, warp_matrix, warp_mode, criteria);
    cv::findTransformECC(base_gray, dest_gray, warp_matrix, warp_mode, criteria);

    /*if (warp_mode != cv::MOTION_HOMOGRAPHY) {
        cv::warpAffine(dest, fusedGpuImage, warp_matrix, base.size(), cv::INTER_LINEAR + cv::WARP_INVERSE_MAP);
    }*/

    //cv::imwrite("fishexample.png", fusedImage);
}
